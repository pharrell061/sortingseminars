#include "catch.hpp"
#include "shell_sort.h"
#include <vector>

TEST_CASE("shellSort: empty array stays empty", "[shell_sort]") {
    std::vector<int> v;
    shellSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("shellSort: single element array is unchanged", "[shell_sort]") {
    std::vector<int> v{42};
    shellSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("shellSort: already sorted array stays sorted", "[shell_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    shellSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shellSort: reverse sorted array is sorted correctly", "[shell_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    shellSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shellSort: array with duplicates sorts correctly", "[shell_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    shellSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("shellSort: works with doubles", "[shell_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    shellSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
