#include "catch.hpp"
#include "quick_sort.h"
#include <vector>

TEST_CASE("quickSort: empty array stays empty", "[quick_sort]") {
    std::vector<int> v;
    quickSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("quickSort: single element array is unchanged", "[quick_sort]") {
    std::vector<int> v{42};
    quickSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("quickSort: already sorted array stays sorted", "[quick_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    quickSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("quickSort: reverse sorted array is sorted correctly", "[quick_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    quickSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("quickSort: array with duplicates sorts correctly", "[quick_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    quickSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("quickSort: works with doubles", "[quick_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    quickSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
