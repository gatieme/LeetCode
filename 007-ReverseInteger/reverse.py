#!/usr/bin/python
# -*- coding: utf-8 -*-



import math

class Solution:
    # @return an integer
    def reverse(self, x):
        revx = int(str(abs(x))[::-1])
        if revx > math.pow(2, 31):
            return 0
        else:
            return revx * cmp(x, 0)

# debug
s = Solution()
print s.reverse(1234)