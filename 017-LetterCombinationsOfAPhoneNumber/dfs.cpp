#include <iostream>
#include <vector>
using namespace std;

#define __tmain main

class Solution
{
public:
    void dfsgetString(string digits,
                      int index,
                      string curr,
                      vector<string> dict,
                      vector<string> *result)
    {
        if(index == digits.size())
        {
            //cout <<"解" <<curr <<endl;
            result->push_back(curr);
            return ;

        }
        char strChar = digits[index];
        //cout <<"当前数字" <<strChar <<endl;

        // 循环当前数字对应的每一个字符
        for(int i = 0; i < dict[strChar - '0'].size(); i++)
        {
            string temp = curr;
            curr += dict[strChar-'0'][i];
            //cout <<"取出" <<dict[strChar-'0'][i] <<endl;
            //cout <<"得到" <<curr <<endl;
            dfsgetString(digits, index + 1, curr, dict, result);

            //  每次递归退出后，恢复原来的现场，
            //  主要是回复curr的值
            //cout <<digits <<", " <<index <<", " <<curr <<endl;
            curr = temp;

        }
    }

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

        string curr ="\0";
        dfsgetString(digits, 0, curr, dict, &res);

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
