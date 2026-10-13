#include "catch.hpp"
#include "selection_sort.h"
#include <vector>

TEST_CASE("selectionSort: empty array stays empty", "[selection_sort]") {
    std::vector<int> v;
    selectionSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("selectionSort: single element array is unchanged", "[selection_sort]") {
    std::vector<int> v{42};
    selectionSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("selectionSort: already sorted array stays sorted", "[selection_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    selectionSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("selectionSort: reverse sorted array is sorted correctly", "[selection_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    selectionSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("selectionSort: array with duplicates sorts correctly", "[selection_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    selectionSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("selectionSort: works with doubles", "[selection_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    selectionSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
