#ifndef BINARY_INSERTION_SORT_H
#define BINARY_INSERTION_SORT_H
#include <vector>

// Insertion sort where the insertion position in the already-sorted
// left part is located with binary search instead of a linear scan.
// This cuts the number of comparisons from O(n) to O(log n) per
// element, though the shifting itself is still O(n).
template <typename T>
void binaryInsertionSort(std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];

        // Binary search for the first position in [0, i) where key belongs.
        long left = 0;
        long right = static_cast<long>(i);
        while (left < right) {
            long mid = left + (right - left) / 2;
            if (arr[mid] > key) right = mid;
            else left = mid + 1;
        }

        // Shift everything from 'left' to i-1 one slot to the right.
        for (long j = static_cast<long>(i); j > left; --j) {
            arr[j] = arr[j - 1];
        }
        arr[left] = key;
    }
}

#endif // BINARY_INSERTION_SORT_H
