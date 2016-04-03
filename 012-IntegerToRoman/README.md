#链接
-------

>LeetCode题目：https://leetcode.com/problemset/algorithms/
>
>GitHub代码 :  https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51050223


#题意
-------

>Given an integer, convert it to a roman numeral. 
Input is guaranteed to be within the range from 1 to 3999.

题意
给于一个整型数字范围在1-3999，将它转化为罗马数字
思路： 
将罗马数字用键-值标识出来，转换即可。 
注意的就是罗马数字的转换规则 

#罗马数字规则
-------
罗马数字的计数方法，可以参见[百度百科](http://baike.baidu.com/link?url=nEgIPqXCRrXXyEt9S6AKF9-jIOU5mk6n-6SfxmDrR4VRHai_CJnWcAqZ28eVoyHGCxnzuiZVGn9qdaW8AqZCrq)

|整数数字 |  1  | 5 |  10 | 50  | 100 | 500 | 1000 |
| ------------- |:-------------:| -----:|-----:|-----:|-----:|-----:|-----:|
|罗马字符 |   I  | V |  X  |  L   |    C  |    D  |   M   |


1.    罗马数字共有7个，即I（1）、V（5）、X（10）、L（50）、C（100）、D（500）和M（1000）。 
罗马数字中没有“0”。 

2.    重复次数：一个罗马数字最多重复3次。 

3.    右加左减： 
>在较大的罗马数字的右边记上较小的罗马数字，表示大数字加小数字。 
在较大的罗马数字的左边记上较小的罗马数字，表示大数字减小数字。 

4.    左减的数字有限制，仅限于I、X、C，且放在大数的左边只能用一个。 

*    V 和 X 左边的小数字只能用Ⅰ。 
*    L 和 C 左边的小数字只能用X。 

如下表所示

![这里写图片描述](./roman.png)


#所有的可能性--按位翻译
-------

与十进制数字相比，虽然在个位、十位、百位、千位这些数位上罗马数字的写法各不相同，但却都有着共同规律。

从纵向比较看，每一个数位的写法只和该数位对应的一倍、五倍、十倍对应的字母有关。

如8的罗马数字是VIII（5+1+1+1），80是LXXX（50+10+10+10），800是DCCC（500+100+100+100）。因此我们就可以将十进制数字的

**各位取出，按照罗马数字各数位的字符生成规则，生成对应的罗马数字**
因此有了下面的代码

```c

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

        int index = 0;
        while (num > 0)
        {
            result = trans[index][num % 10] + result;
            num = num / 10;
            index++;
        }
        return result;
    }
};
```

甚至结果可以这么返回
```
        return trans[3][num / 1000] +
            trans[2][num % 1000 / 100] +
            trans[1][num % 100 / 10] +
            trans[0][num % 10];
```


#分析--寻找罗马数字的规则

看懂了上面的规则后，就可以对数字的每位逐个判断即可。可以归纳出如下4种情形：

1.	如果该位数字是4或者9，则说明是上面3、4、5这三种情况中的一种，即把I、X、C中的一个放到了大数字的左侧；

2.	如果该位数字是0~3或者5~8，则说明是上面1这种情况，即I、X、C中的一个，自身连用或者放在大数的右边连用；

```
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

```


进一步，可以看到，罗马数字可以分为四种构成方式，

而1-3999中，共有1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1，共计13种，
依次分别对应"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"，即：

| 整数数字 | 1000 | 900 | 500 | 400 | 100 | 90 | 50 | 40 | 10 | 9 | 5 | 4 | 1 |
| ------------- |:-------------:| -----:|-----:|-----:|-----:|-----:|-----:|
| 罗马数字 | M | CM | D |  CD | C |  XC | L | XL | X | IX | V | IV | I |

```
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
```
