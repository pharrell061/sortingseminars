#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include <vector>
#include <algorithm>

// Plain bubble sort: repeatedly walks the array swapping adjacent
// out-of-order elements, always doing a fixed number of passes.
template <typename T>
void bubbleSort(std::vector<T>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
    }
}

#endif // BUBBLE_SORT_H
