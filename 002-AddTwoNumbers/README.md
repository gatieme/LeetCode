#链接
-------

>LeetCode题目： https://leetcode.com/problems/add-two-numbers/
>
>GitHub代码 ：https://github.com/gatieme/LeetCode/tree/master/002-AddTwoNumbers
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/50809402


#描述
-------

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

Subscribe to see which companies asked this question

这道题其实是大数相加的处理，没什么难度，但需要注意以下几点：

*	因为存储是反过来的，即数字342存成2->4->3，所以要注意进位是向后的；

*	链表l1和l2长度可能不同，因此要注意处理某个链表剩余的高位；

*	最高位如果有进位，那么需要新增一个结点存储最高进位

*	每一位都是0~9的数字，不会超过一个位

#思路
-------

##链表单独进位处理
-------

###C++
-------
思路非常简单，利用两个指针分别遍历两个链表，并且用一个变量表示是否有进位。某个链表遍历结束之后再将另一个链表连接在结果链表之后即可，若最后有进位需要添加一位。
```
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

#define DEBUG



#ifdef DEBUG
class ListNode
{
public :
    ListNode( )
    :val(0), next(NULL)
    {
    }

	ListNode(int x)
	:val(x), next(NULL)
	{
	}

    int val;
	ListNode *next;

};

#endif




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
public :
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.

        if((l1 == NULL) && (l2 == NULL))
        {
            return NULL;
        }
        int sum = 0;
        int carry = 0;     //  进位
        int current = 0;

        ListNode *p = new ListNode(0);
        ListNode *start = p;

        sum = l1->val + l2->val + carry;
        carry = sum / 10;

		p->val = sum % 10;

		l1 = l1->next;
		l2 = l2->next;

        while(l1 != NULL && l2 != NULL)
        {
            sum = l1->val + l2->val + carry;
            carry = sum / 10;

            p->next = new ListNode((int)sum % 10);
            p = p->next;

        	l1 = l1->next;
        	l2 = l2->next;
        }

		//  处理多出的位，因为两个链表可能不一样长度
		if(l1 != NULL)
		{
			while(l1 != NULL)
			{
				sum = l1->val + carry;
				carry = sum / 10;

				p->next = new ListNode((int)sum % 10);
            	p = p->next;

            	l1 = l1->next;
			}
		}
		else if(l2 != NULL)
		{
			while(l2 != NULL)
			{
				sum = l2->val + carry;
				carry = sum / 10;

				p->next = new ListNode((int)sum % 10);
            	p = p->next;

            	l2 = l2->next;
			}
		}

        if(carry != 0)
        {
            p->next = new ListNode((int)carry);
            p = p->next;
        }

        return start;
    }
};


#ifdef DEBUG

int main( int argc, char *argv[] )
{
	ListNode l1[5], l2[5];
	ListNode *pl1 = &l1[0], *pl2 = &l2[0];

	//  Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	//  Output: 7 -> 0 -> 8
	l1[0].val = 2;l1[0].next = &l1[1];
	l1[1].val = 4;l1[1].next = &l1[2];
	l1[2].val = 7;l1[2].next = NULL;

	l2[0].val = 5;l2[0].next = &l2[1];
	l2[1].val = 6;l2[1].next = &l2[2];
	l2[2].val = 7;l2[2].next = NULL;

    Solution solu = Solution();
    ListNode *currNode = solu.addTwoNumbers(pl1, pl2);


	std::cout <<currNode->val;
	while(currNode->next != NULL)
	{
        currNode = currNode->next;
		std::cout <<" -> " <<currNode->val;
	}

    return EXIT_SUCCESS;
}
#endif
```

###Python
-------
```
#!/usr/bin/env python
#coding=utf-8
#
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @return a ListNode
    def addTwoNumbers(self, l1, l2):
        ret = ListNode(0)
        cur = ret

        sum = 0
        while True:
            if l1 != None:
                sum += l1.val
                l1 = l1.next
            if l2 != None:
                sum += l2.val
                l2 = l2.next

            cur.val = sum % 10
            sum /= 10
            if l1 != None or l2 != None or sum != 0:
                cur.next = ListNode(0)
                cur = cur.next
            else:
                break

        return ret


# debug
s = Solution()

```

##换算成整数求和
-------
将两个链表直接换算成两个整数
这样的话，我们两个整数可以直接求和，而不用考虑各位的进位问题
最后再进行处理，将和再转换为链表
```
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

#define DEBUG



#ifdef DEBUG
class ListNode
{
public :
    ListNode( )
    :val(0), next(NULL)
    {
    }
    
	ListNode(int x)
	:val(x), next(NULL)
	{
	}
	
    int val;
	ListNode *next;
	
	
};

#endif




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
public :
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
 {  
        // IMPORTANT: Please reset any member data you declared, as  
        // the same Solution instance will be reused for each test case.  
          
        if((l1 == NULL) && (l2==NULL))
        {  
            return NULL;  
        }  
        
        unsigned long long sum1 = 0;  
        unsigned long long sum2 = 0;  
        unsigned long long sum3 = 0;  
        
        //  位数
        int count1 = 0; 
        int count2 = 0;  
        
        // 2 -> 4 -> 3
        while(l1 != NULL)  
        {  
            sum1 += pow(10, count1) * (l1->val);  
            count1++;  
            l1 = l1->next;  
        }  
        while(l2 != NULL)  
        {
            sum2 += pow(10, count2) * (l2->val);  
            count2++;  
            l2=l2->next;  
        }  

        sum3 = sum1 + sum2;  

#ifdef DEBUG
        std::cout <<sum1 <<" + " <<sum2 <<" = " <<sum3 <<std::endl;
#endif
        unsigned long tmp_digit = sum3 % 10;  
        sum3 = sum3 / 10;  

        ListNode* p = new ListNode((int)tmp_digit);  
        ListNode* start = p;  
          
        while(sum3 > 0)
        {  
            
            tmp_digit = sum3 % 10;
            sum3 /= 10;  
            
            p->next = new ListNode((int)tmp_digit);  
            p = p->next;  
        }  
        p->next = NULL;
        //printList(start);  
        return start;  
    }
};


#ifdef DEBUG

int main( int argc, char *argv[] )
{
	ListNode l1[3], l2[3];
	ListNode *pl1 = &l1[0], *pl2 = &l2[0];
	
	//  Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	//  Output: 7 -> 0 -> 8
	l1[0].val = 2;l1[0].next = &l1[1];
	l1[1].val = 4;l1[1].next = &l1[2];
	l1[2].val = 3;l1[2].next = NULL;
	
	l2[0].val = 5;l2[0].next = &l2[1];
	l2[1].val = 6;l2[1].next = &l2[2];
	l2[2].val = 4;l2[2].next = NULL;
	
    Solution solu = Solution();
    ListNode *currNode = solu.addTwoNumbers(pl1, pl2);

		
	std::cout <<currNode->val;	
	while(currNode->next != NULL)	
	{
        currNode = currNode->next;
		std::cout <<" -> " <<currNode->val;
	}

    
    return EXIT_SUCCESS;
}
#endif

```
