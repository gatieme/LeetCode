#链接
-------
Leetcode题目： https://leetcode.com/problems/palindrome-number/

Github代码：https://github.com/gatieme/LeetCode/tree/master/9-PalindromeNumber

CSDN题解：http://blog.csdn.net/gatieme/article/details/51046193

#题目
-------
检测一个整数是不是回文数字

直接将该整数反序，反序后看是不是等于其本身即可

#C代码
-------
```c
bool isPalindrome(int x)
{
    long long xx = x;
    long long new_xx = 0;

    while (xx > 0)
    {
        new_xx = new_xx * 10 + xx % 10;
        xx /= 10;

    }

    return new_xx == (long long)x;
}

```


#Python代码
-------
```py
class Solution(object):
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        return str(x) == str(x)[::-1]

```