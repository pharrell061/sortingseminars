#include "catch.hpp"
#include "insertion_sort.h"
#include <vector>

TEST_CASE("insertionSort: empty array stays empty", "[insertion_sort]") {
    std::vector<int> v;
    insertionSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("insertionSort: single element array is unchanged", "[insertion_sort]") {
    std::vector<int> v{42};
    insertionSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("insertionSort: already sorted array stays sorted", "[insertion_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    insertionSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("insertionSort: reverse sorted array is sorted correctly", "[insertion_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    insertionSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("insertionSort: array with duplicates sorts correctly", "[insertion_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    insertionSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("insertionSort: works with doubles", "[insertion_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    insertionSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
