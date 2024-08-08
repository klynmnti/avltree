#include "Node.h"
/* Constructor for Node */
// assigns node's key with the entry parameter and sets height + pointers to 0
Node::Node(const string& entry) {
    key = entry;
    height = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}