#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <chrono>

// Structure to hold sorting statistics
struct SortingStats {
    long long comparisons;
    long long swaps;
    double time_ms;
};

// Insertion Sort
template<typename T>
SortingStats insertionSort(std::vector<T>& arr);

// Quick Sort
template<typename T>
SortingStats quickSort(std::vector<T>& arr);

// Merge Sort
template<typename T>
SortingStats mergeSort(std::vector<T>& arr);

// Helper functions
template<typename T>
void quickSortHelper(std::vector<T>& arr, int low, int high, SortingStats& stats);

template<typename T>
int partition(std::vector<T>& arr, int low, int high, SortingStats& stats);

template<typename T>
void mergeSortHelper(std::vector<T>& arr, int left, int right, SortingStats& stats);

template<typename T>
void merge(std::vector<T>& arr, int left, int mid, int right, SortingStats& stats);

#endif // SORTING_ALGORITHMS_H 