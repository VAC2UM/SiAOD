#pragma once
#include <iostream>
#include "Task2.2.h"
using namespace std;

struct Node {
	int trainNumber;// ���� ������(����� ������)
	int fileRecordNumber; // ����� ������ � ���� ������ � �����
	int stepSize;  // ��� ��� ������ ���-�������
	bool isDeleted = false;
	Node* nextEntry = nullptr;
	
	Node(int trainNumber, int fileRecordNumber) {
		this->trainNumber = trainNumber;
		this->fileRecordNumber = fileRecordNumber;
	}
	
	// ���-�������
	int getHash(int sizeArr, int i) {
		int hash1 = this->trainNumber % sizeArr;
		int hash2 = (i * stepSize) % sizeArr;
		return (hash1 + hash2) % sizeArr;
	}
	
	// �����
	void show() {
		if (isDeleted) {
			std::cout << "DELETED ";
		}
		std::cout << "����� ������: " << trainNumber << std::endl;
	}
};