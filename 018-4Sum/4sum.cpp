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
