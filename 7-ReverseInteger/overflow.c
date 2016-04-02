/*************************************************************************
    > File Name: 1.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年04月02日 星期六 21时26分56秒
 ************************************************************************/

/*题意：
 *
 * 反转一个数。
 *
 * 分析：
 *
 * ==1==  overflow的问题?
 *
 * 注意读入和返回的数都是 int 型的，
 *
 * 这时就要考虑反转后这个数会不会超 int，超的话就返回 0 。
 *
 * 检测很简单, 将 res 设为 long, 那你一个 int 怎么反转都不会超出 long 的范围了吧? 然后判断 res 和 INT_MAX的关系就可以了.
 *
 * 这时处理数时最好用比 int 大的类型，不然恐怕会超范围。
 *
 * 当然也可以用 int ：if (result > (INT_MAX/10))
 *
 * ==2==还有一点就是还要考虑前导零。
 *
 * 后几位是0的情况(10, 100.)?
 *
 * */


#include <stdio.h>
#include <stdlib.h>


#include <limits.h>     // use `INT_MAX`
#include <math.h>       //  use `fabs`

#define  DEBUG

#ifdef DEBUG
int main()
{
//    printf("reverse(%ld) = %d\n", 1534236469, reverse(1534236469));  //
    printf("reverse(%ld) = %d\n",-2147483648, reverse(-2147483648));  //

    return EXIT_SUCCESS;
}

#endif




int reverse(int num)
{
    long res = 0;
    while(num != 0)
    {
        res =  res * 10 + num % 10;

        num /= 10;
    }
    return res;

}


