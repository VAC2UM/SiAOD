#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename DataType>
class ExprTree {
public:
	// ����������� �� ���������
	ExprTree();
	// ����������� �����������
	ExprTree(const ExprTree& source);
	// ����� ��� ���������� ������
	void build();
	// ����� ��� ������ ��������������� ���������
	void expression() const;
	// ����� ��� ���������� �������� ���������
	DataType evaluate() const throw (logic_error);
	// ����� ��� �������� ��������������� ���� ��������
	bool isEquivalent(const ExprTree& source) const;
	// ����� ��� ����������� ��������� ������
	void showStructure() const;
private:
	// ��������� ����� ��� ������������� ���� ������
	class ExprTreeNode {
	public:
		// ����������� ����
		ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr);
		char dataItem; // ������ ����
		ExprTreeNode* left; // ��������� �� ����� ���������
		ExprTreeNode* right; // ��������� �� ������ ���������
	};
	// ��������������� ����� ��� ����������� ��������� ������
	void showHelper(ExprTreeNode* p, int level) const;
	// ��������������� ����� ��� ���������� ������
	void buildHelper(ExprTreeNode*& node);
	// �������� ���� ������
	ExprTreeNode* root;
};
#endif