#include <iostream>
#include <string>


#define DEBUG
//http://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Part-II.html

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


#ifdef DEBUG

int main(void)
{
    Solution solu;

    std::cout <<solu.convert("PAYPALISHIRING", 3) <<std::endl;

    return 0;
}

#endif
