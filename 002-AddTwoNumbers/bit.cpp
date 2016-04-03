/*
2. Add Two Numbers

Difficulty: Medium

You are given two linked lists representing two non-negative numbers.

The digits are stored in reverse order and each of their

nodes contain a single digit.

Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

Subscribe to see which companies asked this question

Hide Tags Linked List Math
Hide Similar Problems (M) Multiply Strings (E) Add Binary

*/

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



	friend std::istream &operator>>(std::istream &in, ListNode *head)
	{



	}

	friend std::ostream &operator<<(std::ostream &out, ListNode *head)
	{
		if(head == NULL)
		{
			out <<"NULL LIST" <<std::endl;
			return out;
		}

		ListNode *currNode = head;

		out <<currNode->val;
		while(currNode->next != NULL)
		{
			out <<" -> " <<currNode->val;
		}
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
