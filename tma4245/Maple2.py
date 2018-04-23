import random as r

N = 2000000

counter = 0
for _ in range(N):
    p1 = r.randint(2, 13)
    p2 = r.randint(2, 13)
    p3 = r.randint(2, 13)

    if p1 == p2 or p1 == p3 or p2 == p3:
        counter +=1


print(counter/N)

