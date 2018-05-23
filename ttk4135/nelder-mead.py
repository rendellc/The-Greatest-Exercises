import numpy as np

def compose(f1, f2):
    return lambda t: f1(f2(t))

def update(func, xs):
    n = xs.shape[1]
    x_centroid = sum(xs[:~0])/(n+1)
    x_bar = lambda t: x_centroid + t*(xs[~0] - x_centroid)
    f_reflect = compose(func, x_bar)

    fs = list(map(func, xs)) # shouldnt need to evaluate all, implement lazy evaluation

    outside_contract = f_reflect(-1.0/2.0)
    inside_contract = f_reflect(-1.0/2.0)

    f_reflect_one = f_reflect(-1.0)
    insert_x = None
    if fs[0] <= f_reflect_one and f_reflect_one < fs[~1]:
        insert_x = x_bar(-1)
    elif f_reflect_one < fs[0]:
        f_reflect_two = f_reflect(-2.0)
        if f_reflect_two < f_reflect_two:
            insert_x = x_bar(-2)
        else:
            insert_x =  x_bar(-1)
    else:
        if fs[~1] <= f_reflect_one < fs[~0]:
            f_reflect_onehalf = f_reflect(-0.5)
            if f_reflect_onehalf < f_reflect_one:
                insert_x = x_bar(-0.5)
        else:
            f_reflect_onehalf = f_reflect(0.5)
            if f_reflect_onehalf < fs[~0]:
                insert_x = x_bar(0.5)
        
    if insert_x is None:
        for i in range(1,n+1):
            xs[i] = 0.5*(xs[0] + xs[i])
    else:
        xs[~0] = insert_x

    return xs



if __name__ == "__main__":
    print("Main")
    func = lambda x: x[0]**2 + (x[1] + 20)**2 + x[2]**2 + x[3]**2

    np.random.seed()
    xs = 10*np.random.random((5,4))

    iterations = 1
    while True:
        xs = sorted(xs, key=func)
        xs = np.array(xs)
        update(func, xs)

        if abs(func(xs[0]) - func(xs[~0])) < 0.001:
            break
        else:
            iterations += 1
            print("dbg:", func(xs[0]), func(xs[~0]))
            pass
    print("Iterations:", iterations)
    print("Solution:", xs[0])

