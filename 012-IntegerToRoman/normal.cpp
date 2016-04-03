#include <iostream>

using namespace std;

#define __tmain main





class Solution
{
public:
    string intToRoman(int num)
    {
        string one[11] = {"", "I","II","III","IV","V","VI","VII","VIII","IX"};          ///  个位
        string ten[11] = {"", "X", "XX","XXX","XL","L","LX","LXX","LXXX","XC"};         ///  十位
        string hundred[11] = {"", "C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};      ///  百位
        string thousand[4] = {"", "M", "MM","MMM"};                                     ///  千位



        string result = "";
        string* trans[4] = {one, ten, hundred, thousand};

//        int index = 0;
//        while (num > 0)
//        {
//            result = trans[index][num % 10] + result;
//            num = num / 10;
//            index++;
//        }
        //return result;
        std::cout <<"千位 " <<num / 1000 % 10 <<" == " <<trans[3][num / 1000 % 10] <<std::endl;
        std::cout <<"百位 " <<num / 100 % 10  <<" == " <<trans[2][num / 100 % 10]   <<std::endl;
        std::cout <<"十位 " <<num / 10 % 10   <<" == " <<trans[1][num / 10 % 10]   <<std::endl;
        std::cout <<"个位 " <<num % 10        <<" == " <<trans[0][num % 10]        <<std::endl;

        return  trans[3][num / 1000 % 10] +
                trans[2][num / 100  % 10] +
                trans[1][num / 10   % 10] +
                trans[0][num        % 10];

    }
};
 int __tmain()
 {
     Solution solu;

     std::cout <<solu.intToRoman(1) <<std::endl;;
     return 0;
 }
