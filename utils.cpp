#include "utils.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

std::vector<int> generateAscendingArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

std::vector<int> generateDescendingArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    return arr;
}

std::vector<int> generateSmallArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

void saveResultsToCSV(const std::string& filename,
                     const std::vector<int>& sizes,
                     const std::vector<double>& insertionTimes,
                     const std::vector<double>& quickTimes,
                     const std::vector<double>& mergeTimes,
                     const std::vector<long long>& insertionOps,
                     const std::vector<long long>& quickOps,
                     const std::vector<long long>& mergeOps) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write header
    file << "Size,InsertionSort Time (ms),QuickSort Time (ms),MergeSort Time (ms),"
         << "InsertionSort Ops,QuickSort Ops,MergeSort Ops\n";

    // Write data
    for (size_t i = 0; i < sizes.size(); i++) {
        file << sizes[i] << ","
             << insertionTimes[i] << ","
             << quickTimes[i] << ","
             << mergeTimes[i] << ","
             << insertionOps[i] << ","
             << quickOps[i] << ","
             << mergeOps[i] << "\n";
    }

    file.close();
}

void runSortingTests(const std::string& arrayType,
                    const std::vector<int>& sizes,
                    std::vector<double>& insertionTimes,
                    std::vector<double>& quickTimes,
                    std::vector<double>& mergeTimes,
                    std::vector<long long>& insertionOps,
                    std::vector<long long>& quickOps,
                    std::vector<long long>& mergeOps) {
    
    for (size_t i = 0; i < sizes.size(); i++) {
        std::vector<int> arr;
        
        // Generate appropriate array type
        if (arrayType == "random") {
            arr = generateRandomArray(sizes[i]);
        } else if (arrayType == "ascending") {
            arr = generateAscendingArray(sizes[i]);
        } else if (arrayType == "descending") {
            arr = generateDescendingArray(sizes[i]);
        } else if (arrayType == "small") {
            arr = generateSmallArray(sizes[i]);
        }

        // Test Insertion Sort
        std::vector<int> arr1 = arr;
        SortingStats insertionStats = insertionSort(arr1);
        insertionTimes[i] = insertionStats.time_ms;
        insertionOps[i] = insertionStats.comparisons + insertionStats.swaps;

        // Test Quick Sort
        std::vector<int> arr2 = arr;
        SortingStats quickStats = quickSort(arr2);
        quickTimes[i] = quickStats.time_ms;
        quickOps[i] = quickStats.comparisons + quickStats.swaps;

        // Test Merge Sort
        std::vector<int> arr3 = arr;
        SortingStats mergeStats = mergeSort(arr3);
        mergeTimes[i] = mergeStats.time_ms;
        mergeOps[i] = mergeStats.comparisons + mergeStats.swaps;

        std::cout << "Completed size " << sizes[i] << " for " << arrayType << " arrays\n";
    }
} 