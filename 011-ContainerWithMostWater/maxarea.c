#include <stdio.h>
#include <stdlib.h>

#define __tmain main

int maxArea(int *height, int length)
{
    int area_max = 0;
    int area_tmp = 0;
    int height_min;


    for(int start = 0, end = length - 1;
        start < end;)
    {

        height_min = height[start] < height[end] ? height[start] : height[end];

        area_tmp = (end - start)* height_min;

        if(area_tmp > area_max)
        {
            area_max = area_tmp;
        }

        if(height[end] > height[start])
        {
            start++;
        }
        else
        {
            end--;
        }
    }
    return area_max;

}


int __tmain( )
{


    return EXIT_SUCCESS;
}
