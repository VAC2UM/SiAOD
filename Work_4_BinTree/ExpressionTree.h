#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename DataType>
class ExprTree {
public:
	// Конструктор по умолчанию
	ExprTree();
	// Конструктор копирования
	ExprTree(const ExprTree& source);
	// Метод для построения дерева
	void build();
	// Метод для вывода арифметического выражения
	void expression() const;
	// Метод для вычисления значения выражения
	DataType evaluate() const throw (logic_error);
	// Метод для проверки эквивалентности двух деревьев
	bool isEquivalent(const ExprTree& source) const;
	// Метод для отображения структуры дерева
	void showStructure() const;
private:
	// Вложенный класс для представления узла дерева
	class ExprTreeNode {
	public:
		// Конструктор узла
		ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr);
		char dataItem; // Данные узла
		ExprTreeNode* left; // Указатель на левое поддерево
		ExprTreeNode* right; // Указатель на правое поддерево
	};
	// Вспомогательный метод для отображения структуры дерева
	void showHelper(ExprTreeNode* p, int level) const;
	// Вспомогательный метод для построения дерева
	void buildHelper(ExprTreeNode*& node);
	// Корневой узел дерева
	ExprTreeNode* root;
};
#endif