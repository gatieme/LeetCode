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
    /*
        所以算法就是：
        从头到尾扫描prices，如果i比i-1大
        那么price[i] – price[i-1]就可以计入最后的收益中
        这样扫描一次O(n)就可以获得最大收益了。
    */
    int maxProfit(vector<int>& prices)
    {
        if(prices.size( ) < 2)
        {
            return 0;
        }
        int profit = 0;
        for(int i = 1; i < prices.size( ); i++)
        {
            if(prices[i] > prices[i - 1])
            {
                profit += prices[i] - prices[i - 1];
            }
        }

        return profit;
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

