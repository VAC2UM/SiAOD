#include "Task2.2.h"
#include "HashManager.h"

int main() {
	setlocale(LC_ALL, "");
	HashMap myMap;
	string binaryFilename;
	cout << "Введите имя двоичного файла: ";
	cin >> binaryFilename;
	cout << endl;
	ifstream file(binaryFilename);

	while (!file.is_open()) {
		cout << "Ошибка! Введите имя двоичного файла: ";
		cin >> binaryFilename;
		file.open(binaryFilename);
	}

	while (true) {
		int n;		
		cout << "+=========================Меню=========================+\n";
		cout << "1) Прочитать записи из двоичного файла, вставить их в хэш-таблицу и вывести ее" << endl;
		cout << "2) Удалить запись из хэш-таблицы" << endl;
		cout << "3) Найти запись по порядковому номеру" << endl;
		cout << "Выберите действие: ";
		cin >> n;
		cout << endl;
		switch (n) {
		case 1:
			readBinaryRecordsFromFile(myMap, binaryFilename);
			break;
		case 2:
			cout << "Введите номер поезда, запись которого хотите удалить:";
				int targetKey;
			cin >> targetKey;
			deleteRecordFromTableAndFile(myMap, binaryFilename, targetKey);
			break;
		case 3:
			int trainNumber;
			cout << "Введите номер поезда, запись которого хотите найти:";
				cin >> trainNumber;
			cout << endl;
			TrainRecord record = findRecordFromFileWithTable(myMap,
				binaryFilename, trainNumber);
			if (record.trainNumber > 0) {
				cout << "Запись поезда: " << trainNumber << ":" <<
					endl;
				cout << "Номер поезда: " << record.trainNumber << endl;
				cout << "Пункт отъезда: " << record.departureCity <<
					endl;
				cout << "Пункт прибытия: " << record.destinationCity << endl;
				cout << "Время отъезда: " << record.departureTime << endl;
			}
			else {
				cerr << "Ошибка при чтении записи." << endl;
			}
			break;
		case 4:
			textFileToBinaryFile("input.txt", binaryFilename);
			break;
		default:
			cout << "Такой функции нет!" << endl;
			break;
		}
	}
	file.close();
	return 0;
}