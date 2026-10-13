#ifndef OPTIMIZED_BUBBLE_SORT_H
#define OPTIMIZED_BUBBLE_SORT_H
#include <vector>
#include <algorithm>

// Optimized bubble sort: stops early once a full pass makes no
// swaps (array is already sorted) and shrinks the scanned range
// each pass since the tail is already in place.
template <typename T>
void optimizedBubbleSort(std::vector<T>& arr) {
    size_t n = arr.size();
    bool swapped = true;
    size_t end = n;
    while (swapped && end > 1) {
        swapped = false;
        for (size_t j = 0; j + 1 < end; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        --end;
    }
}

#endif // OPTIMIZED_BUBBLE_SORT_H
