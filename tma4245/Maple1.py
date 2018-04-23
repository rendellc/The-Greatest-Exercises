def avg(xs):
    return sum(xs)/len(xs)

def empVar(xs):
    var = 0
    mean = avg(xs)
    for x in xs:
        var += (x - mean)**2

    return 1/(len(xs)-1)*var

def stdDev(xs):
    return empVar(xs)**0.5

oppg2 = [1, 0.49, 0.44, 0.49, 0.39, 0.58]
print(empVar(oppg2))

oppg3 = [155, 180, 175, 159, 185, 189, 179]
print(stdDev(oppg3))

grades = [1,5,2,4,4,3,2,4,3]
grades.sort()
print(grades[len(grades)//2])
