#!/usr/bin/env python
#coding=utf-8
#
#
#Given an array of integers, 
#
#find two numbers such that they add up to a specific target number.
#
#The function twoSum should return indices of the two numbers 
#
#such that they add up to the target, 
#
#where index1 must be less than index2. 
#
#Please note that your returned answers 
#
#(both index1 and index2) are not zero-based.
#
#You may assume that each input would have exactly one solution.
#
#



#  找出数组中的两个数，这两个数和为target
#  扫到x时看前面Hash的数里有没有target-x，
#  然后将x也放进Hash表。

class Solution:

    # @return a tuple, (index1, index2)
    def twoSum(self, num, target):
        
        # python中字典dict类似于map的
        dict = {}
    
        for i in range(len(num)):   #  对于每一个num
    
            # 判断target - num[i]在不在在字典中
            if dict.get(target - num[i], None) == None: #如果不在
    
                dict[num[i]] = i   # 将该数存入字典中
    
            else:
                # 否则这两个数的和为target, 则返回
                return (dict[target - num[i]] + 1, i + 1)


if __name__ == "__main__" :
    
    num = [3, 2, 4]
    target = 6

    solution = Solution()
    print solution.twoSum(num, target)