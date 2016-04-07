#链接
------- 

>LeetCode题目：https://leetcode.com/problems/4sum
>
>GitHub代码：https://github.com/gatieme/LeetCode/tree/master/018-4Sum
>
>CSDN题解：http://blog.csdn.net/gatieme/article/details/51089460

#题意
-------

>Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
>
>Note:
>Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
>
>    A solution set is:
>    (-1,  0, 0, 1)
>    (-2, -1, 1, 2)
>    (-2,  0, 0, 2)

给一个包含n个数的整数数组S，在S中找到所有使得和为给定整数target的四元组(a, b, c, d)。
例如，对于给定的整数数组S=[1, 0, -1, 0, -2, 2]和target=0. 满足要求的四元组集合为：

```
(-1, 0, 0, 1)
(-2, -1, 1, 2)
(-2, 0, 0, 2)
```

四元组(a, b, c, d)中，需要满足a <= b <= c <= d
答案中不可以包含重复的四元组


#借用3Sum的方法
-------

我们采用2sum，以及3sum的方法，先排序后，用两趟循环循环分别遍历第一个数和第二个数，然后剩余的两个数，用二分查找的方法去找。

1.    对数组排序

2.    确定四元数中的前两个（a，b）

3.    遍历剩余数组确定两外两个（c，d），确定cd时思路跟3Sum确定后两个数据一样，二分查找左右逼近。

```cpp
#include <iostream>
#include <vector>

#include <algorithm>


using namespace std;


//#define __tmain main

class Solution
{

public:

    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        vector<vector<int>> res;
        int size = nums.size( );

        sort(nums.begin( ), nums.end( ));


        for(int i = 0; i < size - 3; i++)
        {
            //skip same i
            while(i > 0 && i < size - 3 && nums[i] == nums[i - 1])
            {
                //cout <<"skip all " <<nums[i] <<endl;
                i++;
            }
            for(int j = i + 1; j < size - 2; j++)
            {
                //skip same i
                while(j > i + 1 && j < size - 2 && nums[j] == nums[j - 1])
                {
                    //cout <<"skip all " <<nums[i] <<endl;
                    j++;
                }

                for(int start = j + 1, end = size - 1;
                    start < end; )
                {
                    int sum = nums[i] + nums[j] + nums[start] + nums[end];

                    if(sum == target)
                    {

                        vector<int> cur(4);
                        cur[0] = nums[i];
                        cur[1] = nums[j];
                        cur[2] = nums[start];
                        cur[3] = nums[end];

                        res.push_back(cur);

                        start++;
                        end--;
                        //skip same j
                        while(start < end
                           && nums[start] == nums[start - 1])
                        {
                            //cout <<"skip all " <<nums[start] <<endl;
                            start++;
                        }

                        //skip same k
                        while(end > start && nums[end] == nums[end + 1])
                        {
                            //cout <<"skip all " <<nums[end] <<endl;
                            end--;
                        }
                    }
                    else if(sum > target)
                    {
                        end--;
                        while(end > start && nums[end] == nums[end + 1])
                        {
                            //cout <<"skip all " <<nums[end] <<endl;
                            end--;
                        }

                    }
                    else if(sum < target)
                    {
                        start++;
                        while(start < end
                           && nums[start] == nums[start - 1])
                        {
                            //cout <<"skip all " <<nums[start] <<endl;
                            start++;
                        }
                    }
                }
            }
        }

        return res;

    }
};




int __tmain()
{
    vector<vector<int>> result;
    Solution solution;
    vector<int> vec;
    vec.push_back(-3);
    vec.push_back(-2);
    vec.push_back(-1);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    result = solution.fourSum(vec, 0);

    for(int i = 0; i < result.size( ); i++)
    {
        for(int j = 0; j < result[i].size( ); j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

我们是通过跳过相同的值的方法来去重复的

```cpp
            //skip same i
            while(i > 0 && i < size - 3 && nums[i] == nums[i - 1])
            {
                //cout <<"skip all " <<nums[i] <<endl;
                i++;
            }
```

网上同样思路的方法，看到有些是通过set来去重复的

>参见 [[LeetCode]18.4Sum](https://yq.aliyun.com/articles/3883)

```cpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target)
    {
        int i,j,start,end;
        int Len = num.size();
        vector<int> triplet;
        vector<vector<int>> triplets;
        set<vector<int>> sets;
        //排序
        sort(num.begin(),num.end());
        for(i = 0;i < Len-3;i++)
        {
            for(j = i + 1;j < Len - 2;j++)
            {
                //二分查找
                start = j + 1;
                end = Len - 1;
                while(start < end){
                    int curSum = num[i] + num[j] + num[start] + num[end];
                    //相等 -> 目标
                    if(target == curSum)
                    {
                        triplet.clear();
                        triplet.push_back(num[i]);
                        triplet.push_back(num[j]);
                        triplet.push_back(num[start]);
                        triplet.push_back(num[end]);
                        sets.insert(triplet);
                        start ++;
                        end --;
                    }
                    //大于 -> 当前值小需要增大
                    else if(target > curSum)
                    {
                        start ++;
                    }
                    //小于 -> 当前值大需要减小
                    else{
                        end --;
                    }
                }//while
            }
        }//for
        //利用set去重
        set<vector<int>>::iterator it = sets.begin();
        for(; it != sets.end(); it++)
            triplets.push_back(*it);
        return triplets;
    }
};
int main() {
    vector<vector<int>> result;
    Solution solution;
    vector<int> vec;
    vec.push_back(-3);
    vec.push_back(-2);
    vec.push_back(-1);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    result = solution.fourSum(vec,0);
    for(int i = 0;i < result.size();i++)
    {
        for(int j = 0;j < result[i].size();j++)
        {
            cout <<result[i][j]);
        }
        cout <<endl;
    }
    return 0;
}
```


#递归求解
-------

类似于15题求解的3Sum问题，这次求解4Sum问题，本质是相同的，不可以采用穷举法； 
其实求解4Sum问题可以分解为求3Sum问题，对数列依次遍历i，我们只需得到在第i个数后面，找出所有和为（target?nums[i]）的三元组，同理求3Sum又可以退化为2Sum，进而退化为1Sum。 
因此，采用递归的思想解决KSum问题。

```cpp
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>

using namespace std;


class Solution {
public:
	/*4-sum算法，递归实现，TLE*/
	vector<vector<int>> fourSum1(vector<int>& nums, int target) {
		if (nums.empty())
			return vector<vector<int>>();

		sort(nums.begin(), nums.end());

		return k_Sum(nums, 0, 4, target);
	}
	/*k-sum算法*/
	vector<vector<int>> k_Sum(vector<int> &nums, int begPos, int count, int target)
	{
		if (nums.empty())
			return vector<vector<int>>();
		/*所输入序列为已排序*/
		int len = nums.size();
		unordered_set<int> visited;
		vector<vector<int>> ret;
		vector<int> tmp;
		/*2-sum 处理*/
		if (2 == count)
		{
			int i = begPos, j = len - 1;
			while (i < j)
			{
				int sum = nums[i] + nums[j];
				if (sum == target && visited.find(nums[i]) == visited.end())
				{
					tmp.clear();
					tmp.push_back(nums[i]);
					tmp.push_back(nums[j]);
					ret.push_back(tmp);

					/*加入已访问set*/
					visited.insert(nums[i]);
					visited.insert(nums[j]);

					++i;
					--j;
				}//if
				else if (sum < target)
					++i;
				else
					--j;
			}//while
		}//if
		else{
			for (int i = begPos; i < len; ++i)
			{
				if (visited.find(nums[i]) == visited.end())
				{
					visited.insert(nums[i]);
					/*得到k-1 sum的序列*/
					vector<vector<int>> subRet = k_Sum(nums, i+1, count - 1, target-nums[i]);
					if (!subRet.empty())
					{
						int sz = subRet.size();
						for (int j = 0; j < sz; ++j)
						{
							subRet[j].insert(subRet[j].begin(), nums[i]);
						}//for
						ret.insert(ret.end(), subRet.begin(), subRet.end());
					}//if
				}//if
			}//for
		}//else
		/*返回结果集*/
		return ret;
	}

	/*4-sum算法，方法二，2-sum的变形*/
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		if (nums.empty() || nums.size() < 4)
			return vector<vector<int>>();

		sort(nums.begin(), nums.end());
		int len = nums.size();
		set<vector<int>> tmpRet;
		vector<vector<int>> res;

		for (int i = 0; i < len; ++i)
		{
			for (int j = i + 1; j < len; ++j)
			{
				int beg = j + 1, end = len - 1;
				while (beg < end)
				{
					int sum = nums[i] + nums[j] + nums[beg] + nums[end];
					if (sum == target)
					{
						vector<int> tmp = { nums[i], nums[j], nums[beg], nums[end] };
						tmpRet.insert(tmp);

						++beg;
						--end;
					}
					else if (sum < target)
					{
						++beg;
					}
					else
						--end;
				}//while
			}//for
		}//for
		auto iter = tmpRet.begin();
		while (iter != tmpRet.end())
		{
			res.push_back(*iter);
			++iter;
		}//while
		return res;
	}

};

int main()
{
	Solution s;
	vector<int> v = { 1, 0, -1, 0, -2, 2 };
	vector<vector<int>>ret = s.fourSum(v,0);

	system("pause");
	return

```
