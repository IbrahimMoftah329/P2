#include "myVector.hpp"

void vectorMedian(const std::vector<int>* instructions) {
    if (instructions == nullptr) {
        std::cerr << "Invalid instructions pointer." << std::endl;
        return;
    }

    std::vector<int> sortedVector;
    std::vector<int> medians; // Vector to store medians

    const auto t1_start = std::chrono::steady_clock::now();

    for (int instruction : *instructions) {
        if (instruction == -1) {
            if (sortedVector.empty()) {
                std::cout << "No elements in the vector." << std::endl;
            } else {
                int median;
                if (sortedVector.size() % 2 == 0) {
                    // Even number of elements, median is lesser of the two middle elements
                    int mid1 = sortedVector[sortedVector.size() / 2 - 1];
                    int mid2 = sortedVector[sortedVector.size() / 2];
                    median = std::min(mid1, mid2);
                } else {
                    // Odd number of elements, median is middle element
                    median = sortedVector[sortedVector.size() / 2];
                }
                medians.push_back(median);
                
                // Remove median from sortedVec
                sortedVector.erase(std::find(sortedVector.begin(), sortedVector.end(), median));
            }
        } else {
            sortedVector.insert(std::upper_bound(sortedVector.begin(), sortedVector.end(), instruction), instruction);
        }
    }

    const auto t1_end = std::chrono::steady_clock::now();
    int t1 = std::chrono::duration <double, std::micro> (t1_end - t1_start).count();
    std::cout << "Vector method completed in " << t1 << " microseconds." << std::endl;

    // Print the medians
    for (int median : medians) {
        std::cout << median << " ";
    }
}