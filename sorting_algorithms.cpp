#include "sorting_algorithms.h"
#include <algorithm>
#include <chrono>

template<typename T>
SortingStats insertionSort(std::vector<T>& arr) {
    SortingStats stats = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < arr.size(); i++) {
        T key = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            stats.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }

    auto end = std::chrono::high_resolution_clock::now();
    stats.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    return stats;
}

template<typename T>
SortingStats quickSort(std::vector<T>& arr) {
    SortingStats stats = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    quickSortHelper(arr, 0, arr.size() - 1, stats);

    auto end = std::chrono::high_resolution_clock::now();
    stats.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    return stats;
}

template<typename T>
void quickSortHelper(std::vector<T>& arr, int low, int high, SortingStats& stats) {
    if (low < high) {
        int pi = partition(arr, low, high, stats);
        quickSortHelper(arr, low, pi - 1, stats);
        quickSortHelper(arr, pi + 1, high, stats);
    }
}

template<typename T>
int partition(std::vector<T>& arr, int low, int high, SortingStats& stats) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats.comparisons++;
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            stats.swaps++;
        }
    }
    std::swap(arr[i + 1], arr[high]);
    stats.swaps++;
    return i + 1;
}

template<typename T>
SortingStats mergeSort(std::vector<T>& arr) {
    SortingStats stats = {0, 0, 0.0};
    auto start = std::chrono::high_resolution_clock::now();

    mergeSortHelper(arr, 0, arr.size() - 1, stats);

    auto end = std::chrono::high_resolution_clock::now();
    stats.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    return stats;
}

template<typename T>
void mergeSortHelper(std::vector<T>& arr, int left, int right, SortingStats& stats) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, stats);
        mergeSortHelper(arr, mid + 1, right, stats);
        merge(arr, left, mid, right, stats);
    }
}

template<typename T>
void merge(std::vector<T>& arr, int left, int mid, int right, SortingStats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        stats.comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        stats.swaps++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        stats.swaps++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        stats.swaps++;
    }
}

// Explicit template instantiations
template SortingStats insertionSort<int>(std::vector<int>&);
template SortingStats quickSort<int>(std::vector<int>&);
template SortingStats mergeSort<int>(std::vector<int>&); 