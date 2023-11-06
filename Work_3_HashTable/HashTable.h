#pragma once
#include <functional>
#include "Node.h"
#include "Bucket.h"

class HashMap {
	const int SIZE = 19;
	int size; // размер таблицы
	int amount; // количество элементов в таблице
	Bucket* buckets = nullptr; // массив полезных данных
	int stepSize;  // Шаг для второй хэш-функции

public:
	HashMap() {
		this->size = SIZE;
		this->amount = 0;
		buckets = new Bucket[this->size];
	}
	~HashMap() {
		Bucket* bucket;
		for (int i = 0; i < this->size; i++) {
			bucket = &this->buckets[i];
			Node* ent = bucket->entry;
			Node* tempEnt;
			while (ent != nullptr) {
				tempEnt = ent;
				ent = ent->nextEntry;
				delete tempEnt;
			}
		}
		delete[]buckets;
	}
	// Удаление из таблицы
	void remove(int id) {
		int i = 0;
		int code = this->doubleHashFunc(id, i);
		bool resultEx = buckets[code].remove(id);
		if (resultEx) {
			amount--;
			cout << "Запись удалена!\n";
		}
		else {
			cout << "Элемент с таким номером не найден\n";
		}
	}
	// Поиск записи по ключу
	Node* findNodeById(int id) {
		int i = 0;
		int hashCode = this->doubleHashFunc(id, i);
		Bucket* bucket = &buckets[hashCode];
		if (bucket != nullptr && bucket->hash != -1) {
			return bucket->get(id);
		}
		else {
			return nullptr;
		}
		i++;
	}

	void show() {
		cout << "/-----------------Hash_Table-----------------\\\n";
		bool flag;
		for (int i = 0; i < size; i++) { // проходимся по buckets
			cout  << i + 1 << ") ";
			flag = false;
			if (!buckets[i].isEmpty()) {
				Node* node = buckets[i].entry;
				while (node != nullptr) {
					if (flag) cout << " ";
					node->show();
					flag = true;
					node = node->nextEntry;
				}
			}
			else {
				cout << "-----NULL-----" << endl;
			}
		}
		cout << "\\--------------------------------------------/\n\n";
	}
	// добавить в таблицу
	//исправить с цепного на простое добавление
	void insert(Node* node) {
		if (this->checkOverflow()) {
			this->resize();
		}
		int i = 0;
		int hashCode = node->getHash(this->size, i);
		while (this->buckets[hashCode].hash != -1) {
			// Пробуем следующую ячейку, пока не найдем свободную
			i++;
			hashCode = node->getHash(this->size, i);
		}
		this->buckets[hashCode].hash = hashCode;
		this->buckets[hashCode].entry = node;
		amount++;
	}

	//void insert(Node* node) {
	//	if (this->checkOverflow()) {
	//		this->resize();
	//	}
	//	int i = 0;
	//	int hashCode = node->getHash(this->size, i);
	//	Bucket* bucket = &this->buckets[hashCode];
	//	bucket->hash = hashCode;
	//	bucket->add(node);
	//	amount++;
	//}
private:
	// хэш-функция
	int doubleHashFunc(int id, int i) {
		int hash1 = id % this->size;
		int hash2 = (i * stepSize) % this->size;
		return (hash1 + hash2) % this->size;
	}
	// рехэширование таблицы
	void resize() {
		int oldSize = this->size;
		this->size *= 2;
		Bucket* newBuckets = new Bucket[this->size];

		for (int i = 0; i < oldSize; i++) {
			Bucket* bucket = &this->buckets[i];
			Node* curEntry = bucket->entry;
			if (curEntry == nullptr) {
				continue;
			}

			int j = 0;
			while (curEntry != nullptr) {
				int hashCode = doubleHashFunc(curEntry->trainNumber, j);
				while (newBuckets[hashCode].hash != -1) {
					j++;
					hashCode = doubleHashFunc(curEntry->trainNumber, j);
				}

				newBuckets[hashCode].hash = hashCode;
				newBuckets[hashCode].entry = curEntry;
				curEntry = curEntry->nextEntry;
			}
		}

		delete[] buckets;
		this->buckets = newBuckets;
		cout << "Рехеширование прошло успешно\n";
	}
	// проверка не переполнение
	bool checkOverflow() {
		return (((double)amount + 1) / size) >= 0.75;
	}
};
//ostream& operator << (ostream& dfdf, HashMap& m) {
//	m.show();
//	return dfdf;
//}