#!/usr/bin/python3

from sys import stdin
from itertools import repeat
import time

def merge_helper(left, right):
    result = []
    i = 0
    j = 0
    left.append((float('inf'), 'NA'))
    right.append((float('inf'), 'NA'))
    
    for _ in range(len(left) + len(right) - 2):
        if left[i][0] < right[j][0]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
        
    return result

def merge(decks):
    #start_time = time.time()


    while len(decks)>1:
        decks[0] = merge_helper(decks[0], decks[len(decks)-1])
        del decks[len(decks)-1]
    #end_time = time.time()
    #print("Sorting time:", end_time - start_time)

    #start_time = time.time()
    result = ''
    for card in decks[0]:
        result += card[1]
    #end_time = time.time()
    #print("Formatting time:", end_time - start_time)
    
    return result

def main():
    # Read input.
    
    decks = []
    for line in stdin:
        (index, csv) = line.strip().split(':')
        deck = list(zip(map(int, csv.split(',')), repeat(index)))
        decks.append(deck)
    '''
    decks =  [[(1,'i'),(3,'i'),(5,'i'),(8,'i')], [(2,'n')], [(4,'t'),(7,'t')], [(6,'a')], [(9,'v')]]
    '''
    # Merge the decks and print result.
    print(merge(decks))

if __name__ == "__main__":
    main()
