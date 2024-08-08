#include "AVLTree.h"
/* Default Constructor */
// creates a new tree and sets root to null
AVLTree::AVLTree() {
    root = nullptr;
}
/* Destructor */
// deletes left + right subtrees and root
AVLTree::~AVLTree() {
    delete root->left;
    delete root->right;
    delete root;
}
/* Update Height Function */
// increments height and updates the node's height variable
void AVLTree::updateHeight(Node* n) {
    int lheight = -1;
    int rheight = -1;
    if (n->left != nullptr) { lheight = n->left->height; }
    if (n->right != nullptr) { rheight = n->right->height; }
    n->height = max(lheight, rheight) + 1;
}
/* Set Child Helper Function */
// takes two node parameters and a childname parameter
// sets the parent node's left/right pointer based on childname parameter
// then sets child pointer and updates height of parent node
bool AVLTree::setChild(Node* parnode, string childname, Node* childnode) {
    if (childname != "left" && childname != "right") { return false; }
    if (childname == "left") { parnode->left = childnode; }
    else { parnode->right = childnode; }
    if (childnode != nullptr) { childnode->parent = parnode; }
    updateHeight(parnode);
    return true;
}
/* Replace Child Helper Function */
// takes three node parameters
// sets the parent's node with the child node and adjusts pointers in setChild
// returns true if n was the parent node's child, false otherwise
bool AVLTree::replaceChild(Node* parnode, Node* n, Node* childnode) {
    if (parnode->left == n) { return setChild(parnode, "left", childnode); }
    else if (parnode->right == n) { return setChild(parnode, "right", childnode); }
    return false;
}
/* Rotate Right */
// finds the left right child of the node parameter
// uses replaceChild function to set node's parent to point to node's left
// sets n's left's child to n and sets n's left child as the its left right child
Node* AVLTree::rotateRight(Node* n) {
    Node* lrchild = n->left->right;
    if (n->parent != nullptr) { replaceChild(n->parent, n, n->left); }
    else {
        root = n->left;
        root->parent = nullptr;
    }
    setChild(n->left, "right", n);
    setChild(n, "left", lrchild);
    return n;
}
/* Rotate Left */
// finds the right left child of the node parameter
// uses replaceChild function to set node's parent to point to node's right
// sets n's right's child to n and sets n's right child to its right left child
Node* AVLTree::rotateLeft(Node* n) {
    Node* rlchild = n->right->left;
    if (n->parent != nullptr) { replaceChild(n->parent, n, n->right); }
    else {
        root = n->right;
        root->parent = nullptr;
    }
    setChild(n->right, "left", n);
    setChild(n, "right", rlchild);
    return n;
}
/* Recursive Print Factors Function */
// recursively prints left subtree, root, right subtree
void AVLTree::recPrintFactors(Node* n) const {
    if (n != nullptr) {
        recPrintFactors(n->left);
        cout << n->key << "(" << balanceFactor(n) << "), ";
        recPrintFactors(n->right);
    }
}
/* Rebalance Function */
// updates node's height and determines which rotation to use
// if node's subtree is right skewed, left rotation
// if node's subtree is left skewed, right rotation
// determines if double rotation is required
Node* AVLTree::rebalance(Node* n) {
    updateHeight(n);
    if (balanceFactor(n) == -2) {
        if (balanceFactor(n->right) == 1) { rotateRight(n->right); }
        return rotateLeft(n);
    }
    else if (balanceFactor(n) == 2) {
        if (balanceFactor(n->left) == -1) { rotateLeft(n->left); }
        return rotateRight(n);
    }
    return n;
}
/* BalanceFactor Function */ 
// calculates the node's balance factor by doing left height - right height
int AVLTree::balanceFactor(Node* n) const {
    int lheight = -1;
    if (n->left != nullptr) { lheight = n->left->height; }
    int rheight = -1;
    if (n->right != nullptr) { rheight = n->right->height; }
    return lheight - rheight;
}
/* Balance Factors */
// calls recursive print balance function
void AVLTree::printBalanceFactors() const {
    recPrintFactors(root);
    cout << endl;
}
/* Insert Function */
void AVLTree::insert(const string& word) {
    Node* n = root;
    // finds leaf node where new node should be inserted
    while (n != nullptr) {
        if (word < n->key) { n = n->left; }
        else if (word > n->key) { n = n->right; }
        else { return; }
    }
    // creates a new node with the word parameter
    Node* add = new Node(word);
    // if tree is empty, root becomes the new node
    if (root == nullptr) {
        root = add;
        add->parent = nullptr;
        return;
    }
    // otherwise if the tree has at least one node,
    // find the leaf node and insert the new node
    Node* curr = root;
    while (curr != nullptr) {
        if (add->key < curr->key) {
            if (curr->left == nullptr) {
                curr->left = add;
                add->parent = curr;
                curr = nullptr;
            }
            else { curr = curr->left; }
        }
        else {
            if (curr->right == nullptr) {
                curr->right = add;
                add->parent =  curr;
                curr = nullptr;
            }
            else { curr = curr->right; }
        }
    }
    add = add->parent;
    // rebalance the tree from the new node's parent upwards
    while (add != nullptr) {
        rebalance(add);
        add = add->parent;
    }
}

/*
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}*/
