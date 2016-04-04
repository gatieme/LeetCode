#链接
-------

>LeetCode题目：https://leetcode.com/problems/longest-common-prefix/
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51055968


#题意
-------

Write a function to find the longest common prefix string amongst an array of strings.



找出所有字符串的最长公共前缀。这道题很简单，但需要注意减少比较字符的操作次数。


#解法
-------

思路：设置一个位数记录器num，遍历所有字符串的第num位。如果都相同，则num++。

直到某字符串结束或者所有字符串的第num位不都相同，则返回[0~num-1]位，即最长公共前缀。

时间复杂度：O(nm)（n是字符串数组长度，m是字符串长度）

空间复杂度：O(1)



```cpp
class Solution
{
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        string result = "";
        bool flag = false;
        if(strs.size( ) == 0)
        {
            return "";
        }
        else if(strs.size( ) == 1)
        {
            return strs[0];
        }

        // 每次第1个字符串的pos位为基准
        for(int pos = 0; pos < strs[0].size(); pos++)
        {
            char temp = strs[0][pos];
            for(int index = 1; index < strs.size(); index++)
            {
                if(strs[index][pos] != temp)
                {
                    flag = true;
                    break;
                }
            }
            if(flag == true)
            {
                break;
            }
            result += strs[0][pos];
        }
        return result;
    }
};
```