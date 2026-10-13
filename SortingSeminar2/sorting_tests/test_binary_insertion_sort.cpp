#include "catch.hpp"
#include "binary_insertion_sort.h"
#include <vector>

TEST_CASE("binaryInsertionSort: empty array stays empty", "[binary_insertion_sort]") {
    std::vector<int> v;
    binaryInsertionSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("binaryInsertionSort: single element array is unchanged", "[binary_insertion_sort]") {
    std::vector<int> v{42};
    binaryInsertionSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("binaryInsertionSort: already sorted array stays sorted", "[binary_insertion_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    binaryInsertionSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("binaryInsertionSort: reverse sorted array is sorted correctly", "[binary_insertion_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    binaryInsertionSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("binaryInsertionSort: array with duplicates sorts correctly", "[binary_insertion_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    binaryInsertionSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("binaryInsertionSort: works with doubles", "[binary_insertion_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    binaryInsertionSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
