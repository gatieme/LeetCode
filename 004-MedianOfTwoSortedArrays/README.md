#链接
-------

>题目地址：https://leetcode.com/problems/median-of-two-sorted-arrays/
>
>github代码：https://github.com/gatieme/LeetCode/tree/master/004-MedianOfTwoSortedArrays
>
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51045252
>
>这也是2015年4月阿里实习生招人附加题第一题我用的

#题目描述
-------
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Subscribe to see which companies asked this question

给定两个有序序列，要求两个序列合并后的中位数。



#归并算法
-------
我用的是归并算法，时间复杂度和空间复杂度都为$O（M+N）$

```
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

```


#分治算法
-------

##第k小的数
-------

现在我们考虑一个现实中的模型，
A班和B班的同学人数分别为aEnd与bEnd，有天体育老师说要找他们中间第k矮的同学，于是先将两班的同学按从小到大的顺序站成两队。

假设k是为13。那此时A班派出第x矮的同学，B班派出第y矮的同学来比较（注意：此时x+y<=k）。若x为6，y为7。

如果A的第6位同学比B的第7位同学还要矮，那如果两班整体排序，那A班的6位同学一定是要站在B班的第7位前面，最多A班第6位就站在B班第7位的前一位，最多就整体排第12，怎么都轮不到他排第k=13个。于是可以把A班前6位丢掉，在剩下的两个队列里面找。但是就不再是找第k个，而是找第k-x个了。因为x做了基数被丢掉了。

当然，上述例子，只要（x+y)<=k的情况，x与y只要是为非负的，那都可以。

只是为了效率，一般去x=y=(k/2)。而当某一队被丢到剩下人很少或者没人了，那这个取值就要根据具体情况来取值。


##算法描述
-------
好了现在我们描述下算法的模型

首先假设数组A和B的元素个数都大于k/2

我们比较A[k/2-1]和B[k/2-1]两个元素，这两个元素分别表示A的第k/2小的元素和B的第k/2小的元素。

这两个元素比较共有三种情况：>、<和=。

*	如果$A[k/2-1]<B[k/2-1]$，这表示A[0]到A[k/2-1]的元素都在A和B合并之后的前k小的元素中。换句话说，**A[k/2-1]不可能大于两数组合并之后的第k小值**，所以我们可以将其抛弃。

>证明也很简单，可以采用反证法。假设A[k/2-1]大于合并之后的第k小值，我们不妨假定其为第（k+1）小值。由于A[k/2-1]小于B[k/2-1]，所以B[k/2-1]至少是第（k+2）小值。但实际上，在A中至多存在k/2-1个元素小于A[k/2-1]，B中也至多存在k/2-1个元素小于A[k/2-1]，所以小于A[k/2-1]的元素个数至多有k/2+ k/2-2，小于k，这与A[k/2-1]是第（k+1）的数矛盾。

*	当A[k/2-1]>B[k/2-1]时存在类似的结论。

*	当A[k/2-1]=B[k/2-1]时，我们已经找到了第k小的数，也即这个相等的元素，我们将其记为m。由于在A和B中分别有k/2-1个元素小于m，所以m即是第k小的数。(这里可能有人会有疑问，如果k为奇数，则m不是中位数。这里是进行了理想化考虑，在实际代码中略有不同，是先求k/2，然后利用k-k/2获得另一个数。)

通过上面的分析，我们即可以采用递归的方式实现寻找第k小的数。此外我们还需要考虑几个边界条件：

1.	如果A或者B为空，则直接返回B[k-1]或者A[k-1]；

2.	如果k为1，我们只需要返回A[0]和B[0]中的较小值；

3.	如果A[k/2-1]=B[k/2-1]，返回其中一个；




##代码
-------

```c


#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define DEBUG

#define max(x, y)  ((x) > (y) ? (x):(y))
#define min(x, y)  ((x) < (y) ? (x):(y))


/*
 *  寻找两个排序好的数组中，第K大的那个数
 *
 *  那么这个第K大的数，一定在
 * **/
double findKth(int a[], int m, int b[], int n, int k)
{
	//  always assume that m is equal or smaller than n
    //
    //  （一）首先，我们规定A数组比B数组短。
    //
    //  这样处理的好处在于：我们所需的(k-1)/2位置可能大于某个数组总长度，
    //
    //  规定A短之后，只需要考虑超过A的长度，不需要再复制代码分情况讨论了。
    //
    //  这里需要斟酌一下：为什么不是k/2？ k/2±1？而是(k-1)/2
    //
    //  我的思考如下：
    //
    //  如果k==1,2，就是需要比较头两个元素，因此下标为0
    //
    //  如果k==3,4，就是需要比较第1个元素，因此下标为1
    //
    //  综上归纳而得。
	if (m > n)
    {
		return findKth(b, n, a, m, k);
    }

    //  （二）其次，把特殊情况处理掉。
    //
    //  (1)A数组为空时，即返回B数组第k个元素。
    //
    //  (2)k==1时，即返回A[0]、B[0]中小的那个
    //
    if (m == 0)
    {
        return b[k - 1];
    }

    if (k == 1)
    {
        return min(a[0], b[0]);
    }

    //divide k into two parts
    //
    //（三）接下来再分为两种情况：
    //
    //  (k - 1) / 2位置是否超过A数组长度？
    //
    //  （1）若超过，则A数组派出的代表Acandi就是最后元素A[m-1]，B派出的代表Bcandi是B[k-m-1]
    //
    //      (a)Acandi==Bcandi，那么正好有k-2个元素比Acandi、Bcandi小，所以第k个元素就是Acandi/Bcandi
    //
    //      (b)Acandi > Bcandi，那么最多只有m-1+k-m-1=k-2个元素比Bcandi小，因此包括Bcandi在内之前的k-m个B数组元素肯定不是第k个数，所以删去，子问题变为寻找第k-(k-m)个元素
    //
    //      (c)Acandi < Bcandi，那么最多只有m-1+k-m-1=k-2个元素比Acandi小，因此包括Acandi在内之前的整个A数组元素m个元素肯定不是第k个数，所以删去，子问题变为寻找第k-m个元素
    //
    //
    //  （2）若不超过，则A数组派出的代表Acandi就是A[(k-1)/2]，B派出的代表Bcandi是B[(k-1)/2]
    //
    //      (a)Acandi==Bcandi，那么正好有(k-1)/2+(k-1)/2=k-1个元素比Acandi、Bcandi小，所以第k个元素就是Acandi/Bcandi
    //
    //      如果不相等，对于Acandi 、Bcandi本身是否需要取舍就要注意分析了。
    //
    //      经过举几个例子简单分析就很容易发现，k为奇数时，需要保留小的candidate，舍弃大的。
    //
    //      而k为偶数时，需要保留大的candidate，舍弃小的。
    //
    //      (b)Acandi > Bcandi
    //
    //          (b.1)k为奇数，保留Bcandi，删除Bcandi前面的(k-1)/2个元素，删除A及A后面的元素（保留A中前(k-1)/2个元素）
    //
    //          (b.2)k为偶数，保留Acandi，删除Bcandi及前面的(k-1)/2+1个元素，删除A后面的元素（保留A中前(k-1)/2+1个元素）
    //
    //      (c)Acandi < Bcandi
    //
    //          同(b)，略去不赘述了。

    int pa = min(k / 2, m), pb = k - pa;

    //  判断舍弃哪一部分[A中前pa部分, 或是B中前pb部分]
	if (a[pa - 1] < b[pb - 1])          //  A中数小, 则可以舍弃A中前pa那个数
    {
        //  继续在a + pa和B中, 寻找第k-pa个数
        return findKth(a + pa, m - pa, b, n, k - pa);
    }
    else if (a[pa - 1] > b[pb - 1])     //  同理 B中那个数小, 则可以舍弃B中前pb个数
    {
        //  继续在a和b + pb中寻找第k - pb个数
        return findKth(a, m, b + pb, n - pb, k - pb);
    }
    else        //  如果两个数相等, 那么好了，他们就是那个要找的第K个数
    {
		return a[pa - 1];
    }
}



double findMedianSortedArrays(int *A, int m, int *B, int n)
{

    int total = m + n;

    if (total & 0x1)
    {
        return findKth(A, m, B, n, total / 2 + 1);
    }
    else
    {
        return (findKth(A, m, B, n, total / 2) + findKth(A, m, B, n, total / 2 + 1)) / 2;
    }
}


#ifdef DEBUG
int main()
{
    int a[] =  {1, 3, 5, 7, 9,};
    int b[] =  {2, 4, 6, 8, 10,};

    printf("%f\n", findMedianSortedArrays(a, 5, b, 5));


    return EXIT_SUCCESS;
}
#endif

```
