#!/usr/bin/python3
# -*- coding: utf-8 -*-
#import timeit
from sys import stdin, stderr, stdout
#import traceback
import cProfile, pstats
#import filecmp

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
    #try:
    #ord = stdin.readline().split()
    ord = stdin.readline()
    print(ord)
    '''
    ordliste = []
    pos = 0
    for o in ord:
        ordliste.append((o, pos))
        pos += len(o) + 1

    toppnode = bygg(ordliste)

    
    '''
    string_list = []
    pos = 0
    for sokeord in stdin:
        sokeord = sokeord.strip()

        soke

        string_list.extend(("%s:"%sokeord))
        posi = posisjoner(sokeord, toppnode)

        posi.sort()
        for p in posi:
            string_list.extend((" %i"%p))
        string_list.extend(('\n'))

    print(''.join(string_list), end='')

    #except:
    #    traceback.print_exc(file=stderr)


if __name__ == "__main__":
    pr.enable()

    main()
    pr.disable()

    sortby = 'cumulative'
    ps = pstats.Stats(pr, stream=stdout).sort_stats(sortby)
    ps.print_stats()