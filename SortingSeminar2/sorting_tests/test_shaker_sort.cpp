#include "catch.hpp"
#include "shaker_sort.h"
#include <vector>

TEST_CASE("shakerSort: empty array stays empty", "[shaker_sort]") {
    std::vector<int> v;
    shakerSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("shakerSort: single element array is unchanged", "[shaker_sort]") {
    std::vector<int> v{42};
    shakerSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("shakerSort: already sorted array stays sorted", "[shaker_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    shakerSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shakerSort: reverse sorted array is sorted correctly", "[shaker_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    shakerSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shakerSort: array with duplicates sorts correctly", "[shaker_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    shakerSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("shakerSort: works with doubles", "[shaker_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    shakerSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
