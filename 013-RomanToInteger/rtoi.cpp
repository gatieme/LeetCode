#include <iostream>

using namespace std;

/**

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems

string one[11] = {"", "I","II","III","IV","V","VI","VII","VIII","IX"};          ///  个位
string ten[11] = {"", "X", "XX","XXX","XL","L","LX","LXX","LXXX","XC"};         ///  十位
string hundred[11] = {"", "C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};      ///  百位
string thousand[4] = {"", "M", "MM","MMM"};                                     ///  千位


*/

class Solution {
public:
    int romanToInt(string s)
    {
        int result = 0;
        const char* p = s.c_str( );
        int count = 0;

        //千位
        while(*p!='\0'&&*p=='M')
        {
            p++;        //千位循环结束后p指向百位。
            count++;
        }
        result += 1000 * count;
        count=0;

        //百位
        if(*p == 'C')
        {
            while(*p!='\0'&&*p=='C')
            {
                p++;
                count++;
            }
            if(count==1&&*p=='M')
            {
                p++;
                count=9;
            }
            else if(count==1&&*p=='D')
            {
                p++;
                count=4;
            }
        }else if(*p=='D')
        {
            p++;
            count=5;
            while(*p!='\0'&&*p=='C')
            {

                p++;
                count++;
            }

        }
        else
        {
            count=0;
        }
        result+=count*100;
        count=0;


        //十位
        if(*p=='X')
            {
            while(*p!='\0'&&*p=='X')
            {
                p++;
                count++;
            }
            if(count==1&&*p=='C')
            {
                p++;
                count=9;
            }
            else if(count==1&&*p=='L')
            {
                p++;
                count=4;
            }
        }else if(*p=='L') {
            p++;
            count=5;
            while(*p!='\0'&&*p=='X')
            {
                p++;
                count++;
            }

        }else{
            count=0;
        }
        result+=count*10;
        count=0;


        //个位
        if(*p=='I')
            {
            while(*p!='\0'&&*p=='I')
            {
                p++;
                count++;
            }
            if(count==1&&*p=='X')
            {
                p++;
                count=9;
            }
            else if(count==1&&*p=='V')
            {
                p++;
                count=4;
            }
        }
        else if(*p=='V')
        {
            p++;
            count=5;
            while(*p!='\0'&&*p=='I')
            {
                p++;
                count++;
            }

        }
        else
        {
            count=0;
        }
        result+=count;

        return result;
    }
};


int main(void)
{

}
