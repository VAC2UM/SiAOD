#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Task2.2.h"

using namespace std;

// Функция для преобразования текстовых данных в двоичный файл
void convertTextToBinary(const string& inputFileName, const string& outputFileName) {
	ifstream inputFile(inputFileName);
	if (!inputFile) {
		cerr << "Не удалось открыть текстовый файл для чтения." << endl;
		return;
	}
	ofstream outputFile(outputFileName, ios::binary);
	if (!outputFile) {
		cerr << "Не удалось открыть двоичный файл для записи." << endl;
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
		cerr << "Не удалось открыть текстовый файл для чтения." << endl;
		return;
	}
	ofstream outputFile(binaryFilename, ios::binary);
	if (!outputFile) {
		cerr << "Не удалось открыть двоичный файл для записи." << endl;
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

// Функция для сохранения данных из двоичного файла в текстовом формате
void binaryFileToTextFile(string binaryFilename, string textFilename) {
	ifstream binaryFile(binaryFilename, ios::binary);
	ofstream textFile(textFilename);

	if (!binaryFile.is_open()) {
		cout << "Ошибка открытия бинарного файла." << endl;
		return;
	}

	if (!textFile.is_open()) {
		cout << "Ошибка открытия текстового файла." << endl;
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
		cout << "Ошибка открытия бинарного файла." << endl;
		return;
	}

	TrainRecord record;
	while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(TrainRecord))) {
		cout << record.trainNumber << " " << record.departureCity << " " << record.destinationCity << " " << record.departureTime << endl;
	}
	cout << endl;
	binaryFile.close();
}

// Функция для чтения записи по порядковому номеру
TrainRecord readRecordByIndex(const string& fileName, int targetNumber) {
	ifstream file(fileName, ios::binary);
	if (!file) {
		cerr << "Не удалось открыть двоичный файл для чтения." << endl;
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
		cerr << "Запись с номером " << targetNumber << " не найдена." << endl;
		file.close();
	}
}
// Функция для удаления записи с помощью замены на последнюю по порядковому номеру
void deleteRecordByKey(const string& fileName, int targetIndex) {
	fstream file(fileName, ios::binary | ios::in | ios::out);
	if (!file) {
		cerr << "Не удалось открыть двоичный файл для чтения и записи." << endl;
		return;
	}
	TrainRecord currentRecord;
	int recordCount = 0;
	while (file.read((char*)&currentRecord, sizeof(TrainRecord))) {
		++recordCount;
	}
	if (targetIndex < 1 || targetIndex > recordCount) {
		cerr << "Запись с указанным порядковым номером не существует." << endl;
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