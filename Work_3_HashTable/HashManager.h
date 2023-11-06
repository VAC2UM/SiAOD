#pragma once
#include "Bucket.h"
#include "HashTable.h"
#include "Task2.2.h"
#include "Node.h"

using namespace std;

// ������ ������� �� ��������� ����� � ������� � ���-�������
void readBinaryRecordsFromFile(HashMap& map, string binaryFilename) {
	ifstream file(binaryFilename, ios::binary);
	if (!file.is_open()) {
		cerr << "�� ������� ������� ����." << endl;
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
// �������� ������ �� ���-�������
void deleteRecordFromTableAndFile(HashMap& map, string fileName, int targetKey) {
	Node* nodeToDelete = map.findNodeById(targetKey);
	if (nodeToDelete == nullptr) {
		cout << "������ � ��������� ������ �� ������� � �������." << endl;
		return;
	}
	//����� ������ � ���� ������ � �����
	int fileRecordNumberToDelete = nodeToDelete->fileRecordNumber;
	deleteRecordByKey(fileName, fileRecordNumberToDelete);
	map.remove(targetKey);
	map.show();
	cout << "������ � ������ " << targetKey << " ������� �� ������� � �����." << endl;
}

// ������� ��� ���������� ������ � ����� �� ����������� ������ � ������� ���-�������
TrainRecord findRecordFromFileWithTable(HashMap& map, string binaryFilename, int groupNumber) {
	//����� ������ � ���-�������
	return readRecordByIndex(binaryFilename, map.findNodeById(groupNumber)->fileRecordNumber);
}