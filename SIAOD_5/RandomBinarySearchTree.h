#pragma once
#include "Record.h"
#include <iostream>
class RandomBinarySearchTree {
    struct Node {
        RecordKey record;
        Node* left;
        Node* right;
        int size = 1;
        Node(unsigned int key, int offset);
        ~Node();
    };
    Node* root = nullptr;
public:
    int countRotate = 0;
    void printTree(Node* root, int level = 0, const std::string& prefix = "Root: ");
    Node* getRoot();
    void setRoot(Node*);
    int findNode(unsigned int key);
    int getSize(Node* p);
    void fixSize(Node* p);
    Node* rotateRight(Node* p);
    Node* rotateLeft(Node* p);
    Node* insert(Node* root, unsigned int key, int offset);
    Node* insertRoot(Node* root, unsigned int key, int offset);
    Node* join(Node* p, Node* q);
    Node* remove(Node* p, int k, int& offset);
    ~RandomBinarySearchTree();
};