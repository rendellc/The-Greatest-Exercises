#!/usr/bin/python3
from sys import stdin
Inf = float(1e10)

def mst(graph):
    i = 0
    while i < 10000000:
        i += 1


    this_node = 0
    k = len(graph)
    noder_ink = []
    node_tall = []
    node_in_consideration = []
    for iterasjoner in range(k-1):
        for node, weight in enumerate(graph[this_node]):
            if node not in node_tall and weight < Inf:
                node_in_consideration.append((this_node, node, weight))  
        
        minimum, min_edge, min_index = Inf, Inf, Inf # changed from Inf, None, None
        for i, kant in enumerate(node_in_consideration):
            if kant[2] < minimum:
                minimum = kant[2]
                minimum_kant = kant
                minste_indeks = i
        index, kant = minste_indeks, minimum_kant
        node_in_consideration.pop(index)
        noder_ink.append(kant)
        node_tall.append(this_node)
        this_node = kant[1]
    maks = -Inf
    for node in noder_ink:
        if node[2] > maks:
            maks = node[2]
    return maks
    


lines = []
for str in stdin:
    lines.append(str)
n = len(lines)
neighbour_matrix = [None] * n
node = 0
for line in lines:
    neighbour_matrix[node] = [Inf] * n
    for k in line.split():
        data = k.split(':')
        neighbour = int(data[0])
        weight = int(data[1])
        neighbour_matrix[node][neighbour] = weight
    node += 1
result = mst(neighbour_matrix)
if result:
    print (result)
else:
    print(Inf)

#try:
#    main()
#except: 
#    print(Inf)