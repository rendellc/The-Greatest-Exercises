from sys import stdin, stderr

#import time

def print_matrix(mat):
    for line in mat:
        print (line)

def get_path_string(path, start, goal):
    #print ("goal: {0}".format(goal))
    #print ("path: {0}".format(path))

    if path[goal] == -1:
        return 0

    path_string = str(goal) + '-'
    current = goal
    while current != start:
        #print (path_string)
        #time.sleep(1.0)
        path_string += str(path[current]) + '-'
        current = path[current]

    return path_string[~1::-1] #remove last '-'
    



def best_path(nm, prob):
    complete = [False for _ in prob] 
    best_prob = [0.0 for _ in prob]  # probabillity of reaching any node, including the probabillity at the node
    best_path = [-1 for _ in prob]
    best_prob[0], best_path[0] = prob[0], 0

    #data = zip(complete, best_prob)

    queue = [0]
    while queue:
        active = queue.pop(0)
        complete[active] = True

        neighbours = [] # (neighbour, prob)

        # add neighbours to queue
        for node in range(len(nm[active])):
            if nm[active][node] == 1 and not complete[node]:
                neighbours.append((node, prob[node]))
        neighbours = [n for n,_  in sorted(neighbours, key=lambda pair: pair[1], reverse=True)]

        # calculate
        #best_prob_found = best_prob[active]
        for n in neighbours:
            if best_prob[active]*prob[n] > best_prob[n]:
                best_prob[n] = best_prob[active]*prob[n]
                best_path[n] = active




        queue.extend(neighbours)
        #print (queue)
        #print (best_prob)

        #print (best_prob[~0])
    

    #print (best_path)

    return get_path_string(best_path, 0, len(prob)-1)






n = int(stdin.readline())
probabilities = [float(x) for x in stdin.readline().split()]
neighbour_matrix = []
for line in stdin:
    neighbour_row = [0] * n
    neighbours = [int(neighbour) for neighbour in line.split()]
    for neighbour in neighbours:
        neighbour_row[neighbour] = 1
    neighbour_matrix.append(neighbour_row)

#print_matrix(neighbour_matrix)
#print (probabilities)
print (best_path(neighbour_matrix, probabilities))