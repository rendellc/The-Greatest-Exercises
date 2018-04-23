#!/usr/bin/python3

from sys import stdin
from math import floor

def quick_sort(A):
    if len(A) == 0:
        return []

    smaller = []
    larger = []

    for i in range(1, len(A)):
        if A[i] < A[0]:
            smaller.append(A[i])
        else:
            larger.append(A[i])

    return quick_sort(smaller) + [A[0]] + quick_sort(larger)



def sort_list(A):
    return quick_sort(A)

def find(A, lower, upper):

    if lower < A[0]:
        lower_result = A[0]
    else:
        lower_result = A[0]
        i = 1
        while lower_result < lower and i < len(A):
            lower_result = A[i]
            i += 1
        if lower_result > lower:
            lower_result = A[i - 2]
        else:
            lower_result = A[i - 1]

    if upper > A[~0]:
        upper_result = A[~0]
    else:
        upper_result = A[~0]
        i = len(A) - 2
        while upper_result > upper and i >= 0:
            upper_result = A[i]
            i -= 1

        if upper_result < upper:
            upper_result = A[i + 2]
        else:
            upper_result = A[i + 1]


    return lower_result, upper_result

def main():

    input_list = []
    for x in stdin.readline().split():
        input_list.append(int(x))

    sorted_list = sort_list(input_list)

    for line in stdin:
        word = line.split()
        minimum = int(word[0])
        maximum = int(word[1])
        result = find(sorted_list, minimum, maximum)
        print(str(result[0]) + " " + str(result[1]))


if __name__ == "__main__":
    main()
