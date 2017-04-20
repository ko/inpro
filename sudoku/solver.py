#!/usr/bin/python

def getPuzzle(solved=False):
    if solved is False:
        return '.96...43.7..4.6..53..7.9..6.839.257.....6.....273.169.2..6.4..35..1.8..4.64...82.'
    else:
        return '896215437712436985345789216683942571951867342427351698278694153539128764164573829'

def cross(a, b):
    return [ i+j for i in a for j in b ]

def getRows(puzzle):
    n = 9
    return [ puzzle[i:i+n] for i in range(0, len(puzzle), n) ]

def getCols(puzzle):
    n = 9
    
def grid_values(tiles, puzzle):
    return { tiles[i]: puzzle[i] for i in range(0, len(puzzle)) }

def show_grid(grid):
    line = ''
    for cpos, c in enumerate('ABCDEFGHI'):
        for rpos, r in enumerate('123456789'):
            key = c+r
            line += grid[key]
            if (rpos + 1) % 3 == 0 and rpos != 8:
                line += '|'
            if rpos == 8:
                line += '\n'
            else:
                line += ' '
        if ((cpos+1) % 3) == 0 and cpos != 8:
            line += '-----+------+-------\n'
    print line

def main():
    puzzle = getPuzzle()
    tiles = cross('ABCDEFGHI', '123456789')
    rows = getRows(getPuzzle())
    grid = grid_values(tiles, puzzle)
    show_grid(grid)

main()
