#pragma once
#include <iostream>
#include "Task2.2.h"
using namespace std;

struct Node {
	int trainNumber;// Ключ записи(номер поезда)
	int fileRecordNumber; // Номер записи с этим ключом в файле
	int stepSize;  // Шаг для второй хэш-функции
	bool isDeleted = false;
	Node* nextEntry = nullptr;
	
	Node(int trainNumber, int fileRecordNumber) {
		this->trainNumber = trainNumber;
		this->fileRecordNumber = fileRecordNumber;
	}
	
	// хэш-функция
	int getHash(int sizeArr, int i) {
		int hash1 = this->trainNumber % sizeArr;
		int hash2 = (i * stepSize) % sizeArr;
		return (hash1 + hash2) % sizeArr;
	}
	
	// вывод
	void show() {
		if (isDeleted) {
			std::cout << "DELETED ";
		}
		std::cout << "Номер поезда: " << trainNumber << std::endl;
	}
};