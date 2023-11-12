#include "BinarySearchTree.h"


BinarySearchTree::Node::Node(unsigned int key, int offset) {
    record.key = key;
    record.offset = offset;
    left = nullptr;
    right = nullptr;
}
BinarySearchTree::Node::~Node() {
    delete left;
    delete right;
}

void BinarySearchTree::addNode(unsigned int key, int offset) {
    if (!root) {
        root = new Node(key, offset);
        return;
    }
    Node* cur = root;
    while (true) {
        if (cur->record.key > key) {
            if (!cur->left) {
                cur->left = new Node(key, offset);
                break;
            }
            else {
                cur = cur->left;
            }
        }
        else if (cur->record.key < key) {
            if (!cur->right) {
                cur->right = new Node(key, offset);
                break;
            }
            else {
                cur = cur->right;
            }
        }
        else {
            break;
        }
    }
    return;
}

int BinarySearchTree::findNode(unsigned int key) {
    if (!root) {
        return -1;
    }
    Node* cur = root;
    while (true) {
        if (cur->record.key == key) {
            return cur->record.offset;
        }
        else if (cur->record.key > key) {
            if (!cur->left) {
                return -1;
            }
            else {
                cur = cur->left;
            }
        }
        else if (cur->record.key < key) {
            if (!cur->right) {
                return -1;
            }
            else {
                cur = cur->right;
            }
        }
    }
}
BinarySearchTree::Node* BinarySearchTree::findMin(BinarySearchTree::Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BinarySearchTree::Node* BinarySearchTree::deleteNode(Node* root, unsigned int key, int& offset) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->record.key) {
        root->left = deleteNode(root->left, key, offset);
    }
    else if (key > root->record.key) {
        root->right = deleteNode(root->right, key, offset);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            root->right = nullptr;
            root->left = nullptr;
            offset = root->record.offset;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            root->right = nullptr;
            root->left = nullptr;
            offset = root->record.offset;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->record = temp->record;
        offset = root->record.offset;
        int x;
        root->right = deleteNode(root->right, temp->record.key,x);
    }
    return root;
}

void BinarySearchTree::printTree(Node* root, int level, const std::string& prefix) {
    if (root != nullptr) {
        if (level == 0) {
            std::cout << prefix << root->record.key << std::endl;
        }
        else {
            std::string indent = "    ";
            for (int i = 0; i < level - 1; i++) {
                indent += "    ";
            }
            std::cout << indent << prefix << "|__ " << root->record.key << std::endl;
        }
        printTree(root->left, level + 1, "L: ");
        printTree(root->right, level + 1, "R: ");
    }
}
BinarySearchTree::Node* BinarySearchTree::getRoot() {
    return root;
}
void BinarySearchTree::setRoot(Node* root) {
    this->root = root;
}
BinarySearchTree::~BinarySearchTree() {
    if (root) {
        delete root;
    }
}