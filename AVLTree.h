#include "Node.h"

class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        int balanceFactor(Node* n) const;
        void printBalanceFactors() const;
        void insert(const string& word);
        //void visualizeTree(const string &outputFilename);
    private:
        Node* root;
        void updateHeight(Node* n);
        bool setChild(Node* parnode, string childname, Node* childnode);
        bool replaceChild(Node* parnode, Node* n, Node* childnode);
        Node* rotateRight(Node* n);
        Node* rotateLeft(Node* n);
        void recPrintFactors(Node* n) const;
        Node* rebalance(Node* n);
        //void visualizeTree(ofstream &outFS, Node* n);
        
};