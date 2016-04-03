#链接
-------

题目地址：https://leetcode.com/problems/two-sum/
Github代码：https://github.com/gatieme/LeetCode/tree/master/001-TwoSum
CSDN题解：http://blog.csdn.net/gatieme/article/details/50596965


#描述
-------
给定一个整数数组，找出其中两个数满足相加等于你指定的目标数字。

要求：这个函数twoSum必须要返回能够相加等于目标数字的两个数的索引，且index1必须要小于index2。请注意一点，你返回的结果（包括index1和index2）都不是基于0开始的，即自1开始

你可以假设每一个输入肯定只有一个结果。

>举例：
>输入：numbers={3, 2, 4}, target = 6
>输出：index1 = 2, index2 = 3


#暴力解法O(n^2)
-------
首先是最暴力的方法，使用双层循环，对于数组nums中的每一个数据nums[left]判断后面是否有某个数nums[right],使得

>nums[left] + nums[right] ==target
>即 num[right] = target - nums[left]

```c
/**
 *
 * Note: The returned array must be malloced, assume caller calls free().
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//#define DEBUG

int* twoSum(int* nums,      /*  the pointer which point to the array  */
            int numsSize,   /*  the size of the array  */
            int target)     /*  the sum of the two num  */
{
    int *answer = (int *)malloc(sizeof(int) * 2);

    for(int left = 0; left < numsSize; left++)  // 对于每一个数据
    {
        // 循环其后面的数据看nums[left] + nums[right] == target是否成立
        // 其实就是看target - nums[right]在不在数组中
        for(int right = left + 1; right < numsSize; right++)
        {
            if(nums[left] + nums[right] == target)
            {
                answer[0] = left + 1;
                answer[1] = right + 1;
                break;
            }
        }
    }
    return answer;
}

#ifdef DEBUG

int main(void)
{
    int nums[5] = {3, 2, 4};
    int *answer = NULL;
    answer = twoSum(nums, 3, 6);
    printf("[%d, %d]\n", answer[0], answer[1]);
}
#endif
```

#进阶解法--基于排序O（nlogn）
-------

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//#define DEBUG

///////////////////////////////////////////////////////////////////////////
///
///
///  快速排序--QuickSort
///  http://www.cnblogs.com/RootJie/archive/2012/02/13/2349649.html
///
///
///////////////////////////////////////////////////////////////////////////
/*
 *2012年2月13日16:42:45
 *效率较高的实现
 */

#include <stdio.h>
#include <time.h>

#define MAX_SIZE 20000

#define SWAP(x, y) {int t=x; x=y; y=t;}

void QuickSort(int *array, int left, int right);
int Partition(int *array, int left, int right);

int position[MAX_SIZE]; //  用于存储位置信息

int InitPosion(int *position, int length)
{
    for(int pos = 0; pos < length; pos++)
    {
        position[pos] = pos + 1;
    }
}

int Partition(int *array, int left, int right)
{
    int pivot = array[left];

    while (left < right)
    {
        while (left < right && array[right] >= pivot)
        {
            --right;
        }
        SWAP(array[left], array[right]);
        SWAP(position[left], position[right]);

        while (left < right && array[left] <= pivot)
        {
            ++left;
        }
        SWAP(array[right], array[left]);
        SWAP(position[left], position[right]);
        
    }

    return left;
}

void QuickSort(int *array, int left, int right)
{
    int pivot;

    if (left < right)
    {
        pivot = Partition(array, left, right);
    
        QuickSort(array, left, pivot - 1);
        QuickSort(array, pivot + 1, right);
    }

}






int cmp(const void *left, const void *right)
{
    int *left_num = (int *)left;
    int *right_num = (int *)right;

    return (*left_num - *right_num);
    
    //qsort(nums, numsSize, sizeof(nums[0]), cmp);
}


int* twoSum(int* nums,      /*  the pointer which point to the array  */
            int numsSize,   /*  the size of the array  */
            int target)     /*  the sum of the two num  */
{
    //qsort(nums, numsSize, sizeof(nums[0]), cmp);
    InitPosion(position, numsSize);

#ifdef DEBUG   
    printf("Before Quick Sort : \n");
    printf("Array    : ");
    for(int pos = 0; pos < numsSize; pos++)
    {
        printf("%3d", nums[pos]);
    }
    printf("\n");
    printf("Position : ");
    for(int pos = 0; pos < numsSize; pos++)
    {
        printf("%3d", position[pos]);
    }
    printf("\n");
#endif  

    QuickSort(nums, 0, numsSize - 1);

#ifdef DEBUG   

    printf("After Quick Sort : \n");
    printf("Array    : ");
    for(int pos = 0; pos < numsSize; pos++)
    {
        printf("%3d", nums[pos]);
    }
    printf("\n");
    printf("Position : ");

    for(int pos = 0; pos < numsSize; pos++)
    {
        printf("%3d", position[pos]);
    }
    printf("\n");
#endif  


    int *answer = (int *)malloc(sizeof(int) * 2);

    int left = 0, right = numsSize - 1, sum;
    while(left < right)
    {
        sum = nums[left] + nums[right];

#ifdef DEBUG
        printf("[%d, %d], %d + %d = %d\n",
            left, right,
            nums[left], nums[right], sum);
#endif  

        if(sum == target)
        {
#ifdef DEBUG
            printf("[%d, %d], %d + %d = %d\n",
                left, right,
                nums[left], nums[right], target);
#endif
            break;
        }
        else if(sum < target)
        {
#ifdef DEBUG
            printf("[%d, %d], %d + %d = %d\n",
                left, right,
                nums[left], nums[right], target);
#endif
            left++;
        }
        else if(sum > target)
        {
#ifdef DEBUG
            printf("[%d, %d], %d + %d = %d\n",
                left, right,
                nums[left], nums[right], target);

#endif
            right--;
        }
    }
    if(position[left] < position[right])
    {
        answer[0] = position[left];
        answer[1] = position[right];
    }
    else
    {
        answer[0] = position[right];
        answer[1] = position[left];
    }
        
    return answer;
}

#ifdef DEBUG

int main(void)
{
    int nums[5] = {-1, -2, -3, -4, -5};
    int *answer = NULL;
    answer = twoSum(nums, 5, -8);
    printf("[%d, %d]\n", answer[0], answer[1]);
}
#endif
```


#优化解法
-------

前面我们的算法是

对于数组nums中的每一个数据nums[left]判断后面是否有某个数nums[right],使得

>nums[left] + nums[right] ==target
>即 num[right] = target - nums[left]

循环每一个nums[left]的时间复杂度为O(N)
现在我们要是能在查找 num[right]上提高效率，就能提高整个算法的效率。

我们在处理的时候，不仅需要知道当前数据，还需要知道数据的位置，而又需要提高查找的效率，因此可以使用map映射或者哈希表
>对一个字符串算出hash码后，这个hash码相当于一个指针，就可以直接指向其存储位置，从而是O(1)的时间复杂度。

##cpp
-------

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

///==================
/// 思路如下
///==================
///
/// 采用哈希表或者map来做
/// 对于数组numbers中的每一个数numbers[i]
/// 判断target - numbers[i]在不在哈希表中
/// 如果在那么就返回这两个叔的位置
/// 如果不在就继续往下找, 同时将当前的数存入哈希表中
#define DEBUG
class Solution
{
public:
    
    std::vector<int> twoSum(std::vector<int> &numbers,  //  the array of the number
                            int target) //  the sum of the two num
    {
        std::unordered_map<int, int> mp;

        std::vector<int> ans;
        
        //  用哈希表来做
        for(int i = 0; i < numbers.size(); i ++)    //  对于数组中的每个数据
        {
            //  判断target - numbers[i]在不在
            if(mp.count(target - numbers[i]))   //  如果在里面   
            {
                //  那么numbers中就存在两个数和为target
                ans.push_back(mp[target - numbers[i]] + 1); 
                ans.push_back(i + 1);
                break;
            }
            
            if(mp.count(numbers[i]) != 1)
            {
                mp[numbers[i]] = i;
            }
        }
        return ans;
    }
};


#ifdef DEBUG
int main(void)
{
    std::vector<int> numbers = {3, 2, 4};
    int target = 6;

    Solution solu = Solution();
    std::cout <<"[" <<solu.twoSum(numbers, target)[0] <<", " <<solu.twoSum(numbers, target)[1] <<"]" <<std::endl;;

}
#endif
```


##python
-------

python中的字典有和map一样的功能

```
#!/usr/bin/env python
#coding=utf-8
#
#  找出数组中的两个数，这两个数和为target
#  扫到x时看前面Hash的数里有没有target-x，
#  然后将x也放进Hash表。

class Solution:

    # @return a tuple, (index1, index2)
    def twoSum(self, num, target):
        
        # python中字典dict类似于map的
        dict = {}
    
        for i in range(len(num)):   #  对于每一个num
    
            # 判断target - num[i]在不在在字典中
            if dict.get(target - num[i], None) == None: #如果不在
    
                dict[num[i]] = i   # 将该数存入字典中
    
            else:
                # 否则这两个数的和为target, 则返回
                return (dict[target - num[i]] + 1, i + 1)


if __name__ == "__main__" :
    
    num = [3, 2, 4]
    target = 6

    solution = Solution()
    print solution.twoSum(num, target)
```
