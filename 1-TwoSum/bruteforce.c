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