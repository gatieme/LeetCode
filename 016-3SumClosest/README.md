#链接
-------

>LeetCode题目：https://leetcode.com/problems/3sum-closest
>
>GitHub代码：https://github.com/gatieme/LeetCode
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51057063

#题意
-------

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

给定一个数组和一个目标值，返回其中3个数字的和且和值最接近目标值。

给定n个整数的数组S，寻找S中三个整数，使得总和最接近给定的目标。

返回三个整数的总和。

你可以假设每个输入将有一个确切的解决方案。


#分析
-------

题目思路和上题差不多。

先排序，二分查找来左右逼近。对于a + b + c ，对a规定一个数值时，采用二分查找b，c使Sum= a + b + c 最接近target。

先把数组排序，把3个数字的问题转换为找2个数字问题，每次固定一个数值，那么target就变为了（target-固定的数字），找两个数字近似新target就简单多了，定义两个指针，指向首和尾，定义一个Min，表示与新target的差值，差值越小越接近，不断的向后移动首指针或者向前移动尾指针来调整近似度Min，直到轮寻完毕为止，也就是每个值都被固定过。

#代码
-------

```c
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>


using namespace std;


#define __tmain main

class Solution
{
public:

    int threeSumClosest(vector<int>& nums, int target)
    {
        int size = nums.size( );
        int min = INT_MAX;
        int res = 0;
        sort(nums.begin(), nums.end());

        for(int index = 0; index < size - 2; index++)
        {

            for(int start = index + 1, end = size - 1;
                start < end;)
            {
                //  计算 a + b + c
                int sum = nums[index] + nums[start] + nums[end];

                //  计算接近度
                int dis = fabs(sum - target);

                //  保存最小的接近度
                if(dis < min)
                {
                    min = dis;
                    res = sum;
                }

                if(sum == target)
                {
                    res = sum;
                    break;
                }
                else if(sum > target)
                {
                    end--;
                }
                else
                {
                    start++;
                }

            }
        }

        return res;
    }
};


int __tmain( )
{
    int a[] = { 1, 1, 1, 0, };
    vector<int> vec(a, a + 4);

    Solution solu;
    cout <<solu.threeSumClosest(vec, 100) <<endl;

    return 0;
}
```
