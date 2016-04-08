#链接
------- 

>LeetCode题目：https://leetcode.com/problems/generate-parentheses
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51095236

#题意
-------

>Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
>
>For example, given n = 3, a solution set is:
>
>"((()))", "(()())", "(())()", "()(())", "()()()"
>
>Subscribe to see which companies asked this question


给定一个数字n，要求写一个方法，生成所有n个括号的可能合法组合。
例如，n=3， 那么3个括号的所有可能组合如上。


#分析
-------

这道题的要求是给定n对括号，生成所有正确的括号组合。

这道题要生成正确形式的括号匹配的数量，其实就是卡特兰数，这里就不详说了。

至于要输出所有括号的正确组合形式，可以采用递归。用两个变量l和r记录剩余左括号和右括号的数量，当且仅当左右括号数量都为0时，正常结束。当然还有一点限制，就是剩余的右括号数量比左括号多时才能添加右括号。



#代码

-------



```cpp

#include <iostream>
#include <vector>

using namespace std;


#define __tmain main


class Solution
{
public :
    vector<string> generateParenthesis(int n)
    {
        vector<string> v;
        generateParenthesis(v, "", n, n);

        return v;
    }

    void generateParenthesis(vector<string> &v, string s, int l, int r) // l和r记录剩余左右括号的数量
    {
        // 当且仅当左右括号数量都为0时，正常结束
        if(l == 0 && r == 0)
        {
            v.push_back(s);
        }

        //  括号要想匹配，首先应该压入左括号，再压入右括号
        if(l > 0)
        {
            generateParenthesis(v, s + "(", l - 1, r);
        }
        //  压入右括号时候，必须保证左括号数多，即有左括号在解集中
        if(r > 0 && l < r) // 剩余的右括号数量比左括号多时才能添加右括号
        {
            generateParenthesis(v, s + ")", l, r - 1);
        }
    }
};

int __tmain( )
{
    Solution solu;
    vector<string> res = solu.generateParenthesis(3);

    for(int i = 0; i <res.size(); i++)
    {
        cout <<res[i] <<endl;
    }
}

```



