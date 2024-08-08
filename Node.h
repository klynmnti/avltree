#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
using namespace std;
#pragma once

struct Node {
    Node(const string& entry);
    Node* left;
    Node* right;
    Node* parent;
    string key;
    int height;
};

#endif