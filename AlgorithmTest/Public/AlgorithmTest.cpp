#include <iostream>
#include <vector>
#include "D:/UE_Project/StudyCpp/AlgorithmTest/Private/AlgorithmTest.h"
using namespace std;

LinkNode* createLinkNode(vector<int>& nums)
{
    LinkNode dummy = LinkNode(0);
    LinkNode* curr = &dummy;  //创建根节点
    for(auto it : nums)
    {
        curr->next = new LinkNode(it);  //在链表下创建一块节点
        curr = curr->next;  //指向当前节点
    }
    return &dummy;  //返回真是链表
}

//遍历链表
void AlgorithmTest::PrintLink(LinkNode* head)
{
    if(!head) return;
    LinkNode* curr = head;  //指针指向头节点
    while(!curr)
    {
        cout<<curr->val<<" ";
        curr = curr->next;
    }
}

//指针插入数据
void AlgorithmTest::InsertLink(LinkNode* head, int val)
{
    LinkNode* curr = head;
    //头插法
    LinkNode NewLinkNode(val);
    NewLinkNode.next = curr->next;
    curr->next = &NewLinkNode;

    //尾插法
    while(curr->next)
    {
        curr = curr->next;
    }
    LinkNode NewTileLinkNode(val);
    curr->next = &NewTileLinkNode;

    //中间插法
    curr = head;  //重新指向开头
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
    //无论什么插法，时间复杂度都是O(1);
}

void AlgorithmTest::FastAndSlowSearch(LinkNode* head)
{
    //快慢指针找到中间节点，然后快指针走两步，慢指针走一步，快指针走到头时，慢指针的位置就是中间节点
    LinkNode* Fast = head;
    LinkNode* Slow = head;

    while(Fast)
    {
        Slow = Slow->next;
        Fast = Fast->next->next;
    }
    cout<<Slow->val<<" ";
    /* 复杂度分析
时间复杂度：O(n)。遍历链表一次。

空间复杂度：O(1)。 */
}

int main(int argc, char* argv[])
{
    vector<int> arr = {1,6,45,7,9,100};
    LinkNode* TestNode = createLinkNode(arr);
    AlgorithmTest::PrintLink(TestNode); //遍历打印链表
    AlgorithmTest::InsertLink(TestNode,5);
    AlgorithmTest::FastAndSlowSearch(TestNode);
    return 0;
}
