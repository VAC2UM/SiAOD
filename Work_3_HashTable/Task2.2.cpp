#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Task2.2.h"

using namespace std;

// ������� ��� �������������� ��������� ������ � �������� ����
void convertTextToBinary(const string& inputFileName, const string& outputFileName) {
	ifstream inputFile(inputFileName);
	if (!inputFile) {
		cerr << "�� ������� ������� ��������� ���� ��� ������." << endl;
		return;
	}
	ofstream outputFile(outputFileName, ios::binary);
	if (!outputFile) {
		cerr << "�� ������� ������� �������� ���� ��� ������." << endl;
		return;
	}
	TrainRecord record;
	while (inputFile >> record.trainNumber) {
		inputFile.ignore();
		inputFile.getline(record.departureCity, sizeof(record.departureCity));
		inputFile.getline(record.destinationCity, sizeof(record.destinationCity));
		inputFile.ignore();
		inputFile.getline(record.departureTime, sizeof(record.departureTime));
		inputFile.ignore();
		outputFile.write((char*)&record, sizeof(TrainRecord));
	}
	inputFile.close();
	outputFile.close();
}
void textFileToBinaryFile(string textFilename, string binaryFilename) {
	ifstream inputFile(textFilename);
	if (!inputFile) {
		cerr << "�� ������� ������� ��������� ���� ��� ������." << endl;
		return;
	}
	ofstream outputFile(binaryFilename, ios::binary);
	if (!outputFile) {
		cerr << "�� ������� ������� �������� ���� ��� ������." << endl;
		return;
	}
	TrainRecord record;
	while (inputFile >> record.trainNumber) {
		inputFile.ignore();
		inputFile.getline(record.departureCity, sizeof(record.departureCity));
		inputFile.getline(record.destinationCity, sizeof(record.destinationCity));
		inputFile.ignore();
		inputFile.getline(record.departureTime, sizeof(record.departureTime));
		inputFile.ignore();
		outputFile.write((char*)&record, sizeof(TrainRecord));
	}
	inputFile.close();
	outputFile.close();
}

// ������� ��� ���������� ������ �� ��������� ����� � ��������� �������
void binaryFileToTextFile(string binaryFilename, string textFilename) {
	ifstream binaryFile(binaryFilename, ios::binary);
	ofstream textFile(textFilename);

	if (!binaryFile.is_open()) {
		cout << "������ �������� ��������� �����." << endl;
		return;
	}

	if (!textFile.is_open()) {
		cout << "������ �������� ���������� �����." << endl;
		return;
	}

	TrainRecord record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(TrainRecord))) {
		textFile << record.trainNumber << " " << record.departureCity << " " << record.destinationCity << " " << record.departureTime << endl;
	}

	binaryFile.close();
	textFile.close();
}

void printBinaryFile(string binaryFilename) {
	ifstream binaryFile(binaryFilename, ios::binary);

	if (!binaryFile.is_open()) {
		cout << "������ �������� ��������� �����." << endl;
		return;
	}

	TrainRecord record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(TrainRecord))) {
		cout << record.trainNumber << " " << record.departureCity << " " << record.destinationCity << " " << record.departureTime << endl;
	}
	cout << endl;
	binaryFile.close();
}

// ������� ��� ������ ������ �� ����������� ������
TrainRecord readRecordByIndex(const string& fileName, int targetNumber) {
	ifstream file(fileName, ios::binary);
	if (!file) {
		cerr << "�� ������� ������� �������� ���� ��� ������." << endl;
		return TrainRecord();
	}
	TrainRecord record;
	size_t recordSize = sizeof(TrainRecord);
	file.seekg((targetNumber) * recordSize, ios::beg);
	if (file.read((char*)&record, recordSize)) {
		file.close();
		return record;
	}
	else {
		cerr << "������ � ������� " << targetNumber << " �� �������." << endl;
		file.close();
	}
}
// ������� ��� �������� ������ � ������� ������ �� ��������� �� ����������� ������
void deleteRecordByKey(const string& fileName, int targetIndex) {
	fstream file(fileName, ios::binary | ios::in | ios::out);
	if (!file) {
		cerr << "�� ������� ������� �������� ���� ��� ������ � ������." << endl;
		return;
	}
	TrainRecord currentRecord;
	int recordCount = 0;
	while (file.read((char*)&currentRecord, sizeof(TrainRecord))) {
		++recordCount;
	}
	if (targetIndex < 1 || targetIndex > recordCount) {
		cerr << "������ � ��������� ���������� ������� �� ����������." << endl;
		file.close();
		return;
	}
	file.clear();
	file.seekg(0);
	int currentIndex = 0;
	while (currentIndex < targetIndex - 1) {
		file.read((char*)&currentRecord, sizeof(TrainRecord));
		++currentIndex;
	}
	streampos deletePos = file.tellg();
	file.seekg(0, ios::end);
	streampos endPos = file.tellg();
	file.seekg(-static_cast<streamoff>(sizeof(TrainRecord)), ios::cur);
	file.read((char*)&currentRecord, sizeof(TrainRecord));
	file.seekp(deletePos);
	file.write((char*)&currentRecord, sizeof(TrainRecord));
	file.seekp(endPos - static_cast<streamoff>(sizeof(TrainRecord)));
	TrainRecord emptyrecord;
	file.write((char*)&emptyrecord, sizeof(emptyrecord));
	file.close();
}