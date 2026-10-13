#include "catch.hpp"
#include "bubble_sort.h"
#include <vector>

TEST_CASE("bubbleSort: empty array stays empty", "[bubble_sort]") {
    std::vector<int> v;
    bubbleSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("bubbleSort: single element array is unchanged", "[bubble_sort]") {
    std::vector<int> v{42};
    bubbleSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("bubbleSort: already sorted array stays sorted", "[bubble_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    bubbleSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("bubbleSort: reverse sorted array is sorted correctly", "[bubble_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    bubbleSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("bubbleSort: array with duplicates sorts correctly", "[bubble_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    bubbleSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("bubbleSort: works with doubles", "[bubble_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    bubbleSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
