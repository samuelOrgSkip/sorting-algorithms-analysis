#include "utils.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>

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

void testSortingAlgorithms(const std::vector<int>& sizes,
                          std::function<std::vector<int>(int)> arrayGenerator,
                          const std::string& outputFile) {
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << outputFile << std::endl;
        return;
    }

    // Write header
    outFile << "Size,Insertion Sort Time,Quick Sort Time,Merge Sort Time,"
            << "Insertion Sort Operations,Quick Sort Operations,Merge Sort Operations\n";

    for (int size : sizes) {
        std::vector<int> arr = arrayGenerator(size);
        std::vector<int> arrCopy = arr;

        // Test Insertion Sort
        auto start = std::chrono::high_resolution_clock::now();
        SortingStats insertionStats = insertionSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        double insertionTime = std::chrono::duration<double, std::milli>(end - start).count();

        // Test Quick Sort
        arr = arrCopy;
        start = std::chrono::high_resolution_clock::now();
        SortingStats quickStats = quickSort(arr);
        end = std::chrono::high_resolution_clock::now();
        double quickTime = std::chrono::duration<double, std::milli>(end - start).count();

        // Test Merge Sort
        arr = arrCopy;
        start = std::chrono::high_resolution_clock::now();
        SortingStats mergeStats = mergeSort(arr);
        end = std::chrono::high_resolution_clock::now();
        double mergeTime = std::chrono::duration<double, std::milli>(end - start).count();

        // Write results
        outFile << size << ","
                << insertionTime << ","
                << quickTime << ","
                << mergeTime << ","
                << (insertionStats.comparisons + insertionStats.swaps) << ","
                << (quickStats.comparisons + quickStats.swaps) << ","
                << (mergeStats.comparisons + mergeStats.swaps) << "\n";
    }

    outFile.close();
} 