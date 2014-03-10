#!/usr/bin/python

for i in range(1,31):
    fizz = ''
    buzz = ''
    if i % 3 == 0:
        fizz = 'fizz'
    if i % 5 == 0:
        buzz = 'buzz'
    if len(fizz) > 0 or len(buzz) > 0:
        print('{:d}: {:s}{:s}'.format(i, fizz, buzz))
