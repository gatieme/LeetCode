#include <iostream>

using namespace std;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#define __tmain main


#ifdef __tmain

struct ListNode
{
public :
    int val;
    ListNode *next;
    //ListNode(int x) : val(x), next(NULL) {};
};

#endif // __tmain

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *first = head;
        ListNode *second = head;
        int i;

        //  空节点的情况
        if(head == NULL || head->next == NULL)
        {
            return NULL;
        }

        //  first指针向走N步
        for(i = 0; i < n && first != NULL; i++)
        {
            first = first->next;
        }

        if(first == NULL && i < n)      //  结点长度不够
        {
            return head;
        }
        else if(first == NULL && i == n)
        {
            //cout <<"找到了尾巴" <<endl;
            // 倒数第N个结点正好是头结点
            second = head;
            delete second;
            head = head->next;
            return head;
        }

        while(first->next != NULL)
        {
            first = first->next;
            second = second->next;
        }
        //  此时second就是第倒数N+1个结点
        //  即倒数第N个节点的前一个结点

        //  下面删除第N个结点
        ListNode *p = second->next;
        second->next = p->next;
        delete p;
        return head;

    }
};

int __tmain()
{
    ListNode list[2];
    list[0].val = 1;
    list[0].next = &list[1];
    list[1].val = 2;
    list[1].next = NULL;

    Solution solu;
    solu.removeNthFromEnd(list, 2);
    return 0;
}
