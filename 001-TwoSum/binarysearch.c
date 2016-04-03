#include <stdio.h>
#include <stdlib.h>


#define DEBUG


////////////////////////////////////////////////////
///
///
/// 二分查找
///
///
////////////////////////////////////////////////////
int BinarySearch(int *array, int length, int target)
{
    int low = 0;
    int high = length - 1;
    int middle;

    while(low <= high)
    {
        middle = (low + high)/2;

        if(array[middle] == target)
        {
            return middle;
        }
        else if(array[middle] > target)
        {
            high = middle - 1;
        }
        else
        {
            low = middle + 1;
        }
    }
    // not find
    return -1;
}


#ifdef DEBUG

int main(void)
{
    int nums[5] = {-1, -2, -3, -4, -5};

    printf("%d",BinarySearch(nums, 5, -2));
    
    //int *answer = NULL;
    //answer = twoSum(nums, 5, -8);
    //printf("[%d, %d]\n", answer[0], answer[1]);
}
#endif