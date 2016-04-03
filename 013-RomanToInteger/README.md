#链接
-------

>LeetCode题目：https://leetcode.com/problems/roman-to-integer/
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51052713

#题意
-------
Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems

与12题正好相反，这道题把一个不大于4000的罗马数字转换为十进制整数


#所有的可能性--按位翻译
-------

因为数字不大于4000，因此我们可以分析罗马数字个位、十位、百位、千位的规则，然后计算所有的可能性然后分析


```c
string one[11] = {"", "I","II","III","IV","V","VI","VII","VIII","IX"};          ///  个位
string ten[11] = {"", "X", "XX","XXX","XL","L","LX","LXX","LXXX","XC"};         ///  十位
string hundred[11] = {"", "C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};      ///  百位
string thousand[4] = {"", "M", "MM","MMM"};   
```

因此有了这样的代码
```c
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

```



#分析--寻找罗马数字的规则
-------

上面的解法太繁琐太深入细节了，观察到罗马数字和Integer的转换的小规律是：

>IV = 5 -  1 =  (-1) + 5 = 4
>
>VI = 5 + 1 = 5 + 1 = 6

I在V前面，由于I比V小，所以I被解释为负数。
V在I后面，由于V比I大，所以V给解释为整数。
继续看几个例子。

>VII = 5 + 1 + 1 = 7
> 
>IX = (-1) + 10 = 9

所以，

*    扫描字符串一遍，从第一个字符开始，到最后一个字符为止，一次比较当前字符a和当前字符的下一个字符b。

*    如果a< b ，解释为 b - a,否则如果a >= b， 解释为a + b。 

实际上，由于每次总是比较2个相邻的字符，所以是下标是从0开始，到`inputstring.length()-2`结束。

```c
class Solution {
public:
    int romanToInt(std::string s)
    {
        int sum = 0;
        int start = 0;

        char char_arr[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        int int_arr[] = {1, 5, 10, 50, 100, 500, 1000};

        std::map<char, int> roman_map;
        int map_len = sizeof(char_arr) / sizeof(char);

        for (int i = 0; i< map_len; ++i)
        {
            roman_map.insert(std::pair<char, int> (char_arr[i], int_arr[i]));
        }
        for (int i = 0; i < s.length() - 1; ++i)
        {
            if (roman_map[s[i]]>=roman_map[s[i + 1]])
            {
                sum += roman_map[s[i]];
            }
            else
            {

                sum -= roman_map[s[i]];
            }
        }
        sum += roman_map[s[s.length()-1]];
        return sum;
    }
};
```
