/*
CSCI335 Spring 2024
Project 2
Ibrahim Moftah
*/

#include "myAVLtree.hpp"

// Default constructor
AvlTree::AvlTree( ) : root{nullptr} { 
}

// Copy constructor
AvlTree::AvlTree(const AvlTree& rhs) : root{nullptr} {
    root = clone(rhs.root);
}

// Move constructor
AvlTree::AvlTree(AvlTree&& rhs) : root{rhs.root} {
    rhs.root = nullptr;
}

// Destructor
AvlTree::~AvlTree( ) {
    makeEmpty( );
}

/**
 * Deep copy.
 */
AvlTree &AvlTree::operator=(const AvlTree &rhs) {
    AvlTree copy = rhs;
    std::swap(*this, copy);
    return *this;
}
    
/**
 * Move.
 */
AvlTree &AvlTree::operator=(AvlTree &&rhs) {
    std::swap(root, rhs.root);
    
    return *this;
}

/**
 * Find the smallest item in the tree.
 * Throw UnderflowException if empty.
 */
const int& AvlTree::findMin( ) const {
    if (isEmpty())
    {
        static const int default_value = -1; // Default value to return
        return default_value;
    }
    return findMin(root)->element;
}

/**
 * Find the largest item in the tree.
 * Throw UnderflowException if empty.
 */
const int& AvlTree::findMax( ) const {
    if (isEmpty())
    {
        static const int default_value = -1; // Default value to return
        return default_value;
    }
    return findMax(root)->element;
}

/**
 * Returns true if x is found in the tree.
 */
bool AvlTree::contains(const int & x) const {
    return contains(x, root);
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
bool AvlTree::isEmpty( ) const {
    return root == nullptr;
}

/**
 * Print the tree contents in sorted order.
 */
void AvlTree::printTree( ) const {
    if( isEmpty( ) )
        std::cout << "Empty tree" << std::endl;
    else
        printTree(root);
}

/**
 * Make the tree logically empty.
 */
void AvlTree::makeEmpty( ) {
    makeEmpty(root);
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
void AvlTree::insert( const int & x ) {
    insert(x, root);
}
    
/**
 * Insert x into the tree; duplicates are ignored.
 */
void AvlTree::insert(int && x) {
    insert(std::move( x ), root);
}
    
/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
void AvlTree::remove(const int & x) {
    remove(x, root);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void AvlTree::insert(const int & x, AvlNode * & t) {
    if(t == nullptr)
        t = new AvlNode{x, nullptr, nullptr};
    else if(x < t->element)
        insert(x, t->left);
    else if(t->element < x)
        insert(x, t->right);
    
    balance( t );
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void AvlTree::insert(int&& x, AvlNode* &t) {
    if(t == nullptr)
        t = new AvlNode{std::move(x), nullptr, nullptr};
    else if(x < t->element)
        insert(std::move(x), t->left);
    else if(t->element < x)
        insert(std::move(x), t->right);
    
    balance(t);
}
    
/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void AvlTree::remove(const int& x, AvlNode* &t) {
    if(t == nullptr)
        return;   // Item not found; do nothing
    
    if(x < t->element)
        remove(x, t->left);
    else if(t->element < x)
        remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr) // Two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        AvlNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
    
    balance(t);
}

// Assume t is balanced or within one of being balanced
void AvlTree::balance(AvlNode* &t) {
    if(t == nullptr)
        return;
    
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
        if(height(t->left->left) >= height(t->left->right)) {
            rotateWithLeftChild(t);
        } else {
            doubleWithLeftChild(t);
        }
    } else {
        if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            if(height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }
    }        
    t->height = max(height(t->left), height(t->right)) + 1;
}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
AvlTree::AvlNode* AvlTree::findMin(AvlNode *t) const {
    if(t == nullptr)
        return nullptr;
    if(t->left == nullptr)
        return t;
    return findMin(t->left);
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
AvlTree::AvlNode* AvlTree::findMax(AvlNode *t) const {
    if(t != nullptr)
        while(t->right != nullptr)
            t = t->right;
    return t;
}


/**
 * Internal method to test if an item is in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 */
bool AvlTree::contains(const int &x, AvlNode *t) const {
    if(t == nullptr)
        return false;
    else if(x < t->element)
        return contains(x, t->left);
    else if(t->element < x)
        return contains(x, t->right);
    else
        return true;    // Match
}

/****** NONRECURSIVE VERSION*************************
bool contains( const Comparable & x, AvlNode *t ) const
{
    while( t != nullptr )
        if( x < t->element )
            t = t->left;
        else if( t->element < x )
            t = t->right;
        else
            return true;    // Match

    return false;   // No match
}
*****************************************************/

/**
 * Internal method to make subtree empty.
 */
void AvlTree::makeEmpty(AvlNode* &t) {
    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
void AvlTree::printTree(AvlNode *t) const {
    if(t != nullptr)
    {
        printTree(t->left);
        std::cout << t->element << std::endl;
        printTree(t->right);
    }
}

/**
 * Internal method to clone subtree.
 */
AvlTree::AvlNode* AvlTree::clone(AvlNode *t) const {
    if(t == nullptr)
        return nullptr;
    else
        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
}

// Avl manipulations

/**
 * Return the height of node t or -1 if nullptr.
 */
int AvlTree::height(AvlNode *t) const {
    return t == nullptr ? -1 : t->height;
}

int AvlTree::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

/**
 * Rotate binary tree node with left child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
void AvlTree::rotateWithLeftChild(AvlNode* &k2) {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 4.
 * Update heights, then set new root.
 */
void AvlTree::rotateWithRightChild(AvlNode* &k1) {
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

/**
 * Double rotate binary tree node: first left child.
 * with its right child; then node k3 with new left child.
 * For AVL trees, this is a double rotation for case 2.
 * Update heights, then set new root.
 */
void AvlTree::doubleWithLeftChild(AvlNode* &k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

/**
 * Double rotate binary tree node: first right child.
 * with its left child; then node k1 with new right child.
 * For AVL trees, this is a double rotation for case 3.
 * Update heights, then set new root.
 */
void AvlTree::doubleWithRightChild(AvlNode* &k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

// Function to find the number of elements in a subtree rooted at t
int AvlTree::countElements(AvlNode *t) const {
    if (t == nullptr)
        return 0;
    else
        return 1 + countElements(t->left) + countElements(t->right);
}

// Function to get the number of elements in the AVL tree
int AvlTree::size() const {
    return countElements(root);
}


/**
 * Function to calculate median of a AVL tree
 * It takes a vector of instructions as input, where -1 indicates median calculation and other integers represent elements to be inserted
 * print the calculated medians.
 */
void treeMedian(const std::vector<int>* instructions) {
    if (instructions == nullptr) {
        std::cerr << "Invalid instructions pointer." << std::endl;
        return;
    }

    AvlTree small; // AVL tree for elements less than or equal to the median
    AvlTree large; // AVL tree for elements greater than the median
    std::vector<int> medians; // Vector to store medians

    const auto t1_start = std::chrono::steady_clock::now();

    for (int instruction : *instructions) {
        if (instruction == -1) {
            if (small.isEmpty()) {
                std::cout << "No elements in the list." << std::endl;
            } else {
                int median = small.findMax();
                medians.push_back(median);
                small.remove(median);

                if (small.size() < large.size()) {
                    int min = large.findMin();
                    large.remove(min);
                    small.insert(min);
                } 
                
            }
        } else {
            if (small.isEmpty() || instruction <= small.findMax()) {
                small.insert(instruction);
            } else {
                large.insert(instruction);
            }

            // Rebalance the containers if necessary
            if (small.size() < large.size()) {
                int min = large.findMin();
                large.remove(min);
                small.insert(min);
            } else if (small.size() > large.size() + 1) {
                int max = small.findMax();
                small.remove(max);
                large.insert(max);
            }
        }
    }

    const auto t1_end = std::chrono::steady_clock::now();
    int t1 = std::chrono::duration <double, std::micro> (t1_end - t1_start).count();
    std::cout << "AVL tree method completed in " << t1 << " microseconds." << std::endl;

    // Print the medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}