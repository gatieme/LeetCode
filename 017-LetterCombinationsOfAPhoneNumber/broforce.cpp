#include <iostream>
#include <vector>
using namespace std;

#define __tmain main

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> res;
        if(digits == "")
        {
            return res;
        }


        vector<string> dict(10);
        dict[2] = "abc";
        dict[3] = "def";
        dict[4] = "ghi";
        dict[5] = "jkl";
        dict[6] = "mno";
        dict[7] = "pqrs";
        dict[8] = "tuv";
        dict[9] = "wxyz";

        res.push_back("");

        //  输入2, 生成解空间a, b, c
        //  输入3, 先取出原来的解，再加上当前的
        for(int i = 0; i < digits.size(); i++)      //  循环输入的每个字符
        {
            int size = res.size( );
            for(int j = 0; j < size; j++)     //  遍历原来的解空间
            {
                string cur = res[0];
                //std::cout <<"取出" <<cur <<endl;
                res.erase(res.begin());
                //std::cout <<"读取" <<dict[digits[i] - '0'] <<endl;
                for(int k = 0; k < dict[digits[i] - '0'].size(); k++)
                {
                    res.push_back(cur + dict[digits[i] - '0'][k]);
                    //std::cout <<"添加" <<dict[digits[i] - '0'][k] <<endl;

                }
            }
        }

        return res;
    }
};

int __tmain(void)
{

    string digits = "23";
    Solution solu;
    vector<string> res = solu.letterCombinations(digits);
    for(int i = 0; i < res.size( ); i++)
    {
        std::cout <<res[i] <<endl;
    }
    return 0;
}
