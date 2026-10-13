#include "catch.hpp"
#include "natural_merge_sort.h"
#include <vector>
#include <fstream>
#include <cstdio>

static void writeInputFile(const std::string& path, const std::vector<int>& values) {
    std::ofstream out(path);
    for (int v : values) out << v << "\n";
}

static std::vector<int> readOutputFile(const std::string& path) {
    std::ifstream in(path);
    std::vector<int> values;
    int v;
    while (in >> v) values.push_back(v);
    return values;
}

TEST_CASE("naturalMergeSort: empty file stays empty", "[natural_merge_sort]") {
    std::string in = "natural_merge_sort_in1.tmp", out = "natural_merge_sort_out1.tmp";
    writeInputFile(in, {});
    naturalMergeSort<int>(in, out);
    REQUIRE(readOutputFile(out).empty());
    std::remove(in.c_str()); std::remove(out.c_str());
}

TEST_CASE("naturalMergeSort: single-element file is unchanged", "[natural_merge_sort]") {
    std::string in = "natural_merge_sort_in2.tmp", out = "natural_merge_sort_out2.tmp";
    writeInputFile(in, {7});
    naturalMergeSort<int>(in, out);
    REQUIRE(readOutputFile(out) == std::vector<int>{7});
    std::remove(in.c_str()); std::remove(out.c_str());
}

TEST_CASE("naturalMergeSort: already-sorted file stays sorted", "[natural_merge_sort]") {
    std::string in = "natural_merge_sort_in3.tmp", out = "natural_merge_sort_out3.tmp";
    writeInputFile(in, {1, 2, 3, 4, 5});
    naturalMergeSort<int>(in, out);
    REQUIRE(readOutputFile(out) == std::vector<int>{1, 2, 3, 4, 5});
    std::remove(in.c_str()); std::remove(out.c_str());
}

TEST_CASE("naturalMergeSort: reverse-sorted file is sorted correctly", "[natural_merge_sort]") {
    std::string in = "natural_merge_sort_in4.tmp", out = "natural_merge_sort_out4.tmp";
    writeInputFile(in, {5, 4, 3, 2, 1});
    naturalMergeSort<int>(in, out);
    REQUIRE(readOutputFile(out) == std::vector<int>{1, 2, 3, 4, 5});
    std::remove(in.c_str()); std::remove(out.c_str());
}

TEST_CASE("naturalMergeSort: larger unsorted file with duplicates", "[natural_merge_sort]") {
    std::string in = "natural_merge_sort_in5.tmp", out = "natural_merge_sort_out5.tmp";
    writeInputFile(in, {9, 3, 7, 3, 1, 8, 2, 2, 6, 5});
    naturalMergeSort<int>(in, out);
    REQUIRE(readOutputFile(out) == std::vector<int>{1, 2, 2, 3, 3, 5, 6, 7, 8, 9});
    std::remove(in.c_str()); std::remove(out.c_str());
}
