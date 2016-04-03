#include <iostream>

using namespace std;

#define __tmain main


class Solution
{
public:
    string intToRoman(int num)
    {
        int n[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string r[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string s = "";
        for(int i = 0; num > 0; num %= n[i], ++ i)
        {
            for(int j = 0, k = num / n[i]; j < k; ++ j)
            {

                s += r[i];
            }
        }

    return s;
   }
};


 int main()
 {
     Solution solu;

     std::cout <<solu.intToRoman(8) <<std::endl;;
     return 0;
 }
