/*
CSCI335 Spring 2024
Project 2
Ibrahim Moftah
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "myVector.hpp"
#include "myList.hpp"
#include "myHeap.hpp"
#include "myAVLtree.hpp"

// Function to parse input line and return instruction as integer
int parseInstruction(const std::string& line) {
    if (line.find("insert") != std::string::npos) {
        std::istringstream iss(line);
        std::string command;
        int value;
        iss >> command >> value;
        return value;
    } else if (line.find("pop") != std::string::npos) {
        return -1;
    } else {
        // Handle invalid instruction
        return 0;
    }
}

int main() {
    // Open input file
    std::ifstream inputFile("input1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::vector<int> instructions;

    // Read input file line by line
    std::string line;
    while (std::getline(inputFile, line)) {
        // Parse instruction and convert to integer
        int instruction = parseInstruction(line);
        // Store the instruction in the vector
        instructions.push_back(instruction);
    }

    // // Output all the integers stored in the vector
    // std::cout << "Instructions in the vector:" << std::endl;
    // for (std::vector<int>::size_type i = 0; i < instructions.size(); ++i) {
    //     std::cout << instructions[i] << " ";
    // }

    // Now you have the instructions stored in 'instructions' vector
    // You can pass this vector to your median-tracking methods for testing

    vectorMedian(&instructions);
    listMedian(&instructions);
    heapMedian(&instructions);
    treeMedian(&instructions);
    

    // Close the input file
    inputFile.close();

    return 0;
}
