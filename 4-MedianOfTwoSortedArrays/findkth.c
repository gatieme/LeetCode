/*************************************************************************
    > File Name: 1.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年04月01日 星期五 17时53分29秒
 ************************************************************************/

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
