#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <vector>
#include <algorithm>

template <typename T>
long partition(std::vector<T>& arr, long low, long high) {
    T pivot = arr[high];
    long i = low - 1;
    for (long j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSortRange(std::vector<T>& arr, long low, long high) {
    if (low < high) {
        long p = partition(arr, low, high);
        quickSortRange(arr, low, p - 1);
        quickSortRange(arr, p + 1, high);
    }
}

// Quick sort: recursively partitions around a pivot (last element)
// so everything smaller ends up left of it and everything larger
// ends up right of it, then recurses on both halves.
template <typename T>
void quickSort(std::vector<T>& arr) {
    if (!arr.empty()) {
        quickSortRange(arr, 0, static_cast<long>(arr.size()) - 1);
    }
}

#endif // QUICK_SORT_H
