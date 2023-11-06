#pragma once
#include "Bucket.h"
#include "HashTable.h"
#include "Task2.2.h"
#include "Node.h"

using namespace std;

// Чтение записей из двоичного файла и вставка в хеш-таблицу
void readBinaryRecordsFromFile(HashMap& map, string binaryFilename) {
	ifstream file(binaryFilename, ios::binary);
	if (!file.is_open()) {
		cerr << "Не удалось открыть файл." << endl;
		return;
	}
	TrainRecord record;
	int index = 0;
	while (file.read((char*)(&record), sizeof(TrainRecord))) {
		if (record.trainNumber > 0) {
			Node* newNode = new Node(record.trainNumber, index);
			map.insert(newNode);
		}
		index++;
	}
	file.close();
	map.show();
}
// Удаление записи из хэш-таблицы
void deleteRecordFromTableAndFile(HashMap& map, string fileName, int targetKey) {
	Node* nodeToDelete = map.findNodeById(targetKey);
	if (nodeToDelete == nullptr) {
		cout << "Запись с указанным ключом не найдена в таблице." << endl;
		return;
	}
	//номер записи с этим ключом в файле
	int fileRecordNumberToDelete = nodeToDelete->fileRecordNumber;
	deleteRecordByKey(fileName, fileRecordNumberToDelete);
	map.remove(targetKey);
	map.show();
	cout << "Запись с ключом " << targetKey << " удалена из таблицы и файла." << endl;
}

// Функция для нахождения записи в файле по порядковому номеру с помощью хэш-таблицы
TrainRecord findRecordFromFileWithTable(HashMap& map, string binaryFilename, int groupNumber) {
	//Поиск записи в хэш-таблице
	return readRecordByIndex(binaryFilename, map.findNodeById(groupNumber)->fileRecordNumber);
}