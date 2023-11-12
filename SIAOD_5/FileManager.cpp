#include "FileManager.h"
FileManager::FileManager(int countRecord) {
	this->countRecord = countRecord;
};

int FileManager::GenerateTxtFile(unsigned int array_size, bool randomOrder) {
    const std::vector<std::string> ARR_FIRST_NAMES = { "Иван", "Василий", "Семен", "Арсений", "Артем", "Лев", "Макар", "Сергей", "Михаил", "Максим", "Евгений", "Николай", "Юрий", "Илья", "Аристарх", "Виталий", "Егор" };
    const std::vector<std::string> ARR_OF_LAST_NAMES = { "Высоцкий", "Пулеметов", "Мельников", "Кузнцеов", "Чупков", "Малютин", "Волков", "Морозов", "Рылов", "Минаков", "Головин", "Чернов", "Смирнов", "Карпов", "Саламатин" };
    const std::vector<std::string> ARR_OF_PATRONOMYCS = { "Артемович", "Иванович", "Львович", "Ильич", "Семнович", "Макарович", "Олегович", "Павлович", "Игоревич", "Юрьевич", "Дмитрович", "Егорович", "Сергеевич" };
    const std::vector<std::string> ARR_OF_CAR_BRANDS = { "BMW", "CHEVROLET", "DODGE", "FERRARI", "LAMBORGINI", "NISSAN", "KIA", "MARK", "MERCEDES", "MAZDA", "FIAT", "KAMAZ", "LIAZ" };

    srand(static_cast<unsigned int>(time(0)));
    set<unsigned int> unique_numbers; // Сет для хранения уникальных чисел
    unsigned int min_number = 1000000;
    unsigned int max_number = 9999999;
    // Проверяем, что размер массива не больше диапазона возможных уникальных чисел
    if (array_size > max_number - min_number + 1) {
        std::cerr << "Невозможно сгенерировать массив заданного размера с уникальными числами." << std::endl;
        return 1;
    }
    // Генерируем уникальные числа и добавляем их в сет
    while (unique_numbers.size() < array_size) {
        unsigned int random_number = min_number + (unsigned int)((double)(rand() * rand()) / (RAND_MAX * RAND_MAX) * (max_number - min_number + 1));
        unique_numbers.insert(random_number);
    }
    // Конвертируем сет в массив
    vector<int> random_numbers = vector<int>(array_size);
    int i = 0;
    for (int num : unique_numbers) {
        random_numbers[i] = num;
        i++;
    }
    // Перемешиваем элементы массива, если требуется
    if (randomOrder) {
        shuffle(begin(random_numbers), end(random_numbers), default_random_engine{});
    }

    // Запись в файл
    ofstream out("cars.txt");
    if (out.is_open()) {
        for (int i = 0; i < array_size; i++) {
            out << random_numbers[i] << " ";
            out << ARR_OF_CAR_BRANDS[rand() % ARR_OF_CAR_BRANDS.size()] << " ";
            out << ARR_OF_LAST_NAMES[rand() % ARR_OF_LAST_NAMES.size()] << " ";
            out << ARR_FIRST_NAMES[rand() % ARR_FIRST_NAMES.size()] << " ";
            out << ARR_OF_PATRONOMYCS[rand() % ARR_OF_PATRONOMYCS.size()] << endl;
        }
    }
    out.close();
}
int FileManager::GenerateBinFile(unsigned int size) {
    ifstream fin("cars.txt");
    ofstream binfout("records.bin", ios::trunc | ios::out | ios::binary);
    if (fin.is_open() && binfout.is_open()) {
        Record record;
        for (int i = 0; i < size; i++) {
            fin >> record.number_car;
            fin >> record.carBrand;
            fin >> record.lastName;
            fin >> record.firstName;
            fin >> record.patronymic;
            binfout.write((char*)&record, sizeof(record));
        }
    }
    fin.close();
    binfout.close();
    return 0;
}

int FileManager::getCountRecord() {
	return countRecord;
}

void FileManager::add(Record& record) {
	fs.open("records.bin", ios::in | ios::out | ios::binary);
	if (fs.is_open()) {
		fs.seekp(0, std::ios::end);
		fs.write(reinterpret_cast<char*>(&record), sizeof(Record));
		++countRecord;
	}
	fs.close();
}
HashTable* FileManager::generateTable() {
	fs.open("records.bin", ios::in | ios::out | ios::binary);
	Record rec;
	HashTable* table = new HashTable(8);
	if (fs.is_open()) {
		fs.seekg(0, ios::beg);
		for (int i = 0; i < countRecord; i++) {
			fs.read(reinterpret_cast<char*>(&rec), sizeof(Record));
			table->pushRecordKey(rec.number_car, i * sizeof(Record));
		}
	}
	fs.seekg(0, ios::beg);
	fs.close();
	return table;
}

Record FileManager::find(unsigned int offset) {
	fs.open("records.bin", ios::in | ios::out | ios::binary);
	Record rec;
	fs.seekg(offset, ios::beg);
	fs.read(reinterpret_cast<char*>(&rec), sizeof(Record));
	fs.close();
	return rec;
}


void FileManager::removeRecord(unsigned int offset) {
	fs.open("records.bin", ios::in | ios::out | ios::binary);
	if (fs.is_open()) {
		fs.seekg(0, std::ios::beg);
		std::fstream ofs("temp.bin", std::ios::out | std::ios::binary);
		Record rec;
		int size = countRecord;
		for (int i = 0; i < size; i++) {
			if ((i * sizeof(Record)) != offset) {
				fs.read(reinterpret_cast<char*>(&rec), sizeof(Record));
				ofs.write(reinterpret_cast<char*>(&rec), sizeof(Record));
			}
			else {
				fs.seekg(sizeof(Record), std::ios::cur);

			}
		}
		ofs.close();
		fs.close();
		--countRecord;
		remove("records.bin");
		rename("temp.bin","records.bin");
		cout << "Запись удалена" << endl;
	}
	fs.close();
}

BinarySearchTree* FileManager::generateBinarySearchTree() {
	fs.open("records.bin", ios::in | ios::out | ios::binary);
	Record rec;
	BinarySearchTree* tree = new BinarySearchTree();
	if (fs.is_open()) {
		fs.seekg(0, ios::beg);
		for (int i = 0; i < countRecord; i++) {
			fs.read(reinterpret_cast<char*>(&rec), sizeof(Record));
			tree->addNode(rec.number_car, i * sizeof(Record));
		}
	}
	fs.seekg(0, ios::beg);
	fs.close();
	return tree;
}
RandomBinarySearchTree* FileManager::generateRandomBinarySearchTree() {
	fs.open("records.bin", ios::in | ios::out | ios::binary);
	Record rec;
	RandomBinarySearchTree* tree = new RandomBinarySearchTree();
	if (fs.is_open()) {
		fs.seekg(0, ios::beg);
		for (int i = 0; i < countRecord; i++) {
			fs.read(reinterpret_cast<char*>(&rec), sizeof(Record));
			tree->setRoot(tree->insert(tree->getRoot(), rec.number_car, i * sizeof(Record)));
		}
	}
	fs.seekg(0, ios::beg);
	fs.close();
	return tree;
}


string FileManager::findWithBTS(unsigned int key, BinarySearchTree* tree){
	int offset = tree->findNode(key);
	if (offset == -1) return "";
	Record record = this->find(offset);
	return to_string(record.number_car) + " " + record.carBrand + " " + record.lastName + " " + record.firstName + " " + record.patronymic;
}

string FileManager::findWithRBTS(unsigned int key, RandomBinarySearchTree* tree) {
	int offset = tree->findNode(key);
	if (offset == -1) return "";
	Record record = this->find(offset);
	return to_string(record.number_car) + " " + record.carBrand + " " + record.lastName + " " + record.firstName + " " + record.patronymic;
}

FileManager::~FileManager() {
	fs.close();
}
