#ifndef VISUAL_REPORTER_H
#define VISUAL_REPORTER_H
// Custom Catch2 reporter: shows every test case with PASS/FAIL, a bar
// proportional to how long it took, and the time itself. Tests are
// grouped by algorithm (the text before ": " in the test name), and a
// summary chart at the end compares total time per algorithm.
//
// Use the old default output with:  ./sorting_tests -r console
#include "catch.hpp"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

class VisualReporter : public Catch::StreamingReporterBase<VisualReporter> {
    using Clock = std::chrono::steady_clock;

    struct Result {
        std::string group;
        std::string name;
        bool passed = true;
        double micros = 0.0;
        std::vector<std::string> failures;
    };

    static const int BAR_WIDTH = 24;

    std::vector<Result> results_;
    Result current_;
    Clock::time_point start_;

    static std::string formatTime(double us) {
        std::ostringstream o;
        o << std::fixed;
        if (us < 1000.0)
            o << std::setprecision(1) << us << " us";
        else
            o << std::setprecision(3) << us / 1000.0 << " ms";
        return o.str();
    }

    static std::string bar(double value, double maxValue) {
        int filled = 0;
        if (maxValue > 0.0) {
            filled = static_cast<int>(value / maxValue * BAR_WIDTH + 0.5);
            if (filled < 1 && value > 0.0) filled = 1;
        }
        return std::string(filled, '#') + std::string(BAR_WIDTH - filled, '.');
    }

    static std::string pad(const std::string& s, size_t width) {
        return s.size() >= width ? s : s + std::string(width - s.size(), ' ');
    }

public:
    explicit VisualReporter(Catch::ReporterConfig const& config)
        : StreamingReporterBase(config) {
        m_reporterPrefs.shouldRedirectStdOut = false;
        m_reporterPrefs.shouldReportAllAssertions = false;
    }

    static std::string getDescription() {
        return "Per-test PASS/FAIL with time bars, grouped by algorithm";
    }

    void testCaseStarting(Catch::TestCaseInfo const& info) override {
        StreamingReporterBase::testCaseStarting(info);
        current_ = Result();
        size_t sep = info.name.find(": ");
        if (sep == std::string::npos) {
            current_.group = "(ungrouped)";
            current_.name = info.name;
        } else {
            current_.group = info.name.substr(0, sep);
            current_.name = info.name.substr(sep + 2);
        }
        start_ = Clock::now();
    }

    void assertionStarting(Catch::AssertionInfo const&) override {}

    bool assertionEnded(Catch::AssertionStats const& stats) override {
        if (!stats.assertionResult.isOk()) {
            current_.passed = false;
            std::ostringstream o;
            o << stats.assertionResult.getSourceInfo().file << ":"
              << stats.assertionResult.getSourceInfo().line << "  "
              << stats.assertionResult.getExpression();
            if (stats.assertionResult.hasExpandedExpression())
                o << "  with expansion:  "
                  << stats.assertionResult.getExpandedExpression();
            current_.failures.push_back(o.str());
        }
        return true;
    }

    void testCaseEnded(Catch::TestCaseStats const& stats) override {
        // Take the time first, so printing/bookkeeping isn't counted.
        auto end = Clock::now();
        StreamingReporterBase::testCaseEnded(stats);
        current_.micros =
            std::chrono::duration<double, std::micro>(end - start_).count();
        results_.push_back(current_);
    }

    void testRunEnded(Catch::TestRunStats const& stats) override {
        double maxTime = 0.0;
        size_t nameWidth = 0;
        for (const auto& r : results_) {
            maxTime = std::max(maxTime, r.micros);
            nameWidth = std::max(nameWidth, r.name.size());
        }

        // ---- per-test listing, grouped by algorithm ----
        std::string lastGroup;
        std::vector<std::pair<std::string, double>> groupTotals;
        std::vector<std::pair<std::string, std::pair<int, int>>> groupCounts;

        stream << "\n";
        for (const auto& r : results_) {
            if (r.group != lastGroup) {
                lastGroup = r.group;
                groupTotals.push_back({r.group, 0.0});
                groupCounts.push_back({r.group, {0, 0}});
                Catch::Colour c(Catch::Colour::Headers);
                stream << "  " << r.group << "\n";
            }
            groupTotals.back().second += r.micros;
            groupCounts.back().second.second++;
            if (r.passed) groupCounts.back().second.first++;

            stream << "    ";
            {
                Catch::Colour c(r.passed ? Catch::Colour::ResultSuccess
                                         : Catch::Colour::Error);
                stream << (r.passed ? "[PASS] " : "[FAIL] ");
            }
            stream << pad(r.name, nameWidth) << "  ";
            {
                Catch::Colour c(r.passed ? Catch::Colour::Success
                                         : Catch::Colour::Error);
                stream << bar(r.micros, maxTime);
            }
            stream << "  " << std::setw(10) << formatTime(r.micros) << "\n";

            for (const auto& f : r.failures) {
                Catch::Colour c(Catch::Colour::Error);
                stream << "           -> " << f << "\n";
            }
        }

        // ---- per-algorithm comparison ----
        double maxGroup = 0.0;
        size_t groupWidth = 0;
        for (const auto& g : groupTotals) {
            maxGroup = std::max(maxGroup, g.second);
            groupWidth = std::max(groupWidth, g.first.size());
        }
        stream << "\n";
        {
            Catch::Colour c(Catch::Colour::Headers);
            stream << "  Total time per algorithm\n";
        }
        for (size_t i = 0; i < groupTotals.size(); ++i) {
            const auto& g = groupTotals[i];
            const auto& cnt = groupCounts[i].second;
            bool ok = cnt.first == cnt.second;
            stream << "    " << pad(g.first, groupWidth) << "  ";
            {
                Catch::Colour c(ok ? Catch::Colour::Success
                                   : Catch::Colour::Error);
                stream << bar(g.second, maxGroup);
            }
            stream << "  " << std::setw(10) << formatTime(g.second) << "   "
                   << cnt.first << "/" << cnt.second << " passed\n";
        }

        // ---- overall summary ----
        double total = 0.0;
        for (const auto& r : results_) total += r.micros;
        const auto& t = stats.totals;
        stream << "\n";
        {
            bool allOk = t.testCases.failed == 0;
            Catch::Colour c(allOk ? Catch::Colour::ResultSuccess
                                  : Catch::Colour::Error);
            stream << "  " << t.testCases.passed << "/"
                   << (t.testCases.passed + t.testCases.failed)
                   << " tests passed";
            if (!allOk) stream << ", " << t.testCases.failed << " FAILED";
            stream << "  (" << t.assertions.passed << " assertions ok, "
                   << t.assertions.failed << " failed)  total "
                   << formatTime(total) << "\n";
        }
        stream << std::endl;

        StreamingReporterBase::testRunEnded(stats);
    }
};

CATCH_REGISTER_REPORTER("visual", VisualReporter)

#endif // VISUAL_REPORTER_H
