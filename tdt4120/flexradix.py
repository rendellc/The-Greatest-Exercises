#!/usr/bin/python3

from sys import stdin
from string import ascii_lowercase as chars
from random import randint, choice
from operator import itemgetter
from collections import defaultdict


def key(word, i):
    #print('word:', word, '\ti:', i)
    if word[i] == ' ':
        return 0
    
    return ord(word[i]) - ord(chars[0]) + 1


def countsort(A, position):
    C = [-1]*(len(chars) + 1)      
    output = ['']*len(A)
    
    for word in A:
        C[key(word, position)] += 1

    #print('Primary count complete:\n', C)
    
    for i in range(1, len(C)):
        C[i] += C[i - 1] + 1

    #print('Accumulation complete:\n', C)
    
    for i in range(len(A)-1, -1, -1):
        #print('sorting word', A[i], '\ton pos', position)
        calc_key = key(A[i], position)
        #print('calc_key:', calc_key)
        output[C[calc_key]] = A[i]
        C[calc_key] -= 1

    #print('Countsort complete on position:', position, '\n', output)
    
    
    return output

def flexradix(A, d):
    for i in range(d-1, -1, -1):
        A = countsort(A, i)

    return A

def padarray(A, length):
    for i in range(len(A)):
        A[i] += ' '*(length - len(A[i]))
    
    return A

def removepad(A):
    return [word.strip(' ') for word in A] 

def main():
    d = int(stdin.readline())
    strings = [] #['kobra', 'alge', 'agg', 'kort', 'hyblen']
    
    for line in stdin:
        strings.append(line.rstrip())

    #print(strings)
    A = padarray(strings, d)
    #print(A)
    A = flexradix(A, d)
    #print(A)
    A = removepad(A)
    #print(A)
    
    for string in A:
        print(string)

    return A

if __name__ == "__main__":
    A = main()
    
