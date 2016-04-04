#链接
-------

>LeetCode题目：https://leetcode.com/problems/3sum/
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51056669


#题意
-------
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.


Note:


Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
The solution set must not contain duplicate triplets.
For example, given array S = {-1 0 1 2 -1 -4

根据题意，我们可以要找出三个数相加等于0的这样的一个集合，所以采用二维数组存储。

#分析
-------

首先抽取一个变量出来，该变量从左往右递归遍历，递归的同时设置两个变量，让其一个从第一个变量的右边，一个从数组的末端，同步的向中间遍历，有点类似于快速排序的判断方式，



如果三个数相加小于零，则让第二个变量自加； 如果三个数相加大于零，则让第三个变量自减； 如果三个数相加等于零，则将三个数加入到数组中，然后让第二个变量和第三个变量同步增减，自增自减的过程中要判断是否有重复数字；
依次递归，直到第一个变量条件终止为止。



先升序排序，然后用第一重for循环确定第一个数字。

然后在第二重循环里，第二、第三个数字分别从两端往中间扫。

如果三个数的sum等于0，得到一组解。

如果三个数的sum小于0，说明需要增大，所以第二个数往右移。

如果三个数的sum大于0，说明需要减小，所以第三个数往左移。

时间复杂度：O(n2)

注意：

1、排序之后天然满足non-descending order的要求

2、为了避免重复，在没有空间要求情况下可以用map，但是也可以跳过重复元素来做。



```c
#include <iostream>
#include <vector>

#include <algorithm>


using namespace std;


#define __tmain main

class Solution
{

public:

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> res;
        int size = nums.size( );

        sort(nums.begin( ), nums.end( ));

/*
        for(int index  = 0; index < nums.size(); index++)
        {
            cout <<" "<<nums[index];
        }
        cout <<endl;
*/

        for(int index = 0; index < size ; index++)
        {
            //skip same i
            while(index > 0 && index < size && nums[index] == nums[index - 1])
            {
                //cout <<"skip all " <<nums[index] <<endl;
                index++;
            }


            for(int start = index + 1, end = size - 1;
                start < end; )
            {
                int sum = nums[index] + nums[start] + nums[end];

                if(sum == 0)
                {
                    //cout <<nums[index] <<" + " <<nums[start] <<" + " <<nums[end] <<endl;

                    vector<int> cur(3);
                    cur[0] = nums[index];
                    cur[1] = nums[start];
                    cur[2] = nums[end];


                    res.push_back(cur);

                    start++;
                    end--;
                    //skip same j
                    while(start < end
                       && nums[start] == nums[start - 1])
                    {
                        //cout <<"skip all " <<nums[start] <<endl;
                        start++;
                    }

                    //skip same k
                    while(end > start && nums[end] == nums[end + 1])
                    {
                        //cout <<"skip all " <<nums[end] <<endl;
                        end--;
                    }
                }
                else if(sum > 0)
                {
                    end--;
                    while(end > start && nums[end] == nums[end + 1])
                    {
                        //cout <<"skip all " <<nums[end] <<endl;
                        end--;
                    }

                }
                else if(sum < 0)
                {
                    start++;
                    while(start < end
                       && nums[start] == nums[start - 1])
                    {
                        //cout <<"skip all " <<nums[start] <<endl;
                        start++;
                    }
                }
            }
        }

        return res;

    }
};


int __tmain()
{
    int a[6] = { 0, 0, 0 };
    vector<int> nums(a, a + 3);

    Solution solu;
    solu.threeSum(nums);

    return 0;
}
```