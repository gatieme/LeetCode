#链接
-------

>  题目地址 https://leetcode.com/problems/zigzag-conversion/
>
> github解题 https://github.com/gatieme/LeetCode/tree/master/006-ZigZagConversion
> 
> CSDN题解：http://blog.csdn.net/gatieme/article/details/50889937

#题目描述
-------

字符串`“PAYPALISHIRING”`通过一个给定的行数写成如下这种Z型模式：
```
P   A   H   N
A P L S I I G
Y   I   R
```
然后一行一行的读取：`“PAHNAPLSIIGYIR”`

写代码读入一个字符串并通过给定的行数做这个转换：

`string convert(string text, int nRows);`

调用`convert("PAYPALISHIRING", 3)`，应该返回`"PAHNAPLSIIGYIR"`。

#思路
-------
`zigzag`的意思是"之"字形，`zigzag conversion`也就是按`"N"`字母的样子来重新安排字符串中字符的位置，并合并成一个新的字符串。
`nRows则表示`"N"`的高度，也就是每一竖列有`nRows`个字符。

我采用的是一个比较简单的方法，创建`nRows`个`string`，并将老字符串中字符依次写入新`string`中，写完之后将`nRows`个`string`合并成一个，问题就解决了。算法的复杂度为`O(n)`。
Zigzag:即循环对角线结构（


参考 http://www.cnblogs.com/sanghai/p/3632528.html


题没什么意思，就是纯粹的**找规律**

发现所有行的重复周期都是 2 * nRows - 2

对于首行和末行之间的行，还会额外重复一次，重复的这一次距离本周期起始字符的距离是 2 * nRows - 2 - 2 * i
```
#include <iostream>
#include <string>

/*
创建nRows个char数组，将s按照0,1,2,...,nRows-2,nRows-1,nRows-2,...,2,1,0的顺序，

将s中每个字符装入数组。

具体来说，数组下标先递增，直到nRows-1，则反向，直到0，再反向，……直到s字符全部装入各数组

再依次输出0~nRows-1个数组。
*/

class Solution {
public:
    std::string convert(std::string s, int nRows)
    {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        std::string result;

        if (nRows < 2) return s;

        for (int i = 0;i < nRows; ++i)
        {
            for (int j = i; j < s.length(); j += 2 * (nRows - 1))
            {
                result.push_back(s[j]);

                if (i > 0 && i < nRows - 1)
                {
                    if (j + 2 * (nRows - i - 1) < s.length())
                    {
                        result.push_back(s[j + 2 * (nRows - i - 1)]);
                    }
                }
            }
        }

        return result;
    }
};



int main(void)
{
    Solution solu;

    std::cout <<solu.convert("PAYPALISHIRING", 3) <<std::endl;

    return 0;
}

```