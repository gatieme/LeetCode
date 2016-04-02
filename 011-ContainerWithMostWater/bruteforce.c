#include <stdio.h>
#include <stdlib.h>

#define __tmain main



int maxArea(int *height, int heightSize)
{
    // IMPORTANT: Please reset any member data you declared, as

    // the same Solution instance will be reused for each test case.

    int area_max = 0;
    int area_tmp = 0;
    int height_min = 0;

    int i = 0;
    int j = heightSize - 1;

    area_max = 0;
    for(int start = 0, end = heightSize -1;
        start < end; )
    {

        height_min = height[start] < height[end] ? height[start] : height[end];

        area_tmp = (end - start) * height_min;

        if(area_tmp > area_max)
        {
            area_max = area_tmp;
        }


        if(height[end] > height[start])
        {
            //  只有大于当前最小高度的节点, 才可能出现大的容积
            while(height[start] <= height_min)
            {
                start++;
            }
        }
        else
        {
            while(height[end] <= height_min)
            {
                end--;
            }
        }

        //printf("[%d, %d], area_tmp = %d, area_max = %d\n", start, end, area_tmp, area_max);


    }

    return area_max;

}

int __tmain(void)
{


    return EXIT_SUCCESS;

}


