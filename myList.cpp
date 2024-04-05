#include "myList.hpp"

void listMedian(const std::vector<int>* instructions) {
    if (instructions == nullptr) {
        std::cerr << "Invalid instructions pointer." << std::endl;
        return;
    }

    std::list<int> sortedList;
    std::vector<int> medians; // Vector to store medians

    const auto t1_start = std::chrono::steady_clock::now();

    for (int instruction : *instructions) {
        if (instruction == -1) {
            if (sortedList.empty()) {
                std::cout << "No elements in the list." << std::endl;
            } else {
                int median;
                auto it = sortedList.begin();
                if (sortedList.size() % 2 == 0) {
                    // Even number of elements, median is lesser of the two middle elements
                    auto it1 = std::next(it, sortedList.size() / 2);
                    --it1;
                    auto it2 = std::next(it, sortedList.size() / 2);
                    median = std::min(*it1, *it2);
                    // Remove median from sortedList
                    sortedList.erase(it1);
                } else {
                    // Odd number of elements, median is middle element
                    std::advance(it, sortedList.size() / 2);
                    median = *it;
                    // Remove median from sortedList
                    sortedList.erase(it);
                }
                medians.push_back(median);
                
            }
        } else {
            auto it = sortedList.begin();
            while (it != sortedList.end() && *it < instruction) {
                ++it;
            }
            sortedList.insert(it, instruction);
        }
    }

    const auto t1_end = std::chrono::steady_clock::now();
    int t1 = std::chrono::duration <double, std::micro> (t1_end - t1_start).count();
    std::cout << "List method completed in " << t1 << " microseconds." << std::endl;

    // Print the medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}

