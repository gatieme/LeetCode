#include <iostream>
#include <vector>
#include <algorithm>

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

class Comp
{
 public:
    bool operator() (const ListNode* left, const ListNode* right) const
    {
        return (left->val > right->val);
    }
};

class Solution
{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {

        /// 将空链表
        vector<ListNode*>::iterator it = lists.begin();
        while(it != lists.end())
        {
            if(*it == NULL)
            {
                lists.erase(it);
            }
            else
            {
                ++it;
            }
        }
        if(lists.size( ) == 0)
        {
            return NULL;
        }

        ListNode *head = NULL;
        ListNode *curr = NULL;
        //  首先构造一个小顶堆
        //  这个操作会对lists中每个链表的第一个元素组成的序列建立一个堆
        make_heap(lists.begin( ), lists.end( ), Comp( ));
        while(lists.size() > 0)
        {
#ifdef __tmain
            for(int i = 0; i < lists.size( ); i++)
            {
                cout <<"第" <<i <<"个链表的首元素" <<lists[i]->val <<endl;
            }
#endif // __tmain

            //  堆顶的元素就是最小的元素
            ListNode *smallNode = lists[0];
#ifdef __tmain
            std::cout <<"最小的元素" <<smallNode->val <<endl;
#endif // __tmain

            //  将smallNode插入到新链表中
            if(head == NULL)
            {
                curr = smallNode;
                head = smallNode;
            }
            else
            {
                curr->next = smallNode;
                curr = curr->next;
            }

            //  将最小的元素弹出


            //  BUG, 不能简单的使用pop操作,
            //  因为数据结构是链表不是数组
            //  如果将首指针弹出后, 会丢失整个单链表
            //  我们期待做的仅仅是需改指针的指向
            //  因此可以这么处理
            //  当链表中仍然有元素时, 仅仅修改首元素指针的指向
            //  只有当当前链表无其他元素时, 可直接弹出

            //pop_heap把堆顶元素取出来，放到了数组或者是vector的末尾，用原来末尾元素去替代，
            pop_heap(lists.begin( ), lists.end( ), Comp( ));
            //  此时smallNode被交换到了末尾
#ifdef __tmain
            cout <<bool(smallNode == lists[lists.size( ) - 1]) <<endl;
#endif // __tmain

            if(lists[lists.size( ) - 1]->next == NULL)       //  如果当前链表已经没有其他元素了那么可以直接弹出
            {

                lists.pop_back( );               //  将为指针弹出后，相当于把整个单链表从lists中删除
            }
            else            //  当前最小元素所在的链表仍有其他元素， 仅仅修改首元素的指向
            {
                //  使用二重指针修改其指向或者直接用list[0]修改
                //ListNode **node = &lists[0];
                //*node = (*node)->next;
                lists[lists.size( ) - 1] = lists[lists.size( ) - 1]->next;

                push_heap(lists.begin( ), lists.end( ), Comp( ));

            }


        }

        return head;

    }
};



int __tmain( )
{
    ListNode list1[2];
    list1[0].val = -1;
    list1[0].next = &list1[1];
    list1[1].val = 1;
    list1[1].next = NULL;

    ListNode list2[3];
    list2[0].val = -3;
    list2[0].next = &list2[1];
    list2[1].val = 1;
    list2[1].next = &list2[2];
    list2[2].val = 4;
    list2[2].next = NULL;

    ListNode list3[4];
    list3[0].val = -2;
    list3[0].next = &list3[1];
    list3[1].val = -1;
    list3[1].next = &list3[2];
    list3[2].val = 0;
    list3[2].next = &list3[3];
    list3[3].val = 2;
    list3[3].next = NULL;

    vector<ListNode *> lists;
    lists.push_back(list1);
    lists.push_back(list2);
    lists.push_back(list3);

    Solution solu;
    ListNode *head = solu.mergeKLists(lists);
    while(head != NULL)
    {
        cout <<" "<<head->val;
        head = head->next;
    }

    return 0;
}
