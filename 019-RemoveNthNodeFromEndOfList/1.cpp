/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

 #include <iostream>

using namespace std;

struct ListNode
{
public :
    int val;
    ListNode *next;
    //ListNode(int x) : val(x), next(NULL) {};
};


class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL)
        {
            return NULL;
        }
        ListNode *pPre = NULL;
        ListNode *second = head;
        ListNode *first = head;

        //  先让first指针向前走N - 1步
        for(int i = 0; i < n - 1; i++)
        {
            first = first->next;
        }

        while(first->next)
        {
            pPre = second;              //  保存second结点为前一个结点
            first = first->next;
            second = second->next;
        }

        if (pPre == NULL)               //  如果倒数第N个节点的前一个结点为NULL
        {
            head = second->next;
            //delete second;
        }
        else
        {
            pPre->next = second->next;
            //delete second;
        }

        return head;
    }
};


int main()
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


