#ifndef EXCHANGE_SORT_H
#define EXCHANGE_SORT_H
#include <vector>
#include <algorithm>

// Exchange sort: compares every pair (i, j) with j > i and swaps
// whenever they are out of order. O(n^2) comparisons, no early exit.
template <typename T>
void exchangeSort(std::vector<T>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[i]) std::swap(arr[i], arr[j]);
        }
    }
}

#endif // EXCHANGE_SORT_H
