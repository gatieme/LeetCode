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
