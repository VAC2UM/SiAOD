#pragma once
#include "Task2.2.h"
#include "Node.h"

struct Bucket {
	int hash = -1;        // ��� �������� ����� (bucket)
	Node* entry = nullptr; // ��������� �� ������ ������ � �����;
	bool isDeleted; //���� ��� ������� ��������� ��-�

	Bucket() : hash(-1),entry(nullptr), isDeleted(false) {}
	bool isEmpty() {
		return hash == -1;// ��������, ������ �� ����
	}
	void add(Node* entry) {
		if (this->entry == nullptr) {
			this->entry = entry; // ���� ����� ������, ������������� ������ ������
		}
		else {
			Node* ent = this->entry;
			while (ent->nextEntry != nullptr) {
				ent = ent->nextEntry;
			}
			ent->nextEntry = entry; // ��������� ������ � ����� ������ ��������
			entry->nextEntry = nullptr; // ����������, ��� ����� ������ ��������� �� nullptr
		}
	}
	Node* get(int id) {
		if (this->entry != nullptr) {
			Node* ent = this->entry;
			while (ent != nullptr) {
				if (ent->trainNumber == id) {
					return ent; // ����� ������ � ��������� ������
				}
				ent = ent->nextEntry;
			}
		}
		return nullptr;
	}
	bool remove(int id) {
		if (entry != nullptr) {
			if (entry->trainNumber == id && !entry->isDeleted) {
				entry->isDeleted = true;
				return true;
			}
		}
		return false;
		//if (this->entry != nullptr) {
		//	Node* ent = this->entry;
		//	if (ent->trainNumber == id) {
		//		if (ent->nextEntry != nullptr) {
		//			this->entry = ent->nextEntry;
		//			ent->nextEntry = nullptr;
		//		}
		//		else {
		//			this->entry = nullptr;
		//			hash = -1;
		//		}
		//		delete ent;
		//		return true;
		//	}
		//	else {
		//		Node* prevNode = entry;
		//		Node* nextNode = entry->nextEntry;
		//		Node* findNode = nullptr;
		//		if (nextNode != nullptr) {
		//			while (nextNode != nullptr) {
		//				if (nextNode->trainNumber == id) {
		//					findNode = nextNode;
		//					break;
		//				}
		//				prevNode = nextNode;
		//				nextNode = nextNode->nextEntry;
		//			}
		//			if (findNode != nullptr) {
		//				prevNode->nextEntry = findNode -> nextEntry;
		//				delete findNode; // ����������� ������		
		//				return true;
		//			}
		//		}
		//	}
		//}
		//return false;
	}
};