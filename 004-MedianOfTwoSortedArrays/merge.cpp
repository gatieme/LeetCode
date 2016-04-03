#include <iostream>
#include <vector>

#define DEBUG

using namespace std;


class Solution
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size();
        int n = nums2.size();

        vector<int> array = merge(nums1, nums2);        //  利用归并进行合并

        //  len = m + n为偶数时, 应该返回中间两个数的平均值
        //      下标    len / 2 = (len + 1) / 2, (len - 1) / 2
        //  len = m + n位奇数时, 应该返回最中间那个数
        //      下标    (len - 1) / 2 = len / 2
        //
        //  因此 直接返回 下标 (len- 1) / 2和len / 2的平均值
        return ((double)(array[(m + n - 1) / 2] + array[(m + n) / 2])) / 2;
    }


    vector<int> merge(vector<int> A, vector<int> B)
    {
        vector<int> ret;

        int m = A.size();
        int n = B.size();

        int i = 0;
        int j = 0;

        while(i < m && j < n)       //  遍历两个序列
        {
            //  依次按照先后顺序入队
            if(A[i] <= B[j])
            {
                ret.push_back(A[i]);
                i ++;
            }
            else
            {
                ret.push_back(B[j]);
                j ++;
            }
        }

        //  合并剩余序列
        if(i == m)      //  此时B序列未完全入队
        {
            while(j < n)
            {
                ret.push_back(B[j]);
                j ++;
            }
        }

        if(j == n)      //  此时A序列未完全入队
        {
            while(i < m)
            {
                ret.push_back(A[i]);
                i ++;
            }
        }

        return ret;
    }
};



#ifdef DEBUG
int main()
{
    int a[] =  {1, 3, 5, 7, 9,};
    int b[] =  {2, 4, 6, 8, 10,};

    vector<int> aa(a, a + 5);
    vector<int> bb(b, b + 5);
    Solution solu;

    std::cout <<solu.findMedianSortedArrays(aa, bb) <<std::endl;


    return 0;
}
#endif
