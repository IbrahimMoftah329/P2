/*
CSCI335 Spring 2024
Project 2
Ibrahim Moftah
*/

#include "myHeap.hpp"

/**
 * Function to calculate median of a heap
 * It takes a vector of instructions as input, where -1 indicates median calculation and other integers represent elements to be inserted
 * print the calculated medians.
 */
void heapMedian(const std::vector<int>* instructions) {
    if (instructions == nullptr) {
        std::cerr << "Invalid instructions pointer." << std::endl;
        return;
    }

    std::priority_queue<int> small; // Holds values less than or equal to the median
    std::priority_queue<int, std::vector<int>, std::greater<int>> large; // Holds values greater than the median
    std::vector<int> medians; // Vector to store medians

    const auto t1_start = std::chrono::steady_clock::now();

    for (int instruction : *instructions) {
        if (instruction == -1) {
            if (small.empty()) {
                std::cout << "No elements in the Heap." << std::endl;
            } else {
                int median = small.top();
                medians.push_back(median);
                small.pop();

                if (small.size() < large.size()) {
                    small.push(large.top());
                    large.pop();
                }

            }
        } else {
            if (small.empty() || instruction <= small.top()) {
                small.push(instruction);
            } else {
                large.push(instruction);
            }

            // Rebalance if necessary
            if (small.size() < large.size()) {
                small.push(large.top());
                large.pop();
            } else if (small.size() > large.size() + 1) {
                large.push(small.top());
                small.pop();
            }
        }
    }

    const auto t1_end = std::chrono::steady_clock::now();
    int t1 = std::chrono::duration_cast<std::chrono::microseconds>(t1_end - t1_start).count();
    // std::cout << "Priority Queue method completed in " << t1 << " microseconds." << std::endl;

    // Print the medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
