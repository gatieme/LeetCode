#define DEBUG
//  最长回文子序列

#include <iostream>
#include <string>
// http://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Par-I.html
#include <cstdio>
#include <cstdlib>

/*

我们可以用动态规划(Dynamic Programming即DP)法对暴力穷举法进行改进。

记住，诀窍就是避免重复计算（即重复检测同一子串）。

考虑这个例子”ababa”。

如果我们已经检测过”bab”是回文，

那么只需判断一下最左右的两个字符（即两个a）是否相同

即可判定”ababa”是否回文了。

总结起来就是：

定义二维数组P[i,j]

用以表示Si…Sj是回文（true）或不是回文（false）

那么可知P[i,j] = (P[i + 1, j - 1] && Si ==Sj)

初始条件是：P[i, i]=true，P[i, i + 1] = (Si == Si+1)

这个DP法的思路就是，首先可以知道单个字符和两个相邻字符是否回文，然后检测连续三个字符是否回文，然后四个。。。

此算法时间复杂度O(N2)，空间复杂度O(N2)。伪代码如下。

*/
class Solution
{
public:
    std::string longestPalindrome(std::string s)
    {
		int n = s.length();

  		int longestBegin = 0;
  		int maxLen = 1;

  		bool P[1000][1000] = {false};

  		/*for(int i = 0; i < 1000; i++)
  		{
  			for(int j = 0; j < 1000; j++)
  			{
  				std::cout <<P[i][j];
  			}
  		}*/

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
	std::cout <<solu.longestPalindrome("jhgtrclvzumufurdemsogfkpzcwgyepdwucnxrsubrxadnenhvjyglxnhowncsubvdtftccomjufwhjupcuuvelblcdnuchuppqpcujernplvmombpdttfjowcujvxknzbwmdedjydxvwykbbamfnsyzcozlixdgoliddoejurusnrcdbqkfdxsoxxzlhgyiprujvvwgqlzredkwahexewlnvqcwfyahjpeiucnhsdhnxtgizgpqphunlgikogmsffexaeftzhblpdxrxgsmeascmqngmwbotycbjmwrngemxpfakrwcdndanouyhnnrygvntrhcuxgvpgjafijlrewfhqrguwhdepwlxvrakyqgstoyruyzohlvvdhvqmzdsnbtlwctetwyrhhktkhhobsojiyuydknvtxmjewvssegrtmshxuvzcbrabntjqulxkjazrsgbpqnrsxqflvbvzywzetrmoydodrrhnhdzlajzvnkrcylkfmsdode") <<std::endl;


	return EXIT_SUCCESS;
}
#endif
