#ifndef NATURAL_MERGE_SORT_H
#define NATURAL_MERGE_SORT_H
#include "external_merge_common.h"
#include <cstdio>

// Natural merge sort (external sort). Identical merge/redistribute
// machinery to the one-phase merge sort, but the initial runs are
// the *natural* already-ascending runs found in the input rather
// than fixed runs of length 1. Data that is already partly sorted
// needs noticeably fewer merge passes as a result.
template <typename T>
void naturalMergeSort(const std::string& inputFile, const std::string& outputFile) {
    const std::string pair0[2] = {"nm_0a.tmp", "nm_0b.tmp"};
    const std::string pair1[2] = {"nm_1a.tmp", "nm_1b.tmp"};

    distributeNaturalRuns<T>(inputFile, pair0[0], pair0[1]); // <-- the only difference
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

        readFrom0 = !readFrom0;
    }

    std::remove(pair0[0].c_str()); std::remove(pair0[1].c_str());
    std::remove(pair1[0].c_str()); std::remove(pair1[1].c_str());
}

#endif // NATURAL_MERGE_SORT_H
