#链接
-------

>LeetCode题目：https://leetcode.com/problemset/algorithms/
>
>GitHub代码：https://leetcode.com/problems/container-with-most-water/
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51050223
#题意
-------
>Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). nvertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

>

>Note: You may not slant the container.

给定n个非负整数a1,a2,...,an，

其中每个代表一个点坐标（i,ai）。

n个垂直线段，例如线段的两个端点在（i,ai）和（i,0）。

第i条线段的两个端点是(i,0)和(i,ai)，

找到两个线段，与x轴形成一个容器，使其包含最多的水。

任意两个线段（下标索引分别是i和j，假设i<j）能容纳的水量是(j-i)*min(ai,aj)。



#暴力解法
-------

如果不考虑时间复杂度，使用双层循环可以计算出任意两条线段之间能容纳的水量，这样可以计算出两条线段之间能容纳的水量的最大值。时间复杂度是O(n^2)，但是明显这种解法有点惨不忍睹。最终也没想出更好的解法，查看了Discuss，时间复杂度是O(n)的解法。


```c
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

```


#贪心
-------

很巧妙的一个解法，假设先选取的是两端之间的两条线段，这样这两条线段之间的距离是最大的，长度是给定数组的长度减1。那么在这种情况下要容纳更多的水，由于宽度已经是最大的了，只能想法提高线段的高度，这种情况下如果两端是左边比右边高，那么只有可能是将左边的指针右移，否则将右边的指针左移，然后这右回到了初始的问题，这样不断移动下去到左右指针相等为止，代码很简单。下面以输入[1,2,4,3]为例：


>直观的解释是：容积即面积，它受长和高的影响，当长度减小时候，高必须增长才有可能提升面积，所以我们从长度最长时开始递减，然后寻找更高的线来更新候补；


```c
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

```