#include <iostream>
#include <vector>
#include <unordered_map>

///==================
/// 思路如下
///==================
///
/// 采用哈希表或者map来做
/// 对于数组numbers中的每一个数numbers[i]
/// 判断target - numbers[i]在不在哈希表中
/// 如果在那么就返回这两个叔的位置
/// 如果不在就继续往下找, 同时将当前的数存入哈希表中
#define DEBUG
class Solution
{
public:
    
    std::vector<int> twoSum(std::vector<int> &numbers,  //  the array of the number
                            int target) //  the sum of the two num
    {
        std::unordered_map<int, int> mp;

        std::vector<int> ans;
        
        //  用哈希表来做
        for(int i = 0; i < numbers.size(); i ++)    //  对于数组中的每个数据
        {
            //  判断target - numbers[i]在不在
            if(mp.count(target - numbers[i]))   //  如果在里面   
            {
                //  那么numbers中就存在两个数和为target
                ans.push_back(mp[target - numbers[i]] + 1); 
                ans.push_back(i + 1);
                break;
            }
            
            if(mp.count(numbers[i]) != 1)
            {
                mp[numbers[i]] = i;
            }
        }
        return ans;
    }
};


#ifdef DEBUG
int main(void)
{
    std::vector<int> numbers = {3, 2, 4};
    int target = 6;

    Solution solu = Solution();
    std::cout <<"[" <<solu.twoSum(numbers, target)[0] <<", " <<solu.twoSum(numbers, target)[1] <<"]" <<std::endl;;

}
#endif