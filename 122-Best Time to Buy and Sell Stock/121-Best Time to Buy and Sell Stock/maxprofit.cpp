#include <iostream>
#include <vector>
using namespace std;


//  调试开关
#define __tmain main

#ifdef __tmain

#define debug cout

#else

#define debug 0 && cout

#endif // __tmain



class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        if(prices.size( ) == 0)
        {
            return 0;
        }    
        int minPrice = prices[0];
        int tempGap, maxGap = INT_MIN;
        for(int i = 1; i < prices.size( ); i++)
        {
            tempGap = prices[i] - minPrice;
            if(tempGap > maxGap)
            {
                maxGap = tempGap;
            }
            if(prices[i] < minPrice)
            {
                minPrice = prices[i];
            }
        }

        return maxGap > 0 ? maxGap : 0;
    }
};


int __tmain( )
{
    int array[] = { 7, 6, 4, 3, 1 };
    vector<int> vec(array, array + 5);
    Solution solu;
    cout <<solu.maxProfit(vec) <<endl;
    
    return 0;
}


解压缩驱动包
tar -zxvf driver.tar.gz 
