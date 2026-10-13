#ifndef ONE_PHASE_MERGE_SORT_H
#define ONE_PHASE_MERGE_SORT_H
#include "external_merge_common.h"
#include <cstdio>

// One-phase simple merge sort (external sort, run length starts at 1).
// Unlike the two-phase version, merging and redistributing happen in
// the SAME pass: as each pair of runs from the current input files is
// merged, the result is written straight into one of the two *next*
// input files, alternating between them. There is no separate
// "distribute" pass after the initial bootstrap split - that's what
// makes it "one-phase" rather than "two-phase".
template <typename T>
void onePhaseMergeSort(const std::string& inputFile, const std::string& outputFile) {
    // Two fixed pairs of temp files; each pass reads from one pair
    // and writes into the other, then they swap roles.
    const std::string pair0[2] = {"op_0a.tmp", "op_0b.tmp"};
    const std::string pair1[2] = {"op_1a.tmp", "op_1b.tmp"};

    distributeInitialRuns<T>(inputFile, pair0[0], pair0[1]);
    bool readFrom0 = true;
    std::vector<T> lastMerged;

    while (true) {
        const std::string& inFileA = readFrom0 ? pair0[0] : pair1[0];
        const std::string& inFileB = readFrom0 ? pair0[1] : pair1[1];
        const std::string& outFileC = readFrom0 ? pair1[0] : pair0[0];
        const std::string& outFileD = readFrom0 ? pair1[1] : pair0[1];

        std::ifstream inA(inFileA), inB(inFileB);
        std::ofstream outC(outFileC), outD(outFileD);

        size_t runCount = 0;
        bool toggle = false;
        std::vector<T> runA, runB;
        bool haveA = readRun(inA, runA);
        bool haveB = readRun(inB, runB);

        while (haveA || haveB) {
            std::vector<T> mergedRun;
            if (haveA && haveB) mergedRun = mergeTwoRuns(runA, runB);
            else if (haveA) mergedRun = runA;
            else mergedRun = runB;

            writeRun(toggle ? outD : outC, mergedRun);
            lastMerged = mergedRun;
            toggle = !toggle;
            ++runCount;

            haveA = readRun(inA, runA);
            haveB = readRun(inB, runB);
        }
        inA.close(); inB.close(); outC.close(); outD.close();

        if (runCount <= 1) {
            std::ofstream out(outputFile);
            for (const T& v : lastMerged) out << v << "\n";
            break;
        }

        readFrom0 = !readFrom0; // next pass reads what we just wrote
    }

    std::remove(pair0[0].c_str()); std::remove(pair0[1].c_str());
    std::remove(pair1[0].c_str()); std::remove(pair1[1].c_str());
}

#endif // ONE_PHASE_MERGE_SORT_H
