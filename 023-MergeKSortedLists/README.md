#链接
------- 

>LeetCode题目：https://leetcode.com/problems/generate-parentheses
>
>GitHub代码：https://github.com/gatieme/LeetCode/tree/master/022-GenerateParentheses
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51095236


#题意
-------

>Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. 

将k个已排好序的链表合并为一个排序的链表。


看到最近有人问K-way merge, 我正好也总结到了Linked List。K-way merge最典型的解法就是用heap了，时间复杂度可以达到n*logk。

#常规归并算法

-------



第一次思考的时候，想得比较自然。打算仿照归并排序的思路来进行。

每次都在K个元素中选择一个最小的出来。每次选择最小的时间复杂度是O(K)，这样的事情一共做了O(N)次(假设一共有N个元素)。

另外注意需要考虑一些情况，比如 lists[i]如果在作为函数的输入，可能会在一开始就是NULL；处理到中途，可能lists[i]对应的单链表从非空变化为了空。
```cpp
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

```

这么暴力的解法， **Time Limit Exceeded**


#使用堆或者优先队列优化选择最小值时时间复杂度
-------

那好，我们看看有没有改进的空间

每次从K个元素中找到最小的1个元素放入新链表的过程，其实就是每次找到最小的1个数的过程，这个过程可以用STL中的Algorithm库中的**最小堆**来实现。

这样每次从K个元素中找到最小的元素只需要O(1)的时间复杂度，然后调整新的堆也只需要O(lgK)的时间复杂度


将每个链表的表头元素取出来，建立一个小顶堆，因为k个链表中都排好序了，因此每次取堆顶的元素就是k个链表中的最小值，可以将其合并到合并链表中，再将这个元素的指针指向的下一个元素也加入到堆中，再调整堆，取出堆顶，合并链表。。。。以此类推，直到堆为空时，链表合并完毕。



##使用STL的heap算法

-------



```cpp
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


```



##自己实现的heap

-------

因为想练习建堆的过程，所以我又写了一份不用STL里的make_heap等方法，而是自己写的建堆函数。

>参见http://www.cnblogs.com/skysand/p/4300711.html

建堆的时间复杂度是k/2logk, 每次取出堆顶再加入元素的复杂度是logk,假设每条链表平均有n个元素，则一共有nk-k次。因此总的时间复杂度为O(nklogk)。


```cpp


class Comp
{
 public:
    bool operator() (const ListNode* left, const ListNode* right) const
    {
        return (left->val > right->val);
    }
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        // 使用堆排序,
        // 1. 选出每个链表的头来插入小顶堆中，
        // 2. 再把堆顶接入合并链表中，
        // 3. 被选出的指针后移再加入小顶堆中,回到2
        // 4. 最后所有链表都为空时，返回合并链表的头指针
        if(lists.empty()) return nullptr;
        vector<ListNode* > heap;
        // 1. 选出每个链表的头来插入小顶堆中，
        for(int i = 0; i != lists.size(); i ++)
        {
            if(lists[i])
            {
                heap.push_back(lists[i]);
            }
        }
        makeHeap(heap);
        // 2. 再把堆顶接入合并链表中，
        ListNode head(-1); // 合并链表的表头
        ListNode* p = &head;
        while(!heap.empty())
        {
            auto minNode = popHeap(heap);
            p->next = minNode; // 接入链表
            p = p->next;
            // 3. 被选出的指针后移再加入小顶堆中,回到2
            auto next = minNode->next;
            if(next) pushHeap(heap, next);
        }
        // 4. 最后所有链表都为空时，返回合并链表的头指针
        return head.next;
    }

    // 建立小顶堆
    // 自低向上
    void makeHeap(vector<ListNode*> &heap){
        // 从最后一个元素的父节点开始建立小顶堆
        for(int i = heap.size()/2; i >0 ; i --)
        {
            minHeap(heap, i);
        }
    }
    // 调整小顶堆,以第i个元素为根建立小顶堆
    //位置从1开始，取元素时记得-1
    // 自顶向下
    void minHeap(vector<ListNode*> &heap, int i){
        int l = i*2;
        int r = l+1;
        int least(i);
        // 算出最小元素的位置
        if((l< heap.size()+1) && heap[l-1]->val<heap[i-1]->val )
        {
            // 如果没有超过边界并且左孩子比父亲小，则换
            least = l;
        }
        if(r<heap.size()+1 && heap[r-1]->val<heap[least-1]->val)
        {
            // 如果没有超过边界并且右孩子最小，则换
            least = r;
        }
        if(least != i)
        {
            swap(heap[i-1], heap[least-1]);
            minHeap(heap, least);
        }
    }
    // 在小顶堆中插入一个元素
    // 自低向上
    void pushHeap(vector<ListNode*> &heap, ListNode* p)
    {
        heap.push_back(p);
        int child = heap.size();
        int parent = child/2;
        for(int child = heap.size(),parent = child/2; parent; child--, parent = child/2)
        {
            if(heap[child-1]->val < heap[parent-1]->val)
                {
                swap(heap[child-1], heap[parent-1]);
            }
        }
    }
    // 弹出堆顶
    ListNode* popHeap(vector<ListNode*> &heap)
    {
        swap(heap[0], heap[heap.size()-1]);
        auto p = heap.back();
        heap.pop_back();
        minHeap(heap, 1);
        return p;
    }
};
```



后来想到既然堆每次加入一个元素的时候都要调整堆顶，那么每次把要添加的元素换到堆顶再调整就不用写pushHeap的函数了，当要添加的元素为空时，相当于执行popHeap函数，因此可以简化代码：



```cpp

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // 使用堆排序, 
        // 1. 选出每个链表的头来插入小顶堆中，
        // 2. 再把堆顶接入合并链表中，
        // 3. 被选出的指针后移再加入小顶堆中,回到2
        // 4. 最后所有链表都为空时，返回合并链表的头指针
        if(lists.empty()) return nullptr;
        vector<ListNode* > heap;
        // 1. 选出每个链表的头来插入小顶堆中，
        for(int i = 0; i != lists.size(); i ++){
           if(lists[i]) heap.push_back(lists[i]);
        }
        makeHeap(heap);
        // 2. 再把堆顶接入合并链表中，
        ListNode head(-1); // 合并链表的表头
        ListNode* p = &head;
        while(!heap.empty()){
            auto minNode = heap[0];
            p->next = minNode; // 接入链表
            p = p->next;
            // 3. 被选出的指针后移再加入小顶堆中,回到2
            auto next = minNode->next;
            if(next) {
                heap[0] = next;
            }else{
                swap(heap[0], heap[heap.size()-1]);
                heap.pop_back();
            }
            minHeap(heap, 1);
        }
        // 4. 最后所有链表都为空时，返回合并链表的头指针
        return head.next;
    }
    // 建立小顶堆
    // 自低向上
    void makeHeap(vector<ListNode*> &heap){
        // 从最后一个元素的父节点开始建立小顶堆
        for(int i = heap.size()/2; i >0 ; i --){
            minHeap(heap, i);
        }
    }
    // 小顶堆,以第i个元素为根建立小顶堆
    //位置从1开始，取元素时记得-1
    // 自顶向下
    void minHeap(vector<ListNode*> &heap, int i){
        int l = i*2;
        int r = l+1;
        int least(i);
        // 算出最小元素的位置
        if((l< heap.size()+1) && heap[l-1]->val<heap[i-1]->val ){
            // 如果没有超过边界并且左孩子比父亲小，则换
            least = l;
        }
        if(r<heap.size()+1 && heap[r-1]->val<heap[least-1]->val){
            // 如果没有超过边界并且右孩子最小，则换
            least = r;
        }
        if(least != i){
            swap(heap[i-1], heap[least-1]);
            minHeap(heap, least);
        }
    }
};

```





##基于优先队列的方法

-------



```cpp

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
        int length = lists.size();
        ListNode head(-1);
        ListNode* pTail = &head;
        priority_queue<ListNode*, vector<ListNode*>, Comp> list_queue;
        for (int i=0; i<length; i++)
        {
            if (lists[i])
                list_queue.push(lists[i]);
        }

        while (list_queue.size() >0)
        {
            ListNode* ptmpNode = list_queue.top();
            list_queue.pop();
            pTail->next = ptmpNode;
            pTail = pTail->next;
            if (ptmpNode->next)
                list_queue.push(ptmpNode->next);
        }

        pTail->next = NULL;

        return head.next;
    }
};

```



#简化为两个链表合并

-------

还有一种思路是取出两条，

用merge2Lists的方法合并为一条，再将这条和下一条用merge2Lists来合并为一条，以此类推。假设每条链表平均有n个元素，此种时间复杂度是O(2n+3n+…+kn), 为O(nk²),因此若用此法会超时。



##递归的进行两个链表的合并

-------



首先是两个链表合并的算法

```cpp
  ListNode* mergeTwoLists(ListNode* left, ListNode* right)
    {
        if(left == NULL && right == NULL)       //  两个链表均为空
        {
            return NULL;
        }
        else if(left != NULL && right == NULL)  //  left不为空, right为空
        {
            return left;
        }
        else if(left == NULL && right != NULL)  //  left为空, right不为空
        {
            return right;
        }

        //  先生成头结点
        ListNode *head = NULL;
        if(left->val < right->val)
        {
            head = left;
            left = left->next;
            //cout <<left->val <<"in list" <<endl;
        }
        else
        {
            head = right;
            right = right->next;
            //cout <<right->val <<"in list" <<endl;
        }

        //  遍历两个链表
        ListNode *curr = head;
        while(left != NULL && right != NULL)
        {
            //  每次找到一个小的加入新的链表
            //cout <<"left = " <<left->val <<", right = " <<right->val <<endl;
            if(left->val < right->val)
            {
                //cout <<left->val <<"in list" <<endl;

                curr->next = left;
                curr = curr->next;

                left = left->next;
            }
            else
            {
                //cout <<right->val <<"in list" <<endl;

                curr->next = right;
                curr = curr->next;

                right = right->next;
            }
        }

        //  处理较长链表的剩余部分
        if(left != NULL)
        {
            curr->next = left;
        }
        else
        {
            curr->next = right;
        }

        return head;
    }
```



那么我们的算法流程如下

```cpp

    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        int length = lists.size();
        if (length == 0)
            return NULL;
        while (lists.size() >1)
        {
            ListNode* p1 = lists.front ();
            lists.erase(lists.begin());
            ListNode* p2 = lists.front();
            lists.erase(lists.begin());
            lists.push_back(mergeTwoLists(p1, p2));
        }

        return lists[0];
    }
```





##分治拆分

-------

```cpp

    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        int length = lists.size();
        if (length == 0)
        {
            return NULL;
        }
        else if(length == 1)
            return lists[0];
        else if(length == 2)
        {
            return mergeTwoLists(lists[0], lists[1]);
        }

        vector<ListNode*> leftHalf(lists.begin(), lists.begin()+length/2);
        vector<ListNode*> rightHalf(lists.begin()+length/2, lists.end());
        return mergeTwoLists(mergeKLists(leftHalf), mergeKLists(rightHalf));
    }
```