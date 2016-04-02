#define DEBUG
//  最长回文子序列

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

/*

最简单的就是暴力穷举(Brute Force)

对每个start和end位置的子串进行检测，

判断其是否回文。

显然有C(N,2)（组合）个子串。

检测每个子串都需要O(N)的时间，

所以此方法的时间复杂度为O(N3)。

*/
class Solution
{
public:
    std::string longestPalindrome(std::string s)
    {
   		// ==暴力法==
   		//  循环所有子串
   		//  判断该子串是否重复
   		std::string subs, maxsubs;
   		int length, maxlength = 0;
   		int maxlen = 0;

	   	for(int start = 0; start < s.size(); start++)
   		{
   			for(int length = 1; length <= s.size() - start; length++)
			{
				subs = s.substr(start, length);
				//std::cout <<subs <<std::endl;
				if(isPalindromicSubstring(subs) == true
				&& maxlen < subs.length())
				{
					maxlen = subs.length();
					maxsubs = subs;
				}
			}
		}

		return maxsubs;
    }

	bool isPalindromicSubstring(std::string s)
	{
		int start = 0;
		int end = s.length() - 1;

		while(start < end
		   && s[start] == s[end])
		{
			start++;
			end--;
		}
		//std::cout <<start <<", " <<end <<std::endl;
		return (start >= end);
	}
};
#ifdef DEBUG

int main(void)
{
	Solution solu;

	//std::cout <<solu.isPalindromicSubstring("abcddcba") <<std::endl;
	std::cout <<solu.longestPalindrome("gatiemeabcdeedcbagatieme") <<std::endl;


	return EXIT_SUCCESS;
}
#endif
