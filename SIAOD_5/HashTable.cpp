#include "Hashtable.h"
#include "Record.h"
#include <forward_list>
#include <string>
using namespace std;
int HashTable::hashFunction(unsigned int key, int size) {
    return key % size;
}
HashTable::HashTable(int size) {
    this->size = size;
    this->countRecords = 0;
    this->p_array = new std::forward_list<RecordKey>[size];
}
HashTable::~HashTable() {
    delete[] p_array;
}
void HashTable::rehash() {
    forward_list<RecordKey>* currentTable = new forward_list<RecordKey>[size * 2];
    for (int i = 0; i < size; i++) {
        for (RecordKey j : p_array[i]) {
            int index = hashFunction(j.key, size * 2);
            currentTable[index].push_front(RecordKey(j.key, j.offset));
        }
    }
    delete[] p_array;
    size = size * 2;
    p_array = currentTable;
};
void HashTable::pushRecordKey(int key, int offset) {
    int index = hashFunction(key, size);
    p_array[index].push_front(RecordKey(key, offset));
    countRecords++;
    if (((double)countRecords / size) > 0.75) {
        this->rehash();
    }
}
int HashTable::deleteRecord(unsigned int key) {
    int index = hashFunction(key, size);
    for (RecordKey record : p_array[index]) {
        if (record.key == key) {
            countRecords--;
            int offset = record.offset;
            //���������� �������� � ������� ����� �����
            for (int i = 0; i < size; i++) {
                for (RecordKey& j : p_array[i]) {
                    if (offset < j.offset) {
                        j.offset -= sizeof(Record);
                    }
                }
            }
            p_array[index].remove(record);
            return offset;
        }
    }
    return -1;
}

int HashTable::findRecord(unsigned int key) {
    int index = hashFunction(key, size);
    for (RecordKey record : p_array[index]) {
        if (record.key == key) {
            return record.offset;
        }
    }
    return -1;
}
void HashTable::print() {
    cout << "������ �������: " << size << endl;
    for (int i = 0; i < size; i++) {
        for (RecordKey record : p_array[i]) {
            cout << "������ ��������, � ������� �������� ������: " + to_string(i) + " ����: " + to_string(record.key) + " ��������: " + to_string(record.offset) << endl;
        }
    }
}