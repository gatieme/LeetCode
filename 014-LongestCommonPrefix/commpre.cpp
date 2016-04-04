#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define __tmain main

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        string prefix = "";
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
        for(int pos = 0; pos < strs[0].length(); pos++)
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
            prefix += strs[0][pos];
        }
        return prefix;
    }
};
int __tmain( )
{
    string str[2] = {"abcd", "a"};
    vector<string> strs(str, str + 2);

    Solution solu;
    cout <<solu.longestCommonPrefix(strs) <<std::endl;

    return EXIT_SUCCESS;
}
