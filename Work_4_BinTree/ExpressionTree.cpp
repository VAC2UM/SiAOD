#include "ExpressionTree.h"
#include <ctype.h>
using namespace std;

template<typename DataType>

ExprTree<DataType>::ExprTree()
{
    root = NULL;
}

template<typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
    *this = source;
}

template<typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>&
    source)
{
    if (this == &source)
        return *this;

    copyHelper(root, source.root);
    return *this;
}

template<typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode*& dest, ExprTreeNode* source)
{
    if (source != NULL)
    {
        ExprTreeNode* left = NULL;  //Store the possible left node
        ExprTreeNode* right = NULL; //Store the possible right node
        copyHelper(left, source->left); //Recursively call left
        copyHelper(right, source->right);   //Recursively call right
        dest = new ExprTreeNode(source->dataItem, left, right); //Copy the node
    }
}

template<typename DataType>
ExprTree<DataType>::~ExprTree()
{
    clear();
}

template<typename DataType>
void ExprTree<DataType>::build()
{
    buildHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& node)
{
    char c;
    cin >> c;
    node = new ExprTreeNode(c, NULL, NULL); //The node is the character entered

    //If it's an operator, recursively call -- digits are leafs
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        buildHelper(node->left);    //Recursively call left
        buildHelper(node->right);   //Recursively call right
    }
}

template<typename DataType>
void ExprTree<DataType>::expression() const
{
    expressionHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::expressionHelper(ExprTreeNode* p) const
{
    //Base case, if it's a digit, simply print out the number
    if (isdigit(p->dataItem))
    {
        cout << p->dataItem;
        return;
    }
    //Build the parenthesis around the expression
    cout << '(';
    expressionHelper(p->left);  //Recursively call left
    cout << p->dataItem;
    expressionHelper(p->right); //Recursively call right
    cout << ')';
}

template<typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
    if (root == NULL)
        throw("ExprTree is empty.");
    return evalHelper(root);
}

template<typename DataType>
DataType ExprTree<DataType>::evalHelper(ExprTreeNode* p) const
{
    switch (p->dataItem)
    {
    case '+':
        return (evalHelper(p->left) + evalHelper(p->right));
        break;
    case '-':
        return (evalHelper(p->left) - evalHelper(p->right));
        break;
    case '*':
        return (evalHelper(p->left) * evalHelper(p->right));
        break;
    case '/':
        return (evalHelper(p->left) / evalHelper(p->right));
        break;
    default:
        return (p->dataItem - '0');
        break;
    }
}

template<typename DataType>
void ExprTree<DataType>::clear()
{
    clearHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode*& p)
{
    //Node is not null, so must be deleted
    if (p != NULL)
    {
        clearHelper(p->left);   //Recursively call left
        clearHelper(p->right);  //Recursively call right
        delete p;   //Delete the node
        p = NULL;   //Set to null for dangling pointer
    }
}

template<typename DataType>
void ExprTree<DataType>::commute()
{
    commuteHelper(root);
}

template<typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode*& p)
{
    //Base case, cannot commute if node is null
    if (p == NULL)
        return;
    //If the character is an operator, then switch the nodes
    if (!isdigit(p->dataItem))
    {
        ExprTreeNode* temp = p->left;
        p->left = p->right;
        p->right = temp;
    }
    commuteHelper(p->left);     //Recursively call left
    commuteHelper(p->right);    //Recursively call right
}

template<typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
    return isEquivHelper(root, source.root);
}

template<typename DataType>
bool ExprTree<DataType>::isEquivHelper(ExprTreeNode* dest,
    ExprTreeNode* source) const
{
    //It's equivalent if the nodes are empty
    if (dest == NULL && source == NULL)
        return true;
    //The nodes aren't empty
    else if (dest != NULL && source != NULL)
    {
        //The two data items are equivalent
        if (dest->dataItem == source->dataItem)
        {
            //Check if non-swap is equivalent
            if (isEquivHelper(dest->left, source->left) &&
                isEquivHelper(dest->right, source->right))
                return true;
            //Check is swap is equivalent
            else if (isEquivHelper(dest->left, source->right) &&
                isEquivHelper(dest->right, source->left))
            {
                //Addition and multiplication can commute
                if (dest->dataItem == '+' || dest->dataItem == '*')
                    return true;
                //Subtraction and division cannot commute
                else
                    return false;
            }
            else
                return false;
        }
    }
    return false;
}

template<typename DataType>
void ExprTree<DataType>::showStructure() const
{
    if (root == NULL)
        cout << "Empty tree" << endl;
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
    int j;   // Loop counter

    if (p != 0)
    {
        showHelper(p->right, level + 1);        // Output right subtree
        for (j = 0; j < level; j++)   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ((p->left != 0) &&          // Output "connector"
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        cout << endl;
        showHelper(p->left, level + 1);         // Output left subtree
    }
}

template<typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr,
    ExprTreeNode* rightPtr)
{
    dataItem = elem;
    left = leftPtr;
    right = rightPtr;
}