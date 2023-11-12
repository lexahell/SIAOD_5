#include <iostream>
#include "Record.h"
#include "RandomBinarySearchTree.h"
#include "BinarySearchTree.h"
#include "FileManager.h"
#include "HashTable.h"
#include <chrono>
using namespace std;





int main() {
    setlocale(0, "RUS");
    unsigned long size = 0;
    unsigned short choice = 0;
    //BinarySearchTree tree;
    //tree.addNode(100, 0);
    //tree.addNode(123, 104);
    //tree.addNode(23, 4);
    //tree.addNode(12, 104);
    //tree.addNode(110, 213);
    //tree.addNode(1000, 104);
    //tree.addNode(1100, 41234);
    //tree.addNode(990, 42341);
    //tree.findNode(110, 213);
    //tree.deleteNode(tree.getRoot(), 990);
    //tree.printTree(tree.getRoot());
    while (true) {
        cout << "Введите номер команды:" << endl;
        cout << "1 - вывод содержимого бинарного файла" << endl;
        cout << "2 - вывод бинарного дерева поиска" << endl;
        cout << "3 - вывод рандомизированного бинарного дерева поиска" << endl;
        cout << "4 - сгенерировать бинарный файл и заполнить деревья поиска" << endl;
        cout << "5 - поиск записи в файле с использованием бинарного дерева поиска" << endl;
        cout << "6 - удаление записи из файла с использованием бинарного дерева поиска" << endl;
        cout << "7 - поиск записи в файле с использованием рандомизированного бинарного дерева поиска" << endl;
        cout << "8 - удаление записи из файла с использованием рандомизированного бинарного дерева поиска" << endl;
        cout << "9 - поиск записи в файле с использованием хеш-таблицы" << endl;
        cout << "0 - завершение программы" << endl;

        bool found = false;
        FileManager* p_file = nullptr;
        BinarySearchTree* tree = nullptr;
        RandomBinarySearchTree* random_tree = nullptr;
        HashTable* table = nullptr;
        while (true) {
            cin >> choice;
            switch (choice) {
            case 1: {
                ifstream fin("records.bin", ios::binary | ios::in);
                fin.seekg(0, ios::beg);
                cout << "Содержимое бинарного файла" << endl;
                for (int i = 0; i < p_file->getCountRecord(); i++) {
                    Record record;
                    fin.read(reinterpret_cast<char*>(&record), sizeof(Record));
                    cout << record.number_car
                        << " " << record.carBrand
                        << " " << record.lastName
                        << " " << record.firstName
                        << " " << record.patronymic
                        << endl;
                }
                fin.close();
                break;
            }
            case 2: {
                if (!tree) {
                    break;
                }
                tree->printTree(tree->getRoot());
                break;
            }
            case 3: {
                if (!random_tree) {
                    break;
                }
                random_tree->printTree(random_tree->getRoot());
                break;
            }
            case 4: {
                cout << "Введите количество записей: ";
                cin >> size;
                p_file = new FileManager(size);
                p_file->GenerateTxtFile(size, true);
                p_file->GenerateBinFile(size);
                tree = p_file->generateBinarySearchTree();
                random_tree = p_file->generateRandomBinarySearchTree();
                table = p_file->generateTable();

                cout << "бинарный файл, деревья поиска заполнены и хеш-таблица заполнены" << endl;
                cout << "Число поворотов:  " << random_tree->countRotate << endl;
                cout << "Cреднее число поворотов равно: " << (double)random_tree->countRotate / size << endl;
                break;
            }
            case 5: {
                int key;
                cout << "Введите номер машины для поиска: ";
                cin >> key;
                string record_info;
                auto begin = chrono::high_resolution_clock::now();
                record_info = p_file->findWithBTS(key, tree);
                cout << "Запись найдена c помощью бинарного дерева поиска за " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - begin).count() << " ns\n";
                cout << record_info << endl;
                break;
            }
            case 6: {
                int key;
                cout << "Введите номер машины для удаления: ";
                cin >> key;
                int offset = -1;
                tree->setRoot(tree->deleteNode(tree->getRoot(),key,offset));
                if (offset < 0) {
                    cout << "Запись не удалена из файла, смещение меньше 0" << endl;
                    break;
                }
                p_file->removeRecord(offset);
                random_tree->setRoot(random_tree->remove(random_tree->getRoot(), key, offset));
                break;
            }
            case 7: {
                int key;
                cout << "Введите номер машины для поиска: ";
                cin >> key;
                string record_info;
                auto begin = chrono::high_resolution_clock::now();
                record_info = p_file->findWithRBTS(key, random_tree);
                cout << "Запись найдена c помощью рандомизированного бинарного дерева поиска за " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - begin).count() << " ns\n";
                cout << record_info << endl;
                break;
            }
            case 8: {
                int key;
                cout << "Введите номер машины для удаления: ";
                cin >> key;
                int offset = -1;
                random_tree->setRoot(random_tree->remove(random_tree->getRoot(), key, offset));
                if (offset < 0) {
                    cout << "Запись не удалена из файла, смещение меньше 0" << endl;
                    break;
                }
                p_file->removeRecord(offset);
                tree->setRoot(tree->deleteNode(tree->getRoot(), key, offset));
                break;
            }
            case 9: {
                unsigned int key;
                cout << "Введите ключ: ";
                cin >> key;
                auto begin = chrono::high_resolution_clock::now();
                int offset = table->findRecord(key);
                if (offset != -1) {
                    Record record;
                    record = p_file->find(offset);
                    cout << "Запись найдена c помощью хеш-таблицы за " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - begin).count() << " ns\n";
                    cout << to_string(record.number_car) + " " + record.carBrand + " " + record.lastName + " " + record.firstName + " " + record.patronymic << endl;
                }
                else {
                    cout << "Запись не найдена" << endl;
                }
                break;
            }
            case 0:
                delete p_file;
                delete tree;
                delete random_tree;
                delete table;
                return 0;
            default:
                break;
            }
        }
    }
    return 0;

}

