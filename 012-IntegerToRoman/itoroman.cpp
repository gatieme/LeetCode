#include <iostream>

using namespace std;

#define __tmain main


class Solution
 {
 public:
     string intToRoman(int num)
     {
         string s;
         int n1[] = {1000, 100, 10, 1};
         char r1[] = {'M', 'C', 'X', 'I'};
         char r2[] = {' ', 'D', 'L', 'V'};

         for(int i = 0; i < 4; ++ i)
         {
             int b = num / n1[i];

             if(b == 9)
             {
                 s = s + r1[i] + r1[i-1];
             }
             else if(b >= 5)
             {
                 s += r2[i];
                 for(int j = 0; j < b - 5; ++ j)
                 {
                     s += r1[i];
                }
             }
             else if(b == 4)
             {
                 s = s + r1[i] + r2[i];
             }
             else
             {
                 for(int j = 0; j < b; ++ j)
                 {
                     s += r1[i];
                }
             }

             num = num % n1[i];
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
