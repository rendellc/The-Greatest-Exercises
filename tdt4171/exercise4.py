import matplotlib.pyplot as plt
import numpy as np
import numpy.matlib 
import random
import time
import csv
import os
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

def load_data(filename, x_dim, y_dim, augment):
    data = []
    with open(filename, 'r') as csvfile:
        linereader = csv.reader(csvfile, delimiter='\t')
        for line in linereader:
            data.append(list(map(float, line)))

    N = len(data)
    data = np.array(data)

    x = data[:,:x_dim]
    y = data[:,x_dim:(x_dim + y_dim)]

    if augment:
        ones = np.matlib.repmat(1,N,1)
        x = np.hstack((ones, x))

    return x, y

def sigmoid(w, x):
    return 1.0/(1.0 + np.exp(-np.dot(w,x)))


def loss_simple(w):
    return (sigmoid(w, np.array([1,0])) - 1)**2 + \
            sigmoid(w, np.array([0,1]))**2 + \
            (sigmoid(w, np.array([1,1])) - 1)**2 

def classify(w, x):
    if sigmoid(w,x) <= 0.5:
        return 0
    else:
        return 1

def loss_n(w,x,y):
    return 0.5*(sigmoid(w,x) - y)**2

def loss(w,D):
    x = D[0]
    y = D[1]
    N = len(y)

    return np.sum([loss_n(w,x[i],y[i]) for i in range(N)])

def loss_derivative_i(w,xn,yn,i):
    sig = sigmoid(w,xn)
    return (sig - yn)*xn[i]*np.exp(np.dot(-w,xn))*(sig**2)

def task1():
    fig = plt.figure()
    ax = fig.gca(projection='3d')

    # data
    w1 = np.arange(-6,6,0.1)
    w2 = np.arange(-6,6,0.1)
    w1, w2 = np.meshgrid(w1,w2)

    # calculate loss function
    w = np.stack([w1,w2], axis=2).reshape(-1,2)
    loss = loss_simple(w)
    loss = loss.reshape(w1.shape)

    # Plot the surface
    surf = ax.plot_surface(w1,w2,loss, rstride=5, cstride=5, cmap='viridis', edgecolor='none')
    ax.set_xlabel('w1')
    ax.set_ylabel('w2')
    ax.set_zlabel('loss function')

    # Gradient descent 
    def grad_loss_simple(w):
        s_w1 = sigmoid(w, np.array([1,0]))
        s_w2 = sigmoid(w, np.array([0,1]))
        s_wb = sigmoid(w, np.array([1,1]))

        partial_w1 = -2*s_w1*(s_w1 - 1)**2 - 2*s_wb*(s_wb - 1)**2
        partial_w2 = 2*s_w2**2 * (1-s_w2) - 2*s_wb*(s_wb - 1)**2

        return np.array([partial_w1, partial_w2])

    def get_next_step(w, etta):
        return w - etta*grad_loss_simple(w)

    iterations = 10000
    ettas = [0.0001, 0.01, 0.1, 1, 10, 100]
    dotcolors = ['r', 'g', 'b', 'y', 'o', 'c']
    dots = []
    for i, etta in enumerate(ettas):
        wk = np.array([0,0]) # start point
        for _ in range(iterations):
            wk = get_next_step(wk, etta)

        dots.append([wk[0], wk[1], loss_simple(wk)])


    labels = map(str, ettas)
    for i, dot in enumerate(dots):
        ax.plot([dot[0]], [dot[1]], [dot[2]], 'ro')
        ax.text(dot[0], dot[1], dot[2], labels[i], size=20)

    plt.show()

def evalTimeAndPrint(func, *args):
    start = time.time()
    retval = func(*args)
    elapsed = time.time() - start
    print("{0}: elapsed time: {1} secs".format(func.__name__, elapsed))
    
    return retval

def testClassificationData(w, x, y):
    prediction = []
    correct = 0
    y = y.flatten()
    for i, xn in enumerate(x):
        p = classify(w,xn) # prediction
        prediction.append(p)
        if p == y[i]:
            correct += 1

    total = len(x)
    return correct, total

def testClassificationFile(w, test_filename):
    x, y = load_data(test_filename, 2, 1, True)
    return testClassificationData(w,x,y)
    

def task2():
    data_dir = "ex4-data"
    rate_list = [0.01, 0.1, 1.0, 5.0, 10.0]
    iteration_list = [10, 20, 50, 100, 200, 500]

    data_sets = os.listdir(data_dir)
    iteration_max = max(iteration_list)



    # extract name of datasets
    training_sets = {}
    testing_sets = {}
    for filename in data_sets:
        index = filename.find('_test.csv')
        if index != -1:
            print("Found test set: {0}".format(filename))
            testing_sets[filename[:index]] = data_dir + "/" + filename
            continue
        index = filename.find('_train.csv')
        if index != -1:
            print("Found training set: {0}".format(filename))
            training_sets[filename[:index]] = data_dir + "/" + filename
            continue
        raise

    for rate in rate_list:
        print("-\nStart training on datasets for {0} iterations with learning rate {1}\n-".format(iteration_max, rate))
        # training results
        w_bgd_dict = {}
        w_sgd_dict = {}
        for name, filename in training_sets.items():
            x, y = load_data(filename, 2, 1, True)
            train_data = [x,y]
            w_bgd = evalTimeAndPrint(BatchGradientDescent, train_data, rate, iteration_max, iteration_list, name)
            print("\t->weights: {0}".format(w_bgd))
            w_sgd = evalTimeAndPrint(StochasticGradientDescent, train_data, rate, iteration_max, iteration_list, name)
            print("\t->weights: {0}".format(w_sgd))

            w_bgd_dict[name] = w_bgd
            w_sgd_dict[name] = w_sgd

        # testing
        
        print("-\nStart evaluating on datasets for {0} iterations with learning rate {1}".format(iteration_max, rate))
        for name, filename in testing_sets.items():
            w_bgd = w_bgd_dict[name]
            w_sgd = w_sgd_dict[name]
            print("\t{0}".format(name))
            print("\t\t{0}: Batch correctness: {1}".format(name, testClassificationFile(w_bgd,filename)))
            print("\t\t{0}: Stochastic correctness: {1}".format(name, testClassificationFile(w_sgd,filename)))



def BatchGradientDescent(training_data, rate, iteration_max, iteration_status_update, name):
    x = training_data[0]
    y = training_data[1]
    N = len(x) 
    d = len(x[0]) - 1 # x has dimension d+1
    w = np.random.rand(d+1)

    for t in range(iteration_max):
        for i in range(d+1):
            grad = numpy.zeros(d+1)
            for n in range(N):
                grad[i] += loss_derivative_i(w,x[n],y[n], i)
            w[i] -= 1.0/N*rate*grad[i]
        
        if t in iteration_status_update:
            correct, total = testClassificationData(w, x, y)
            error = float(total - correct)/float(total)
            print("Batch: {0}: rate {1}: iteration {2}: errors: {3}".format(name, rate, t, error))

    return w
                

def StochasticGradientDescent(training_data, rate, iteration_max, iteration_status_update, name):
    x = training_data[0]
    y = training_data[1]
    N = len(x) 
    d = len(x[0]) - 1 # x has dimension d+1
    w = np.random.rand(d+1)

    for t in range(iteration_max):
        chosen_index = random.randint(0,N-1)
        x_star = x[chosen_index]
        y_star = y[chosen_index]
        for i in range(d+1):
            grad = loss_derivative_i(w, x_star, y_star, i)
            w[i] -= rate*grad

        if t in iteration_status_update:
            correct, total = testClassificationData(w, x, y)
            error = float(total - correct)/float(total)
            print("Stochastic: {0}: rate {1}: iteration {2}: errors: {3}".format(name, rate, t, error))

    return w


def main():
    #task1()
    task2()


main()

