#pragma once
#ifndef FILEMANAGER
#define FILEMANAGER
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "Record.h"
#include "BinarySearchTree.h"
#include "RandomBinarySearchTree.h"
#include "HashTable.h"
#include <set>
#include <algorithm>
#include <random>
#include <string.h>

using namespace std;

class FileManager {
    fstream fs;
    int countRecord;
public:
    FileManager(int countRecord);
    int getCountRecord();
    void add(Record&);
    HashTable* generateTable();
    BinarySearchTree* generateBinarySearchTree();
    RandomBinarySearchTree* generateRandomBinarySearchTree();
    Record find(unsigned int);
    string findWithBTS(unsigned int, BinarySearchTree*);
    string findWithRBTS(unsigned int key, RandomBinarySearchTree* tree);
    void removeRecord(unsigned int);
    int GenerateTxtFile(unsigned int array_size, bool randomOrder);
    int GenerateBinFile(unsigned int size);
    ~FileManager();
};
#endif