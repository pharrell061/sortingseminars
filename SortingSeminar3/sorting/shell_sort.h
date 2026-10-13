#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include <vector>

// Shell sort: generalizes insertion sort by first sorting elements
// that are 'gap' apart, shrinking the gap each round (here using the
// classic gap sequence n/2, n/4, ..., 1) until a final gap-1 pass
// performs a nearly-sorted, cheap insertion sort.
template <typename T>
void shellSort(std::vector<T>& arr) {
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            T temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

#endif // SHELL_SORT_H
