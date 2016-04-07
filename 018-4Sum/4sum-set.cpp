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
