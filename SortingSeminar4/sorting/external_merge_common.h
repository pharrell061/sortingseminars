#ifndef EXTERNAL_MERGE_COMMON_H
#define EXTERNAL_MERGE_COMMON_H
// Shared helpers for the three external (file-based) merge sorts in
// seminar 4. Not one of the assignment's named headers by itself -
// two_phase_merge_sort.h, one_phase_merge_sort.h and
// natural_merge_sort.h each include this and expose their own public
// function, as the assignment asks.
//
// File format: one value per line; a blank line marks the end of a
// "run" (a maximal already-sorted stretch). EOF also ends the file.

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdio>

// Reads the next run from 'in' into 'run'. Returns false only when
// there was nothing left to read (stream already exhausted).
template <typename T>
bool readRun(std::ifstream& in, std::vector<T>& run) {
    run.clear();
    std::string line;
    bool readAny = false;
    while (std::getline(in, line)) {
        if (line.empty()) {
            if (readAny) return true;   // end of this run
            else continue;              // skip stray blank lines
        }
        std::istringstream iss(line);
        T value;
        iss >> value;
        run.push_back(value);
        readAny = true;
    }
    return readAny; // true if we captured a final run with no trailing blank line
}

// Appends 'run' to 'out' followed by a blank-line separator.
template <typename T>
void writeRun(std::ofstream& out, const std::vector<T>& run) {
    for (const T& v : run) out << v << "\n";
    out << "\n";
}

// Standard merge of two already-sorted runs.
template <typename T>
std::vector<T> mergeTwoRuns(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result;
    result.reserve(a.size() + b.size());
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
    }
    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);
    return result;
}

// Splits fixed-length-1 runs alternately into fileA/fileB. This is
// the bootstrap step every external merge sort needs at least once.
template <typename T>
void distributeInitialRuns(const std::string& inputFile,
                            const std::string& fileA,
                            const std::string& fileB) {
    std::ifstream in(inputFile);
    std::ofstream outA(fileA), outB(fileB);
    T value;
    bool toggle = false;
    while (in >> value) {
        std::vector<T> run{value};
        writeRun(toggle ? outB : outA, run);
        toggle = !toggle;
    }
}

// Splits the *natural* ascending runs found in inputFile alternately
// into fileA/fileB (used by natural merge sort: runs can be longer
// than 1 from the start, which means fewer merge passes).
template <typename T>
void distributeNaturalRuns(const std::string& inputFile,
                            const std::string& fileA,
                            const std::string& fileB) {
    std::ifstream in(inputFile);
    std::ofstream outA(fileA), outB(fileB);
    std::vector<T> values{std::istream_iterator<T>(in), std::istream_iterator<T>()};

    bool toggle = false;
    size_t i = 0;
    while (i < values.size()) {
        std::vector<T> run;
        run.push_back(values[i]);
        size_t j = i + 1;
        while (j < values.size() && values[j] >= values[j - 1]) {
            run.push_back(values[j]);
            ++j;
        }
        writeRun(toggle ? outB : outA, run);
        toggle = !toggle;
        i = j;
    }
}

// Re-splits the runs already present in inputFile (whatever their
// length) alternately into fileA/fileB, preserving each run intact.
// Used to redistribute a just-merged file before the next merge pass.
template <typename T>
void distributeRuns(const std::string& inputFile,
                     const std::string& fileA,
                     const std::string& fileB) {
    std::ifstream in(inputFile);
    std::ofstream outA(fileA), outB(fileB);
    std::vector<T> run;
    bool toggle = false;
    while (readRun(in, run)) {
        writeRun(toggle ? outB : outA, run);
        toggle = !toggle;
    }
}

// Copies the single run sitting in sourceFile into outputFile,
// stripped of the trailing blank-line separator, one value per line.
template <typename T>
void copyFinalRun(const std::string& sourceFile, const std::string& outputFile) {
    std::ifstream in(sourceFile);
    std::vector<T> run;
    readRun(in, run);
    std::ofstream out(outputFile);
    for (const T& v : run) out << v << "\n";
}

#endif // EXTERNAL_MERGE_COMMON_H
