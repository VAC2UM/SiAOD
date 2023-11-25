#include "ExpressionTree.h"
#include <ctype.h>

using namespace std;

template<typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL; // Конструктор по умолчанию создает пустое дерево
}
template<typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
	*this = source; // Конструктор копирования
}
template<typename DataType>
void ExprTree<DataType>::build()
{
	buildHelper(root); // Метод для построения дерева
}
template<typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& node)
{
	char c;
	cin >> c;
	node = new ExprTreeNode(c, NULL, NULL); // Узел - это введенный символ
	// Если это оператор, рекурсивно вызываем для левого и правого поддеревьев
	if (c == '+' || c == '-' || c == '*' || c == '/')
	{
		buildHelper(node->left); // Рекурсивный вызов для левого поддерева
		buildHelper(node->right); // Рекурсивный вызов для правого поддерева
	}
}
template<typename DataType>
void ExprTree<DataType>::showStructure() const
{
	if (root == NULL)
		cout << "Пустое дерево" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}
template<typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode* p, int level) const
{
	int j; // Счетчик цикла
	if (p != 0)
	{
		showHelper(p->right, level + 1); // Вывод правого поддерева
		for (j = 0; j < level; j++) // Отступ до уровня
			cout << "\t";
		cout << " " << p->dataItem; // Вывод данных узла
		if ((p->left != 0) && // Вывод "соединителя"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1); // Вывод левого поддерева
	}
}

// Конструктор для внутреннего класса ExprTreeNode, который, используется для создания узлов в дереве выражения.
template<typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}