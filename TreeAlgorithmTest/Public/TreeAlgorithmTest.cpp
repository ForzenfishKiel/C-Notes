#include <iostream>
#include <vector>
#include "D:/UE_Project/StudyCpp/TreeAlgorithmTest/Private/TreeAlgorithmTest.h"

#include <algorithm>
using namespace std;

BinaryTreeNode* CreateTreeNode()
{
    //创建一些新的节点
    BinaryTreeNode* root =new BinaryTreeNode(1);  //创建根节点
    root->left = new BinaryTreeNode(2);
    root->right = new BinaryTreeNode(3);
    root->left->left = new BinaryTreeNode(4);
    root->left->right = new BinaryTreeNode(5);
    root->right->left = new BinaryTreeNode(6);
    return root;
}

//前序遍历，每次停留的节点都是一个根节点
void preorderTraversal(BinaryTreeNode* root, vector<int>& result) {
    if (!root) return;  //若访问的当前节点（看作根节点）
    result.push_back(root->data);     // 访问根节点  //然后存入数组
    preorderTraversal(root->left, result);  // 遍历左子树
    preorderTraversal(root->right, result); // 遍历右子树
}

//前序遍历入口
vector<int> TreeAlgorithmTest::PreorderTraversal(BinaryTreeNode* root)
{
    vector<int> res;
    preorderTraversal(root, res);
    return res;
}

void inorderTraversal(BinaryTreeNode* root , vector<int>& result)
{
    if(!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->data);
    inorderTraversal(root->right, result);
}

//中序遍历入口
vector<int> TreeAlgorithmTest::InorderTraversal(BinaryTreeNode* root)
{
    vector<int> res;
    inorderTraversal(root, res);
    return res;
}

void postorderTraversal(BinaryTreeNode* root , vector<int>& result)
{
    if(!root) return;
    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result.push_back(root->data);
}
//后序遍历入口
vector<int> TreeAlgorithmTest::PostorderTraversal(BinaryTreeNode* root)
{
    vector<int> res;
    postorderTraversal(root, res);
    return res;
}

int main(int argc, char* argv[])
{
    BinaryTreeNode* Tree = CreateTreeNode();  //获取初始化好的树
    vector<int> res = TreeAlgorithmTest::PreorderTraversal(Tree);
    for_each(res.begin(), res.end(), [](int i){cout << i << " ";});

    cout<<"\n";

    vector<int>InorderRes = TreeAlgorithmTest::InorderTraversal(Tree);
    for_each(InorderRes.begin(), InorderRes.end(), [](int i){cout << i << " ";});

    cout<<"\n";
    
    vector<int>PostorderRes = TreeAlgorithmTest::PostorderTraversal(Tree);
    for_each(PostorderRes.begin(), PostorderRes.end(), [](int i){cout << i << " ";});
    return 0;
}
