#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <vector>

// Classic insertion sort: shifts elements right within the sorted
// left-hand part of the array until it finds the correct slot.
template <typename T>
void insertionSort(std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        long j = static_cast<long>(i) - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

#endif // INSERTION_SORT_H
