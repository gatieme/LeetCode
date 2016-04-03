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
