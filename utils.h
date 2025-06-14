#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <random>
#include <fstream>
#include <string>
#include "sorting_algorithms.h"
#include <functional>

// Generate random array
std::vector<int> generateRandomArray(int size);

// Generate ascending array
std::vector<int> generateAscendingArray(int size);

// Generate descending array
std::vector<int> generateDescendingArray(int size);

// Generate small array (few items)
std::vector<int> generateSmallArray(int size);

// Save results to CSV file
void saveResultsToCSV(const std::string& filename, 
                     const std::vector<int>& sizes,
                     const std::vector<double>& insertionTimes,
                     const std::vector<double>& quickTimes,
                     const std::vector<double>& mergeTimes,
                     const std::vector<long long>& insertionOps,
                     const std::vector<long long>& quickOps,
                     const std::vector<long long>& mergeOps);

// Run sorting tests for a specific array type
void runSortingTests(const std::string& arrayType,
                    const std::vector<int>& sizes,
                    std::vector<double>& insertionTimes,
                    std::vector<double>& quickTimes,
                    std::vector<double>& mergeTimes,
                    std::vector<long long>& insertionOps,
                    std::vector<long long>& quickOps,
                    std::vector<long long>& mergeOps);

// Function to test sorting algorithms
void testSortingAlgorithms(const std::vector<int>& sizes,
                          std::function<std::vector<int>(int)> arrayGenerator,
                          const std::string& outputFile);

#endif // UTILS_H 