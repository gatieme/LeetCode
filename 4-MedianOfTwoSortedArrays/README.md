LeetCode
=======


There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Subscribe to see which companies asked this question

#归并算法

merge.cpp       合并的算法，复杂度$O(M + N)$

将两个数组进行进行归并后，返回中间那个数


#分治算法寻找第k小的数

findkth.c       分治查找算法, 复杂度$0(log(M + N)$

每次取两个数组前k/2个数进行比较，比较完成后可舍弃前k/2个数
递归如此直至找到第k个数为止

题目地址 https://leetcode.com/problems/median-of-two-sorted-arrays/

github题解 https://github.com/gatieme/LeetCode/tree/master/4-MedianOfTwoSortedArrays
