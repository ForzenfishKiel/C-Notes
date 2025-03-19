#pragma once
using namespace std;
struct BinaryTreeNode
{
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode(int data) : data{data} , left {nullptr}, right{nullptr} {}
};
class TreeAlgorithmTest
{
public:
    static vector<int> PreorderTraversal(BinaryTreeNode *root);  //前序遍历
    static vector<int> InorderTraversal(BinaryTreeNode *root);  //中序遍历
    static vector<int> PostorderTraversal(BinaryTreeNode *root);  //后序遍历
};