#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#include <vector>
#include <algorithm>

// Selection sort: repeatedly finds the minimum of the unsorted
// suffix and swaps it into place.
template <typename T>
void selectionSort(std::vector<T>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) std::swap(arr[i], arr[minIdx]);
    }
}

#endif // SELECTION_SORT_H
