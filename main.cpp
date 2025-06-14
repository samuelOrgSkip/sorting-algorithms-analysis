#include <iostream>
#include <vector>
#include <string>
#include "utils.h"

int main() {
    // Define array sizes to test
    std::vector<int> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    
    // Arrays to store results
    std::vector<double> insertionTimes(sizes.size());
    std::vector<double> quickTimes(sizes.size());
    std::vector<double> mergeTimes(sizes.size());
    std::vector<long long> insertionOps(sizes.size());
    std::vector<long long> quickOps(sizes.size());
    std::vector<long long> mergeOps(sizes.size());

    // Test cases
    std::vector<std::string> testCases = {"random", "ascending", "descending", "small"};

    for (const auto& testCase : testCases) {
        std::cout << "\nRunning tests for " << testCase << " arrays...\n";
        
        // Run tests for current case
        runSortingTests(testCase, sizes,
                       insertionTimes, quickTimes, mergeTimes,
                       insertionOps, quickOps, mergeOps);

        // Save results to CSV
        std::string filename = testCase + "_results.csv";
        saveResultsToCSV(filename, sizes,
                        insertionTimes, quickTimes, mergeTimes,
                        insertionOps, quickOps, mergeOps);
        
        std::cout << "Results saved to " << filename << "\n";
    }

    std::cout << "\nAll tests completed. Results have been saved to CSV files.\n";
    std::cout << "You can now use these CSV files to generate graphs and analyze the results.\n";

    return 0;
} 