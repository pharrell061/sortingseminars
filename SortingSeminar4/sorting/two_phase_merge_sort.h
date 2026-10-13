#ifndef TWO_PHASE_MERGE_SORT_H
#define TWO_PHASE_MERGE_SORT_H
#include "external_merge_common.h"
#include <cstdio>

// Two-phase simple merge sort (external sort, run length starts at 1).
// Each iteration is explicitly two separate passes over the temp
// files: a MERGE phase (pairs of runs from fileA/fileB -> one merged
// file) followed by a DISTRIBUTE phase (that merged file's runs are
// re-split alternately back into fileA/fileB, doubling the run
// length). This repeats until only one run remains.
template <typename T>
void twoPhaseMergeSort(const std::string& inputFile, const std::string& outputFile) {
    const std::string fileA = "tp_a.tmp";
    const std::string fileB = "tp_b.tmp";
    const std::string merged = "tp_merged.tmp";

    // Bootstrap: initial runs of length 1.
    distributeInitialRuns<T>(inputFile, fileA, fileB);

    while (true) {
        // --- Merge phase ---
        std::ifstream inA(fileA), inB(fileB);
        std::ofstream out(merged);
        size_t runCount = 0;
        std::vector<T> runA, runB;
        bool haveA = readRun(inA, runA);
        bool haveB = readRun(inB, runB);

        while (haveA || haveB) {
            if (haveA && haveB) {
                writeRun(out, mergeTwoRuns(runA, runB));
            } else if (haveA) {
                writeRun(out, runA);
            } else {
                writeRun(out, runB);
            }
            ++runCount;
            haveA = readRun(inA, runA);
            haveB = readRun(inB, runB);
        }
        inA.close();
        inB.close();
        out.close();

        if (runCount <= 1) {
            copyFinalRun<T>(merged, outputFile);
            break;
        }

        // --- Distribute phase --- (preserves the just-merged run lengths)
        distributeRuns<T>(merged, fileA, fileB);
    }

    std::remove(fileA.c_str());
    std::remove(fileB.c_str());
    std::remove(merged.c_str());
}

#endif // TWO_PHASE_MERGE_SORT_H
