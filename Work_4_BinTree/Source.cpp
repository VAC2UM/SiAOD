#include <iostream>
#include <stdexcept>

using namespace std;

#include "ExpressionTree.cpp"

int main()
{
    setlocale(LC_ALL, "");
    cout << "���� ��������� ������" << endl;
    while (true) {
        ExprTree<float> testExpression;

        cout << endl << "������� ��������� � ���������� �����: ";

        testExpression.build();
        testExpression.showStructure();
        testExpression.expression();
        cout << " = " << testExpression.evaluate() << endl;
    }
    return 0;
}