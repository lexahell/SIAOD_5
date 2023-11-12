#pragma once
#include "Record.h"
class BinarySearchTree {
    struct Node {
        RecordKey record;
        Node* left;
        Node* right;
        Node(unsigned int key, int offset);
        ~Node();
    };
    Node* root = nullptr;
public:
    void addNode(unsigned int key, int offset);
    int findNode(unsigned int key);
    Node* findMin(Node* node);
    Node* deleteNode(Node* root, unsigned int key, int& offset);
    void printTree(Node* root, int level = 0, const std::string& prefix = "Root: ");
    Node* getRoot();
    void setRoot(Node* root);
    ~BinarySearchTree();
};