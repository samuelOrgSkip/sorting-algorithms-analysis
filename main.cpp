#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <random>
#include <algorithm>
#include <filesystem>
#include "utils.h"

int main() {
    // Create data directory if it doesn't exist
    std::filesystem::create_directory("data");

    // Test cases
    std::vector<int> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    
    // Random arrays
    std::cout << "Testing random arrays...\n";
    testSortingAlgorithms(sizes, generateRandomArray, "data/random_results.csv");
    
    // Ascending arrays
    std::cout << "Testing ascending arrays...\n";
    testSortingAlgorithms(sizes, generateAscendingArray, "data/ascending_results.csv");
    
    // Descending arrays
    std::cout << "Testing descending arrays...\n";
    testSortingAlgorithms(sizes, generateDescendingArray, "data/descending_results.csv");
    
    // Small arrays
    std::cout << "Testing small arrays...\n";
    std::vector<int> smallSizes = {10, 20, 30, 40, 50};
    testSortingAlgorithms(smallSizes, generateRandomArray, "data/small_results.csv");
    
    std::cout << "Testing completed. Results saved to CSV files in the data directory.\n";
    return 0;
} 