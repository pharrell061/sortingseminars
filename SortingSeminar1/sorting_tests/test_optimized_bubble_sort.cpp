#include "catch.hpp"
#include "optimized_bubble_sort.h"
#include <vector>

TEST_CASE("optimizedBubbleSort: empty array stays empty", "[optimized_bubble_sort]") {
    std::vector<int> v;
    optimizedBubbleSort(v);
    REQUIRE(v.empty());
}

TEST_CASE("optimizedBubbleSort: single element array is unchanged", "[optimized_bubble_sort]") {
    std::vector<int> v{42};
    optimizedBubbleSort(v);
    REQUIRE(v == std::vector<int>{42});
}

TEST_CASE("optimizedBubbleSort: already sorted array stays sorted", "[optimized_bubble_sort]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    optimizedBubbleSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("optimizedBubbleSort: reverse sorted array is sorted correctly", "[optimized_bubble_sort]") {
    std::vector<int> v{5, 4, 3, 2, 1};
    optimizedBubbleSort(v);
    REQUIRE(v == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("optimizedBubbleSort: array with duplicates sorts correctly", "[optimized_bubble_sort]") {
    std::vector<int> v{3, 1, 3, 2, 1};
    optimizedBubbleSort(v);
    REQUIRE(v == std::vector<int>{1, 1, 2, 3, 3});
}

TEST_CASE("optimizedBubbleSort: works with doubles", "[optimized_bubble_sort]") {
    std::vector<double> v{2.5, 0.1, -3.7, 1.0};
    optimizedBubbleSort(v);
    REQUIRE(v == std::vector<double>{-3.7, 0.1, 1.0, 2.5});
}
