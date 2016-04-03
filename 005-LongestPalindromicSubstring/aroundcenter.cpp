#define DEBUG
//  最长回文子序列

#include <iostream>
#include <string>
// http://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Par-I.html
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
	std::cout <<solu.longestPalindrome("jhgtrclvzumufurdemsogfkpzcwgyepdwucnxrsubrxadnenhvjyglxnhowncsubvdtftccomjufwhjupcuuvelblcdnuchuppqpcujernplvmombpdttfjowcujvxknzbwmdedjydxvwykbbamfnsyzcozlixdgoliddoejurusnrcdbqkfdxsoxxzlhgyiprujvvwgqlzredkwahexewlnvqcwfyahjpeiucnhsdhnxtgizgpqphunlgikogmsffexaeftzhblpdxrxgsmeascmqngmwbotycbjmwrngemxpfakrwcdndanouyhnnrygvntrhcuxgvpgjafijlrewfhqrguwhdepwlxvrakyqgstoyruyzohlvvdhvqmzdsnbtlwctetwyrhhktkhhobsojiyuydknvtxmjewvssegrtmshxuvzcbrabntjqulxkjazrsgbpqnrsxqflvbvzywzetrmoydodrrhnhdzlajzvnkrcylkfmsdode") <<std::endl;


	return EXIT_SUCCESS;
}
#endif
