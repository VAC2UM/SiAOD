#include <iostream>
#include <stdexcept>
using namespace std;
#include "ExpressionTree.cpp"
int main()
{
	setlocale(LC_ALL, "");
	cout << "Тест бинарного дерева" << endl;
	while (true) {
		ExprTree<float> testExpression;
		cout << endl << "Введите префиксное выражение: ";
		testExpression.build();
		testExpression.showStructure();
	}
	return 0;
}