#链接
------- 

>LeetCode题目：https://leetcode.com/problems/remove-nth-node-from-end-of-list
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51090234

#题意
-------

>Given a linked list, remove the nth node from the end of list and return its head.
>
>For example,
>
>   Given linked list: 1->2->3->4->5, and n = 2.
>
>   After removing the second node from the end, the linked list becomes 1->2->3->5.
>
>Note:
>Given n will always be valid.
>Try to do this in one pass.
>
>Subscribe to see which companies asked this question

删除链表的倒数第n个元素



#分析

-------

双指针思想，两个指针相隔n-1，每次两个指针向后一步，当后面一个指针没有后继了，前面一个指针就是要删除的节点。



*    设置两个指针first跟second。

*    first指针先移动n步，若此时first指针为空，则表示要删除的是头节点，此时直接返回head->next即可。



*    如果first指针不为空，则将两个指针一起移动，直到first指针指向最后一个节点，令second->next=second->next->next即可删除第你n个节点。





```c



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


```



