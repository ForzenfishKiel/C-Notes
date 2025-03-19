#pragma once
using namespace std;
struct LinkNode
{
    int val; //节点储存的值
    LinkNode* next;  //指向下一个节点的类指针
    LinkNode(int InVal) : val(InVal), next(nullptr) {}
};
class AlgorithmTest
{
public:
    static void PrintLink(LinkNode* head);
    static void InsertLink(LinkNode* head, int val);
    static void FastAndSlowSearch(LinkNode* head);
};