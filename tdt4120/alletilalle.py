from sys import stdin, maxsize, stdout

import cProfile, pstats

pr = cProfile.Profile()
inf = 10000
pr.enable()
def FloydWarshall(adjacency_matrix, n):
    
    #n = len(adjacency_matrix)

    #D = adjacency_matrix

    for k in range(n):
        for row in range(n):
            for col in range(n):
                if adjacency_matrix[row][col] > adjacency_matrix[row][k] + adjacency_matrix[k][col]:
                    adjacency_matrix[row][col] = adjacency_matrix[row][k] + adjacency_matrix[k][col]
    
    return adjacency_matrix


def shortest_path(order_list, distance_matrix):
    cost = 0
    current_city = order_list[0]
    order_list.append(order_list[0])
    for next_city in order_list:
        if distance_matrix[current_city][next_city] >= inf:
            return 'umulig'
        
        cost += distance_matrix[current_city][next_city]
        current_city = next_city

    return cost    


def main():
    testcases = int(stdin.readline())
    for test in range(testcases):
        cities = int(stdin.readline())
        order_list = [int(city) for city in stdin.readline().split()]
        
        # create adjecency matrix

        adjacency_matrix = [[int(city) for city in stdin.readline().split()] for city in range(cities)]

        for i in range(cities):
            for j in range(cities):
                if adjacency_matrix[i][j] == -1:
                    adjacency_matrix[i][j] = inf

        print(shortest_path(order_list, FloydWarshall(adjacency_matrix, cities)))


main()

pr.disable()
sortby = 'cumulative'
ps = pstats.Stats(pr, stream=stdout).sort_stats(sortby)
ps.print_stats()



