#!/usr/bin/python3
# -*- coding: utf-8 -*-
#import timeit
from sys import stdin, stderr, stdout
import cProfile, pstats
import re

pr = cProfile.Profile()
pr.disable()

class Node():
    def __init__(self):
        self.children = {}
        self.pos = []

    def addWord(self, word, pos):
        try:
            self.children[word[0]].addWord(word[1:], pos)
        except KeyError as e:
            self.children[word[0]] = Node()
            self.children[word[0]].addWord(word[1:], pos)
        except IndexError as e:
            self.pos.append(pos)


def bygg(ordliste):
    # SKRIV DIN KODE HER
    head = Node()
    for (word, pos) in ordliste:
        head.addWord(word, pos)

    return head

def posisjoner_spm(word, node, index=0):
    #pr.enable()
    posList = []

    #return [posisjoner(word,child,index+1) for child in node.children.values()]

    for child in node.children.values():
        posList[0:0] = posisjoner(word, child, index + 1)

    #pr.disable()
    return posList


def posisjoner(word, node, index=0):
    # --- base case ---
    if index == len(word):
        return node.pos

    # --- recursive search ---
    try:
   #if word[index] in node.children.keys():
        return posisjoner(word, node.children[word[index]], index + 1)
    #except KeyError:
    except:
        if word[index] == '?':
            return posisjoner_spm(word, node, index)

        return []

def main():

    #ord = stdin.readline().split()
    sentence = stdin.readline()
    print(ord)
    pat = re.compile(r'\w+\?*\w*', re.I|re.M)

    #print(re.findall(pat, ord))

    fi = re.finditer(pat, sentence)
    print("Match:", fi)

    for word in stdin:
        
        print(word, end='')

        #fi = re.findall(pat, sentence)


if __name__ == "__main__":
    #pr.enable()

    main()
    #pr.disable()

    #sortby = 'cumulative'
    #ps = pstats.Stats(pr, stream=stdout).sort_stats(sortby)
    #ps.print_stats()