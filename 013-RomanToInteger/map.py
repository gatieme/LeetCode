class Solution:
# @return an integer
def romanToInt(self, s):
    map={"I":1,"V":5,"X":10,"L":50,"C":100,"D":500,"M":1000}
    sum=0
    for i in range(0,len(s)):
        sum+=map[s[i]]     #s[i]

        if i>0 and map[s[i-1]] < map[s[i]]:
            sum=sum-2*map[s[i-1]]

    return sum 
