Project: ADT Implementation and Performance Comparison

Objective
In this project, you will implement an Abstract Data Type (ADT) with two operations: insert and pop_median. The ADT will be implemented in four different ways, and their performance will be compared.

Implementation Methods
Sorted Vector: Using a vector that is kept sorted.
Sorted Linked List: Using a linked list that is kept sorted.
Heaps: Using a max heap for elements less than or equal to the median and a min heap for elements greater than the median.
AVL Trees: Using two AVL trees, one for elements less than or equal to the median and one for elements greater than the median. AVL trees must support duplicate values.

Operations
Insert: Adds an element to the data structure.
Pop Median: Removes and returns the median of the current elements. For an even number of elements, the median is the lesser of the two middle elements.

Input and Output Format
Input instructions will follow the format shown in testinput_in_integer_format.txt.
Each method should output a list of medians as shown in testinput_medians.txt.

Implementation Details
For the vector and linked list, you will keep them sorted by inserting elements into their correct positions.
For the heaps, maintain balance by ensuring the max heap (holding elements <= median) and the min heap (holding elements > median) are appropriately sized.
For the AVL trees, one tree will hold elements <= median, and the other will hold elements > median.

Main Function (main.cpp)
Reading Input: Read the input file and convert it to an integer vector.
insert X operations push X to the back of the vector.
pop median operations push -1 to the back of the vector.
Testing: Pass the integer vector to each of your four methods for median tracking.
Output: Each method should output the medians after all operations have been processed.

Performance Timing
Time the main loop of each method.
Store the medians in a vector during processing.
Print the vector of medians after timing stops to avoid I/O operation delays affecting performance measurements.

Implementation Tips
For vectors and linked lists, use lower_bound or upper_bound for efficient insertion in a sorted manner.
For heaps, maintain two containers (max heap for smaller elements and min heap for larger elements) and rebalance as necessary.
Implement the AVL trees manually, as STL does not provide AVL trees. Ensure they handle duplicates and follow the median distribution rules.
