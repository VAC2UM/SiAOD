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

        cout << endl << "Введите выражение в префиксной форме: ";

        testExpression.build();
        testExpression.showStructure();
        testExpression.expression();
        cout << " = " << testExpression.evaluate() << endl;
    }
    return 0;
}