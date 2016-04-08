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
