#!/usr/bin/python3

from sys import stdin


class Node:
    def __init__(self):
        self.child = []
        self.ratatosk = False
        self.next_child = 0
        self.level = 0

def dfs(root):
    parent_stack = [root]
    current = root
    level = 0
    while not current.ratatosk and parent_stack:
        if len(current.child) > current.next_child:
            parent_stack.append(current)
            current.next_child += 1
            current = current.child[current.next_child]
            level += 1
        else:
            current = parent_stack.pop()
            level -= 1
    
    
    return current.level

def bfs(root):
    parent_queue = [root]
    current = root
    level = 0
    
    while not current.ratatosk and parent_queue:
        for c in current.child:
            c.level = level + 1
            parent_queue.append(c)
            
        current = parent_queue.pop(0) 

        level = current.level

    return current.level


function = stdin.readline().strip()
number_of_nodes = int(stdin.readline())
nodes = []
for i in range(number_of_nodes):
    nodes.append(Node())
start_node = nodes[int(stdin.readline())]
ratatosk_node = nodes[int(stdin.readline())]
ratatosk_node.ratatosk = True
for line in stdin:
    number = line.split()
    temp_node = nodes[int(number.pop(0))]
    for child_number in number:
        temp_node.child.append(nodes[int(child_number)])

if function == 'dfs':
    print(dfs(start_node))
elif function == 'bfs':
    print(bfs(start_node))
elif function == 'velg':
    print(bfs(start_node))
