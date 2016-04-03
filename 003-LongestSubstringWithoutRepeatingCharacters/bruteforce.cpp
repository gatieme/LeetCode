/*

Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for “abcabcbb” is “abc”, which the length is 3. For “bbbbb” the longest substring is “b”, with the length of 1.

该题目就是求最长的无重复字符的子串。

一开始简单粗暴的用两层循环实现了，结果可想而知，超时

谢谢度娘，谢谢各位大牛前辈，用贪心算法，一层循环实现，效率不错,O(n)

last数组简直神一般存在，完美解决我两层循环的问题！！

贪心算法不是万能的，有些情况就不使用，比如局部最优解，最后可能并非全局最优解。

本题目中，最长无重复子串肯定包含在两个重复字符之间，用len保存当前最长的子串。如果某两个重复字符之间的子串长于len,则给len赋值这个新的长度。

 */
#include <iostream>
#include <string>


#include <cstring>
#include <cmath>
#include <cstdlib>

#define DEBUG

	
/*
==暴力法==
*/

class Solution
{
private:
    bool canUse[256];

public:
    int lengthOfLongestSubstring(std::string s)
    {
   		// ==暴力法==
   		//  循环所有子串
   		//  判断该子串是否重复
   		std::string subs;
   		int length, maxlength = 0; 
	   	for(int start = 0; start < s.size(); start++)
   		{
   			for(int length = 1; length <= s.size() - start; length++)
			{
				subs = s.substr(start, length);
				std::cout <<subs <<std::endl;
				if()
			}
		}
    }
private :
	bool CheckString(std::string str)
	{
	int is[26] = {0};
		
		for(int pos = 0; pos < str.size(); pos++)
		{
			is[str[pos] - 'a']++;
			if(is[str[pos] - 'a'] > 2)
		}
	}
	
	
};

#ifdef DEBUG
int main(void)
{
    Solution solu = Solution();

    std::cout <<solu.lengthOfLongestSubstring("abcabcbb") <<std::endl;
    
    return EXIT_SUCCESS;
}

#endif