/*************************************************************************
    > File Name: panum.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年04月02日 星期六 23时23分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define __tmain main


bool isPalindrome(int x)
{
    long long xx = x;
    long long new_xx = 0;

    while (xx > 0)
    {
        new_xx = new_xx * 10 + xx % 10;
        xx /= 10;

    }

    return new_xx == (long long)x;


}

int __tmain(void)
{

    printf("%d", isPalindrome(12321));
    return EXIT_SUCCESS;

}


