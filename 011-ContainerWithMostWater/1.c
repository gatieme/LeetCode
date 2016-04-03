#include <stdio.h>
#include <stdlib.h>

#define __tmain main

int maxArea(int *height, int heightSize)
{
    // IMPORTANT: Please reset any member data you declared, as

    // the same Solution instance will be reused for each test case.

    int area_max=0;
    int area_tmp=0;
    int height_min=0;
    int i=0;
    int j = heightSize - 1;

    while(i<j)
    {

        height_min = height[i] < height[j] ? height[i] : height[j];

        area_tmp = (j-i) * (height[i] < height[j] ? height[i] : height[j]);

        if(area_tmp > area_max)
        {
            area_max = area_tmp;
        }

        if(height[j] > height[i])
        {

            while(height[i] <= height_min)
            {

                i++;

            }

        }
        else
        {

            while(height[j]<=height_min)
            {
                j--;

            }

        }

        //    std::cout<<"area_tmp="<<area_tmp<<", i="<<i<<" ,j="<<j<<", area_max="<<area_max<<std::endl;

    }

    return area_max;

}

int __tmain(void)
{


    return EXIT_SUCCESS;

}


