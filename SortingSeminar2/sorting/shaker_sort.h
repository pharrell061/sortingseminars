#ifndef SHAKER_SORT_H
#define SHAKER_SORT_H
#include <vector>
#include <algorithm>

// Shaker sort (a.k.a. cocktail sort): bidirectional bubble sort.
// A forward pass bubbles the largest remaining element to the right,
// then a backward pass bubbles the smallest remaining element to the
// left. The scanned window shrinks from both ends each round.
template <typename T>
void shakerSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    long left = 0;
    long right = static_cast<long>(arr.size()) - 1;
    bool swapped = true;

    while (swapped && left < right) {
        swapped = false;

        // Forward pass: push the largest element to the right end.
        for (long i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        --right;

        if (!swapped) break;

        // Backward pass: push the smallest element to the left end.
        swapped = false;
        for (long i = right; i > left; --i) {
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++left;
    }
}

#endif // SHAKER_SORT_H
