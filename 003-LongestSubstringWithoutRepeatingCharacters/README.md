>LeetCode题目地址：https://leetcode.com/problems/longest-substring-without-repeating-characters/
>
>GitHub代码 ： https://github.com/gatieme/LeetCode/tree/master/003-LongestSubstringWithoutRepeatingCharacters
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/50809552


#描述
-------
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.

该题目就是求最长的无重复字符的子串。


#题解
-------

##canuse的标示
-------
本题目中的贪心思想即 **最长无重复子串肯定包含在两个重复字符之间**

用两个指针start和end，一个指向当前子串的头，一个指向尾，
end尾指针不断往后扫描，当有字符前面出现过了，
记录当前子串长度和最优解的比较结果。

然后头指针不断往后扫描，直到扫描到一个字符和尾指针相同，
则尾指针继续扫描，
当尾指针到达字符串结尾，算法结束。复杂度O(n) + O(n) = O(n)

```
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
    bool canUse[256];
public:
    int lengthOfLongestSubstring(std::string s)
    {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        memset(canUse, true, sizeof(canUse));

        int start = 0, end = 0, length = 0;
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
            //  不允许字符重复, 因此每个字符只能使用一次
            if (canUse[(int)s[end]] == true)
            {
                canUse[(int)s[end]] = false;   // 已经使用过的不能再次使用
            }
            else    //  当前字符不能继续被使用, 则可能到达一个最长的子串末尾
            {
                length = end - start;           //  获取到贪心的子串长度
                ret = std::max(ret, length);    //  保存当前最长的子串长度

#ifdef DEBUG
                std::cout <<"[" <<start <<", " <<end <<"]substr = " <<s.substr(start, length) <<", length = " <<length <<std::endl;
#endif

                for( ; s[start] != s[end]; start++)         // [srart, end)  -=>  就是可能的子串
                {
                    //  重新置开始到结束的子串可以使用
                    canUse[(int)s[start]] = true;
                }

                start++;
                canUse[(int)s[end]] = false;
            }
        }

        length = end - start;

        ret = std::max(ret, length);

        return ret;
    }
};

#ifdef DEBUG
int main(void)
{
    Solution solu = Solution();

    std::cout <<solu.lengthOfLongestSubstring("ac") <<std::endl;

    return EXIT_SUCCESS;
}

#endif

```

此外我们也可以使用一个标示了当前位置字符char位置index的数组来标示，
##map[index]来标示
-------
###c++
-------
```

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

        int start = -1, end = 0;
        int ret = 0;

        //  ==贪心算法==
        //  贪心的精髓就是贪婪的每次寻找一个能找到的最长的子串
        int size = s.length();
        for(end = 0; end < size; end++)
        {
            if(local[s[end]] > start)
            {
                start = local[s[end]];
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

```
###python
-------

```
#!/usr/bin/env python
#coding=utf-8
#
#

class Solution(object) :

    def lengthOfLongestSubstring(self, s) :
        """
        :type s: str
        :rtype: int

        算法的思想与C/C++的算法思想相同，
        所不同是只是C++用了use数组标识当前字符是否在组成的子串中
        而python使用的方式是
        ch in d, 当前字符在字典中，但是之前的ch也在字典中存在
        同时d[ch] >= start 说明字符所在的的位置必须在起始字符之后
        两个条件保证了获取到的子串的合理性
        """
        res     = 0
        start   = 0
        d       = {}
        for end, ch in enumerate(s):  #  遍历字符串

            #print "end = %d, char = %c" % (end, ch)

            #  如果当前end字符与前面已经重复,
            #  而且重复的位置在start后面
            #  此时[strart, end)即是贪心出的一个子串
            if ch in d and d[ch] >= start :

                #  更新start指向最新的位置
                start = d[ch] + 1

            #  更新d[ch]的位置为end
            d[ch] = end

            #print "[%d, %d] -=> %s, length = %d" % (start, end, s[start:end + 1], end - start + 1)


            res = max(res, end - start + 1)

        return res


if __name__ == "__main__" :


    solution = Solution()
    print solution.lengthOfLongestSubstring("abcabcbb")

```
