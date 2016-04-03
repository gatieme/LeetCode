#链接
-------

>LeetCode题目地址: https://leetcode.com/problems/longest-palindromic-substring/
>
>GitHub代码:https://github.com/gatieme/LeetCode/tree/master/005-LongestPalindromicSubstring
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/50889546

#题目描述
-------

ven a string S, find the longest palindromic substring in S.

You may assume that the maximum length of S is 1000,and there exists one unique longest palindromic substring.

Subscribe to see which companies asked this question

问题：给定字符串S，求S中的最长回文子串。

##什么是回文串
-------
回文就是从左右两边读都一样的字符串。例如”aba”是回文，”abc”不是回文。

下面的函数可以判断一个字符串是不是回文
```
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
```
##常见错误分析
-------
网上常见的错误思路如下：

翻转S成为S’。查找S和S’最长公共子串，就是S的最长回文子串。

看起来有道理的样子。用实例检验下。

例如`S=”caba”，S’=”abac”`。

S和S’的最长公共子串是`”aba”`，确实是S的最长回文子串。

再看个例子。

`S=”abacdfgdcaba”，S’=”abacdgfdcaba”`

S和S’的最长公共子串是`”abacd”`，不过很明显这不是回文。

#暴力解法$O(N^3)$
-------
最简单的就是暴力穷举(`Brute Force`)对每个`start`和`end`位置的子串进行检测，判断其是否回文。显然有C(N,2)（组合）个子串。检测每个子串都需要`O(N)`的时间，所以此方法的时间复杂度为O($N^3$)。
```
#define DEBUG
//  最长回文子序列

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

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
```
#动态规划法$O(N^2)$时间$O(N^2)$空间
-------
我们针对暴力算法进行优化，诀窍就是避免重复计算（即重复检测同一子串）。

>考虑这个例子”ababa”。如果我们已经检测过”bab”是回文，那么只需判断一下最左右的两个字符（即两个a）是否相同即可判定`”ababa”`是否回文了。

我们用动态规划(`Dynamic Programming`即DP)法对暴力穷举法进行改进。

定义二维数组`P[i,j]`用以表示`Si…Sj`是回文（`true`）或不是回文（`false`）

>初始条件是：`P[i, i]=true，P[i, i + 1] = (Si == Si+1)`
>
> `P[i,j] = (P[i + 1, j - 1] && Si ==Sj)`



这个DP法的思路就是，首先可以知道单个字符和两个相邻字符是否回文，然后检测连续三个字符是否回文，然后四个。。。

此算法时间复杂度`$O(N^2)$`，空间复杂度`$O(N^2)$`。伪代码如下。

```
#define DEBUG
//  最长回文子序列

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>


class Solution
{
public:
    std::string longestPalindrome(std::string s)
    {
		int n = s.length();

  		int longestBegin = 0;
  		int maxLen = 1;

  		bool P[1000][1000] = {false};

  		//  ==初始化==
  		//  P[i, i] = true
  		//  P[i, i + 1] = (Si == Si+1)

  		//  首先初始化P[i, i] = true
  		for (int i = 0; i < n; i++)
  		{
    		P[i][i] = true;
  		}

  		//  然后初始化 P[i, i + 1] = (Si == Si+1)
  		for (int i = 0; i < n - 1; i++)
  		{
    		if (s[i] == s[i+1])
    		{
      			P[i][i+1] = true;
      			longestBegin = i;
      			maxLen = 2;
    		}
  		}

  		//  开始动态规划
  		//  P[i,j] = (P[i + 1, j - 1] && Si == Sj)
  		for (int len = 3; len <= n; len++)  //  循环所有长度
  		{
    		for (int start = 0; start < n - len + 1; start++)   //  循环回文串的起始位置
    		{
      			int end = start + len - 1;

      			if (s[start] == s[end]
                 && P[start + 1][end - 1])
      			{
        			P[start][end] = true;

                    longestBegin = start;
        			maxLen = len;
      			}
    		}
  		}
  		return s.substr(longestBegin, maxLen);
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

```

#改进算法--中心检测$O(n^2)$
-------
下面介绍一个$O(N^2)$时间$O(1)$空间的算法。

回到前面的问题，考虑这个例子”ababa”。如果我们已经检测过”bab”是回文，那么只需判断一下最左右的两个字符（即两个a）是否相同即可判定`”ababa”`是否回文了。

因此我们发现回文有什么特点呢?

很明显就是**中心对称**。

>abba的中心 ab | ba
>
>aboba的中心ab o ba

那么对于有N个字符的字符串S，只可能有2N-1个中心。

>为何是2N-1？因为两个字符之间的空档也可以是一个中心。例如”abba”的两个b中间就是一个中心。

围绕一个中心检测回文需要O(N)时间，所以总的时间复杂度是O(N2)。

那么我们需要做的就是，循环所有可能的中心位置，然后以当前中心开始向两端扩展，找到一个最长的回文串。

代码如下
```
#define DEBUG
//  最长回文子序列

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

/*

下面介绍一个O(N2)时间O(1)空间的算法。

回文的特点，就是中心对称。

对于有N个字符的字符串S，只有2N-1个中心。

为何是2N-1？因为两个字符之间的空档也可以是一个中心。例如”abba”的两个b中间就是一个中心。

围绕一个中心检测回文需要O(N)时间，所以总的时间复杂度是O(N2)。

*/
class Solution
{
public:
	std::string expandAroundCenter(std::string s, int left, int right)
	{
  		int len = s.length();
  	
  		while (left >= 0 
  			&& right <= len - 1 
  			&& s[left] == s[right])
  		{
    		left--;
    		right++;
  		}
  		
  		return s.substr(left + 1, right - left - 1);
	}
 
	std::string longestPalindrome(std::string s)
	{
  		int n = s.length( );
  		if (n == 0)
  		{
  			return "";
  		}
  		
  		std::string longest = s.substr(0, 1);  // a single char itself is a palindrome
  		for (int center = 0; center < n - 1; center++)		//  循环每个中心
  		{
  			//  以centerw为中心的最长回文串
    		std::string p1 = expandAroundCenter(s, center, center);
    		if (p1.length() > longest.length())
    		{
      			longest = p1;
			}
			
			//  以center和center + 1为中心的最长回文串
    		std::string p2 = expandAroundCenter(s, center, center + 1);
    		if (p2.length() > longest.length())
    		{
      			longest = p2;
  			}
  		}
  		
  		return longest;
	}
};


#ifdef DEBUG

int main(void)
{
	Solution solu;

	std::cout <<solu.expandAroundCenter("aabcddcbac", 4, 5) <<std::endl;
	std::cout <<solu.longestPalindrome("gatiemeabcdeedcbagatieme") <<std::endl;


	return EXIT_SUCCESS;
}
#endif

```
