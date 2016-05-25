#include <iostream>
#include <vector>

using namespace std;

#define __tmain main

#ifdef __tmain

struct ListNode
{
public :
    int val;
    ListNode *next;
    ListNode(int x = 0) : val(x), next(NULL) {}
};

#endif // __tmain

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        ListNode *head = NULL;
        ListNode *curr = NULL;
        ListNode maxNode(INT_MAX);

        while(lists.size() > 0)
        {
            //  寻找当前最小的那个链表结点
            ListNode *smallNode = &maxNode;
            int smallIndex = -1;
            for(int i = 0; i < lists.size(); i++)
            {
                ListNode *indexNode = lists[i];
                if(indexNode == NULL)       //  当前链表已经不够长了
                {
#ifdef __tmain
                    std::cout <<"第i个链表已经空了" <<endl;
#endif
                }
                else if(indexNode->val < smallNode->val)    //  当前节点比当前最小的要小
                {
                    //  保存最小的节点和最小节点的位置
                    smallNode = indexNode;
                    smallIndex = i;
                }
            }
            if(smallIndex == -1)
            {
#ifdef __tmain
                cout <<"链表已经为NULL" <<endl;
#endif
                break;
            }
            else
            {
#ifdef __tmain
                cout <<"最小的结点位于" <<smallIndex <<", 值为" <<smallNode->val <<endl;
#endif

            }

            //  循环结束后, 最小节点位于第i个链表的smallNode位置
            //  将它加入到链表中,同时需要将该链表的指针域后移一位


            //  将smallNode插入到新链表中
            if(curr == NULL)
            {
                curr = smallNode;
                head = smallNode;
            }
            else
            {
                curr->next = smallNode;
                curr = curr->next;
            }

            //  将smallNode所指向的链表指针后移一位
            ListNode **node = &lists[smallIndex];       //  要修改指针的指向需要指针的指针
            *node = (*node)->next;
        }

        return head;

    }
};



int __tmain( )
{
    ListNode list1[2];
    list1[0].val = 1;
    list1[0].next = &list1[1];
    list1[1].val = 3;
    list1[1].next = NULL;

    ListNode list2[3];
    list2[0].val = 2;
    list2[0].next = &list2[1];
    list2[1].val = 4;
    list2[1].next = &list2[2];

    list2[2].val = 5;
    list2[2].next = NULL;


    vector<ListNode *> lists;
    lists.push_back(list1);
    lists.push_back(list2);

    Solution solu;
    ListNode *head = solu.mergeKLists(lists);
    while(head != NULL)
    {
        cout <<" "<<head->val;
        head = head->next;
    }

    return 0;
}
