#链接
------- 

>LeetCode题目：https://leetcode.com/problems/valid-parentheses/
>
>GitHub代码：https://github.com/gatieme/LeetCode/tree/master/019-RemoveNthNodeFromEndOfList
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51090593

#题意
-------

>Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
>
>The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
>
>Subscribe to see which companies asked this question


括号匹配问题


#栈匹配策略
-------

利用一个栈来保存前括号，然后有后括号来时弹出栈顶来

注意一下情况：
*    [])   左右括号数目不匹配，左括号少，右括号多，因此出栈时需判断栈是否空 if(!stack.empty())

*    ((    左右括号数目不匹配，左括号多，右括号少， 因此遍历完后 需判断栈是否空   

对于第一种情况，其实如果能匹配的话，那么第一个肯定字符肯定是左括号，因此我们可以直接将第一个字符入栈，这样的话


```cpp
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;
        bool res = true;
        if(s == "")
        {
            return true;
        }

        for(int i = 0; i < s.length( ); i++)
        {
            // 遇见左括号就入栈
            if(s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
                st.push(s[i]);
            }
            else if(s[i] == ')' || s[i] == ']' || s[i] == '}')
            {   //  遇见右括号就出栈

                //  出栈时候, 如果栈为空, 则肯定不匹配
                if(st.empty( ) == true)
                {
                    res = false;
                    break;
                }

                //  弹出栈顶元素看是否匹配
                char temp = st.top();
                st.pop( );
                if(s[i] == ')' && temp != '(')
                {
                    res = false;
                    break;
                }
                else if(s[i] == ']' && temp != '[')
                {
                    res = false;
                    break;
                }
                else if(s[i] == '}' && temp != '{')
                {
                    res = false;
                    break;
                }
            }
        }

        // 所有信息操作完以后如果堆栈不为空, 说明肯定不匹配
        if(st.empty() != true)
        {
            res = false;
        }


        return res;
    }
};


int main()
{

    Solution solu;
    std::cout <<solu.isValid("]") <<std::endl;

    return 0;
}
```
