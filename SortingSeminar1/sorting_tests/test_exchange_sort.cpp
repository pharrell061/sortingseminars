#include "catch.hpp"
#include "exchange_sort.h"
#include <vector>

TEST_CASE("exchangeSort: empty array stays empty", "[exchange_sort]") {
    std::vector<int> v;
    exchangeSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("exchangeSort: single element array is unchanged", "[exchange_sort]") {
    std::vector<int> v{42};
    exchangeSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("exchangeSort: already sorted array stays sorted", "[exchange_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    exchangeSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("exchangeSort: reverse sorted array is sorted correctly", "[exchange_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    exchangeSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("exchangeSort: array with duplicates sorts correctly", "[exchange_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    exchangeSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("exchangeSort: works with doubles", "[exchange_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    exchangeSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
