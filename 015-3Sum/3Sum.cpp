#include <iostream>
#include <vector>

#include <algorithm>


using namespace std;


#define __tmain main

class Solution
{

public:

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> res;
        int size = nums.size( );

        sort(nums.begin( ), nums.end( ));

/*
        for(int index  = 0; index < nums.size(); index++)
        {
            cout <<" "<<nums[index];
        }
        cout <<endl;
*/

        for(int index = 0; index < size ; index++)
        {
            //skip same i
            while(index > 0 && index < size && nums[index] == nums[index - 1])
            {
                //cout <<"skip all " <<nums[index] <<endl;
                index++;
            }


            for(int start = index + 1, end = size - 1;
                start < end; )
            {
                int sum = nums[index] + nums[start] + nums[end];

                if(sum == 0)
                {
                    cout <<nums[index] <<" + " <<nums[start] <<" + " <<nums[end] <<endl;

                    vector<int> cur(3);
                    cur[0] = nums[index];
                    cur[1] = nums[start];
                    cur[2] = nums[end];


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
                else if(sum > 0)
                {
                    end--;
                    while(end > start && nums[end] == nums[end + 1])
                    {
                        //cout <<"skip all " <<nums[end] <<endl;
                        end--;
                    }

                }
                else if(sum < 0)
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

        return res;

    }
};


int __tmain()
{
    int a[6] = { 0, 0, 0 };
    vector<int> nums(a, a + 3);

    Solution solu;
    solu.threeSum(nums);

    return 0;
}

