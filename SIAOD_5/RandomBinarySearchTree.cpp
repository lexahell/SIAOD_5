#include "RandomBinarySearchTree.h"


RandomBinarySearchTree::Node::Node(unsigned int key, int offset) {
    record.key = key;
    record.offset = offset;
    left = nullptr;
    right = nullptr;
}
RandomBinarySearchTree::Node::~Node() {
    delete left;
    delete right;
}


RandomBinarySearchTree::Node* RandomBinarySearchTree::getRoot() {
    return root;
}
void RandomBinarySearchTree::setRoot(Node* root) {
    this->root = root;
};

int RandomBinarySearchTree::getSize(Node* p) {
    if (!p) return 0;
    return p->size;
}
void RandomBinarySearchTree::fixSize(Node* p) {
    p->size = getSize(p->left) + getSize(p->right) + 1;
}

RandomBinarySearchTree::Node* RandomBinarySearchTree::rotateRight(Node* p) {
    Node* q = p->left;
    if (!q) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixSize(p);
    countRotate++;
    return q;
}
RandomBinarySearchTree::Node* RandomBinarySearchTree::rotateLeft(Node* q) {
    Node* p = q->right;
    if (!p) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixSize(q);
    countRotate++;
    return p;
}
RandomBinarySearchTree::Node* RandomBinarySearchTree::insertRoot(Node* root, unsigned int key, int offset) {
    if (!root) {
        return new Node(key, offset);
    } 
    if (key < root->record.key)
    {
        root->left = insertRoot(root->left, key, offset);
        return rotateRight(root);
    }
    else
    {
        root->right = insertRoot(root->right, key, offset);
        return rotateLeft(root);
    }
}

RandomBinarySearchTree::Node* RandomBinarySearchTree::insert(Node* root, unsigned int key, int offset) {
    if (!root) {
        return new Node(key, offset);
    }
    if (rand() % (root->size + 1) == 0) {
        return insertRoot(root, key, offset);
    }
    if (root->record.key > key) {
        root->left = insert(root->left, key, offset);
    }
    else {
        root->right = insert(root->right, key, offset);
    }
    fixSize(root);
    return root;
}



int RandomBinarySearchTree::findNode(unsigned int key) {
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
void RandomBinarySearchTree::printTree(Node* root, int level, const std::string& prefix) {
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

RandomBinarySearchTree::Node* RandomBinarySearchTree::join(Node* p, Node* q) {
    if (!p) return q;
    if (!q) return p;
    if (rand() % (p->size + q->size) < p->size)
    {
        p->right = join(p->right, q);
        fixSize(p);
        return p;
    }
    else
    {
        q->left = join(p, q->left);
        fixSize(q);
        return q;
    }
}
RandomBinarySearchTree::Node* RandomBinarySearchTree::remove(Node* p, int k, int& offset) {
    if (!p) return p;
    if (p->record.key == k)
    {
        Node* q = join(p->left, p->right);
        offset = p->record.offset;
        p->left = nullptr;
        p->right = nullptr;
        delete p;
        return q;
    }
    else if (k < p->record.key)
        p->left = remove(p->left, k, offset);
    else {
        p->right = remove(p->right, k, offset);
    }
    return p;
}

RandomBinarySearchTree::~RandomBinarySearchTree() {
    if (root) {
        delete root;
    }
}