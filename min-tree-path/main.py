#!/usr/bin/python2.7
"""
   2
  4 3
 5 6 7

2 4 1 3

2,3,6,1
"""

"""
                   -7
                 -2  1
              -5   -5  9
           -4   -5   4   4
          -6  -6   2   -1  -5
        3   7   8   -3   7   -9
      -9  -1  -9   6    9   0   7
    -7  0   -6  -8   7   1    -4   9
"""
class Solution:
    LEFT = 'LEFT'
    RIGHT = 'RIGHT'
    ERRORERROR = '-999999999'

    def getChild(self, triangle, parentRow, parentIndex, leftOrRight):
        debug = False 

        if len(triangle) <= parentRow+1:
            if debug is True:
                print 'EROWEXIST'
            return -1

        targetRow = triangle[parentRow+1]

        if leftOrRight is self.LEFT:
            return targetRow[parentIndex]
        elif leftOrRight is self.RIGHT:
            if len(targetRow) <= parentIndex + 1:
                if debug is True:
                    print 'EROWSHORT'
                return -1
            return targetRow[parentIndex+1]

        return -1

    """
    @param triangle: a list of lists of integers.
    @return: An integer, minimum path sum.
    """
    def minimumTotal(self, triangle):
        rowSummary = []
        debug = False 

        # write your code here
        for rowNo, row in enumerate(triangle):
            tmpRow = []
            if rowNo is 0:
                rowSummary.append(row[0])
            if rowNo is len(triangle)-1:
                continue
            for itemNo, item in enumerate(row):
                rollingSummary = rowSummary[itemNo]
                if debug is True:
                    print '---' + str(rollingSummary)

                # left
                leftChild = self.getChild(triangle, rowNo, itemNo, self.LEFT)
                if debug is True: print 'leftChild: ', str(leftChild)
                if leftChild is not self.ERRORERROR:
                    tmpLeft = rollingSummary + leftChild
                    if itemNo > 0:
                        if tmpLeft < tmpRow[-1]:
                            if debug is True: print '?? popping ' + str(tmpRow[-1])
                            tmpRow.pop(-1)
                            tmpRow.append(tmpLeft)
                    else:
                        tmpRow.append(tmpLeft)

                # right
                rightChild =  self.getChild(triangle, rowNo, itemNo, self.RIGHT)
                if debug is True: print 'rightChild: ', rightChild
                if rightChild is not self.ERRORERROR:
                    tmpRight = rollingSummary + rightChild
                    tmpRow.append(tmpRight)

            rowSummary = tmpRow

            if debug is True:
                print rowSummary

        if debug is True:
            print 'FINAL'
            print rowSummary
        return min(rowSummary)

    def __init__(self):
        return

a = [[-7],[-2,1],[-5,-5,9],[-4,-5,4,4],[-6,-6,2,-1,-5],[3,7,8,-3,7,-9],[-9,-1,-9,6,9,0,7],[-7,0,-6,-8,7,1,-4,9],[-3,2,-6,-9,-7,-6,-9,4,0],[-8,-6,-3,-9,-2,-6,7,-5,0,7],[-9,-1,-2,4,-2,4,4,-1,2,-5,5],[1,1,-6,1,-2,-4,4,-2,6,-6,0,6],[-3,-3,-6,-2,-6,-2,7,-9,-5,-7,-5,5,1]]
s = Solution()
print s.minimumTotal(a)

