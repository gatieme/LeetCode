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
