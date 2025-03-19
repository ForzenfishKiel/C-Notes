#include <iostream>
#include <vector>
#include "D:/UE_Project/StudyCpp/AlgorithmTest/Private/AlgorithmTest.h"
using namespace std;

LinkNode* createLinkNode(vector<int>& nums)
{
    LinkNode dummy = LinkNode(0);
    LinkNode* curr = &dummy;  //�������ڵ�
    for(auto it : nums)
    {
        curr->next = new LinkNode(it);  //�������´���һ��ڵ�
        curr = curr->next;  //ָ��ǰ�ڵ�
    }
    return &dummy;  //������������
}

//��������
void AlgorithmTest::PrintLink(LinkNode* head)
{
    if(!head) return;
    LinkNode* curr = head;  //ָ��ָ��ͷ�ڵ�
    while(!curr)
    {
        cout<<curr->val<<" ";
        curr = curr->next;
    }
}

//ָ���������
void AlgorithmTest::InsertLink(LinkNode* head, int val)
{
    LinkNode* curr = head;
    //ͷ�巨
    LinkNode NewLinkNode(val);
    NewLinkNode.next = curr->next;
    curr->next = &NewLinkNode;

    //β�巨
    while(curr->next)
    {
        curr = curr->next;
    }
    LinkNode NewTileLinkNode(val);
    curr->next = &NewTileLinkNode;

    //�м�巨
    curr = head;  //����ָ��ͷ
    while(curr->next)
    {
        if(curr->val = 45)
        {
            LinkNode NewInsertNode(97);
            NewInsertNode.next = curr->next;
            curr->next = &NewInsertNode;
            break;
        }
        curr = curr->next;
    }
    //����ʲô�巨��ʱ�临�Ӷȶ���O(1);
}

void AlgorithmTest::FastAndSlowSearch(LinkNode* head)
{
    //����ָ���ҵ��м�ڵ㣬Ȼ���ָ������������ָ����һ������ָ���ߵ�ͷʱ����ָ���λ�þ����м�ڵ�
    LinkNode* Fast = head;
    LinkNode* Slow = head;

    while(Fast)
    {
        Slow = Slow->next;
        Fast = Fast->next->next;
    }
    cout<<Slow->val<<" ";
    /* ���Ӷȷ���
ʱ�临�Ӷȣ�O(n)����������һ�Ρ�

�ռ临�Ӷȣ�O(1)�� */
}

int main(int argc, char* argv[])
{
    vector<int> arr = {1,6,45,7,9,100};
    LinkNode* TestNode = createLinkNode(arr);
    AlgorithmTest::PrintLink(TestNode); //������ӡ����
    AlgorithmTest::InsertLink(TestNode,5);
    AlgorithmTest::FastAndSlowSearch(TestNode);
    return 0;
}
