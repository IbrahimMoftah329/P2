/*
Author: Ibrahim Moftah
*/

#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>

/**
 * Function to calculate median of a list
 * It takes a vector of instructions as input, where -1 indicates median calculation and other integers represent elements to be inserted
 * print the calculated medians.
 */
void listMedian(const std::vector<int>* instructions);

#endif
