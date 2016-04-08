class Solution:
    # @param {integer} n
    # @return {string[]}
    def generateParenthesis(self, n):
        if not n:
            return []
            
        res = []
        self.helper(n, n, res, "")
        return res
        
    def helper(self, left, right, res, line):
        if right < left:
            return
        
        if left == 0 and right == 0:
            res.append(line)
            return
        
        if left > 0:
            self.helper(left - 1, right, res, line + '(')
        
        if right > 0:
            self.helper(left, right - 1, res, line + ')')