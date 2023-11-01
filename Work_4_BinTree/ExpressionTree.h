#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename DataType>
class ExprTree {
public:
    ExprTree();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);
    ~ExprTree();

    void build();
    void expression() const;
    DataType evaluate() const throw (logic_error);
    void clear();
    void commute();
    bool isEquivalent(const ExprTree& source) const;

    void showStructure() const;

private:

    class ExprTreeNode {
    public:
        // Constructor
        ExprTreeNode(char elem,
            ExprTreeNode* leftPtr, ExprTreeNode* rightPtr);

        char dataItem;
        ExprTreeNode* left, * right;
    };

    void showHelper(ExprTreeNode* p, int level) const;
    DataType evalHelper(ExprTreeNode* p) const;
    void buildHelper(ExprTreeNode*& node);
    void copyHelper(ExprTreeNode*& dest, ExprTreeNode* source);
    void expressionHelper(ExprTreeNode* p) const;
    void clearHelper(ExprTreeNode*& p);
    void commuteHelper(ExprTreeNode*& p);
    bool isEquivHelper(ExprTreeNode* dest, ExprTreeNode* source) const;

    ExprTreeNode* root;
};

#endif