#链接
-------

>LeetCode题目：https://leetcode.com/problems/letter-combinations-of-a-phone-number/
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51087208


#题意
-------

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



![手机键盘](200px-Telephone-keypad2.png)
```

Input:Digit string "23"

Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
```

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.




#暴力解法

-------

枚举所有情况。

循环每一个输入数字，

*    先取出之前的所有解空间（即已有的排列中每一个字符串）

*    分别加入该数字所代表的每一个字符

所有是三重for循环。


举例：

初始化排列{""}

*    输入2，代表"abc"


当前所有解空间（已有排列中只有字符串）为""，所以将数字2对应的字符压入解空间，所以得到{"a","b","c"}



*    输入3，代表"def"



当前的解空间为{"a","b","c"}，因此循环解空间中的每个解，分别追加当前数字3对应的字符


(1)    对于排列中的首元素"a"，删除"a"，并分别加入'd','e','f'，得到{"b","c","ad","ae","af"}


(2)    对于排列中的首元素"b"，删除"b"，并分别加入'd','e','f'，得到{"c","ad","ae","af","bd","be","bf"}


(3)    对于排列中的首元素"c"，删除"c"，并分别加入'd','e','f'，得到{"ad","ae","af","bd","be","bf","cd","ce","cf"}


注意

（1）每次添加新字母时，应该先取出现有ret当前的size()，而不是每次都在循环中调用ret.size()，因为ret.size()是不断变化的，编译器的编译优化可能会将这个数保存下来

（2）每次取出解空间时，应该将该解删除，然后把新追加的解压入解空间



```c
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


```


#DFS搜索策略
-------

我们对我们上面的算法进行优化，会发现

所有的解空间其实就是一个深度优先搜索的结果。

我们自第一个数字开始搜索，当依次向后面一个进行搜索



当搜索的深度（也就是串的长度）与数字串的长度相同时，就说明找到了一个解，将这个解保存起来



```c
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


```


