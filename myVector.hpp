/*
Author: Ibrahim Moftah
*/

#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

/**
 * Function to calculate median of a vector
 * It takes a vector of instructions as input, where -1 indicates median calculation and other integers represent elements to be inserted
 * print the calculated medians.
 */
void vectorMedian(const std::vector<int>* instructions);

#endif
