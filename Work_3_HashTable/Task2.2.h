#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

struct TrainRecord {
    int trainNumber;
    char departureCity[50];
    char destinationCity[50];
    char departureTime[10];
};

void textFileToBinaryFile(string textFilename, string binaryFilename);
void convertTextToBinary(string textFilename, string binaryFilename);
void binaryFileToTextFile(string binaryFilename, string textFilename);
void printBinaryFile(string binaryFilename);
TrainRecord readRecordByIndex(const string& fileName, int index);
void deleteRecordByKey(const string& fileName, int keyToDelete);
