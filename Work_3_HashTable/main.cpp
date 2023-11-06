#include "Task2.2.h"
#include "HashManager.h"

int main() {
	setlocale(LC_ALL, "");
	HashMap myMap;
	string binaryFilename;
	cout << "������� ��� ��������� �����: ";
	cin >> binaryFilename;
	cout << endl;
	ifstream file(binaryFilename);

	while (!file.is_open()) {
		cout << "������! ������� ��� ��������� �����: ";
		cin >> binaryFilename;
		file.open(binaryFilename);
	}

	while (true) {
		int n;		
		cout << "+=========================����=========================+\n";
		cout << "1) ��������� ������ �� ��������� �����, �������� �� � ���-������� � ������� ��" << endl;
		cout << "2) ������� ������ �� ���-�������" << endl;
		cout << "3) ����� ������ �� ����������� ������" << endl;
		cout << "�������� ��������: ";
		cin >> n;
		cout << endl;
		switch (n) {
		case 1:
			readBinaryRecordsFromFile(myMap, binaryFilename);
			break;
		case 2:
			cout << "������� ����� ������, ������ �������� ������ �������:";
				int targetKey;
			cin >> targetKey;
			deleteRecordFromTableAndFile(myMap, binaryFilename, targetKey);
			break;
		case 3:
			int trainNumber;
			cout << "������� ����� ������, ������ �������� ������ �����:";
				cin >> trainNumber;
			cout << endl;
			TrainRecord record = findRecordFromFileWithTable(myMap,
				binaryFilename, trainNumber);
			if (record.trainNumber > 0) {
				cout << "������ ������: " << trainNumber << ":" <<
					endl;
				cout << "����� ������: " << record.trainNumber << endl;
				cout << "����� �������: " << record.departureCity <<
					endl;
				cout << "����� ��������: " << record.destinationCity << endl;
				cout << "����� �������: " << record.departureTime << endl;
			}
			else {
				cerr << "������ ��� ������ ������." << endl;
			}
			break;
		case 4:
			textFileToBinaryFile("input.txt", binaryFilename);
			break;
		default:
			cout << "����� ������� ���!" << endl;
			break;
		}
	}
	file.close();
	return 0;
}