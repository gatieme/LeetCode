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