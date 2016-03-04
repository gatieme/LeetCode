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
用两个指针，一个指向当前子串的头，一个指向尾，
尾指针不断往后扫描，当有字符前面出现过了，
记录当前子串长度和最优解的比较结果。

然后头指针不断往后扫描，直到扫描到一个字符和尾指针相同，则尾指针继续扫描，当尾指针到达字符串结尾，算法结束。复杂度O(n) + O(n) = O(n)

 */

class Solution
{
private:
    bool canUse[256];
public:
    int lengthOfLongestSubstring(std::string s)
    {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        memset(canUse, true, sizeof(canUse));
        
        int count = 0;
        int start = 0;
        int ret = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if (canUse[s[i]])
            {
                canUse[s[i]] = false;
                count++;
            }
            else
            {
                ret = std::max(ret, count);
                while(true)
                {
                    canUse[s[start]] = true;
                    count--;
                    if (s[start] == s[i])
                        break;
                    start++;
                }
                start++;
                canUse[s[i]] = false;
                count++;
            }
        }
        
        ret = std::max(ret, count);
        
        return ret;
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