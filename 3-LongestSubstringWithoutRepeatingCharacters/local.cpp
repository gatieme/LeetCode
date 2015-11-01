/*

Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for “abcabcbb” is “abc”, which the length is 3. For “bbbbb” the longest substring is “b”, with the length of 1.

该题目就是求最长的无重复字符的子串。

谢谢度娘，谢谢各位大牛前辈，用贪心算法，一层循环实现，效率不错,O(n)

last数组简直神一般存在，完美解决我两层循环的问题！！

贪心算法不是万能的，有些情况就不使用，比如局部最优解，最后可能并非全局最优解。

本题目中的贪心思想即 **最长无重复子串肯定包含在两个重复字符之间**
用len保存当前最长的子串。
如果某两个重复字符之间的子串长于len,
则给len赋值这个新的长度。

 */
#include <iostream>
#include <string>


#include <cstring>
#include <cmath>
#include <cstdlib>

#define DEBUG
/*
用两个指针start和end，一个指向当前子串的头，一个指向尾，
end尾指针不断往后扫描，当有字符前面出现过了，
记录当前子串长度和最优解的比较结果。

然后头指针不断往后扫描，直到扫描到一个字符和尾指针相同，
则尾指针继续扫描，
当尾指针到达字符串结尾，算法结束。复杂度O(n) + O(n) = O(n)

 */

class Solution
{
private:
    int local[256];
public:
    int lengthOfLongestSubstring(std::string s)
    {
        memset(local, -1, sizeof(local));     //  全部置为1

        int start = 0, end = 0;
        int ret = 0;

        //  ==贪心算法==
        //  贪心的精髓就是贪婪的每次寻找一个能找到的最长的子串
        //  从start开始找起来,直到最后一个与子串重复的字符end
        //  那么[start, end) 之间的子串就是贪心出的最长无重复子串
        //
        //  存储下来这个length, 那么更新start进行下一论的查找
        //  此时与end相同的那个字符的位置记为pos，即str[pos] == str[end]
        //
        //  更新start时可以简单的start++但是这种方式并不优化
        //  因为pos, end两个位置额字符是重复, 而start <= pos <= end
        //  因此可直接更新start = ++pos;
        int size = s.length();
        for(end = 0; end < size; end++)
        {
            if(local[s[end]] > start)
            {
                start = local[end];
            }

            local[s[end]] = end;
            ret = std::max(ret, end - start);
        }


        return ret;
    }
};

#ifdef DEBUG
int main(void)
{
    Solution solu = Solution();

    std::cout <<solu.lengthOfLongestSubstring("aa") <<std::endl;

    return EXIT_SUCCESS;
}

#endif
