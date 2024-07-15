#ifndef MYHEAP_HPP
#define MYHEAP_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>

/**
 * Function to calculate median of a heap
 * It takes a vector of instructions as input, where -1 indicates median calculation and other integers represent elements to be inserted
 * print the calculated medians.
 */
void heapMedian(const std::vector<int>* instructions);

#endif
