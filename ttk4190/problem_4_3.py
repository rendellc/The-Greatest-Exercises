import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import numpy as np

A_44_points = np.array([ 
    [0.0, 1.1e10],
    [0.1, 1.11e10],
    [0.3, 1.12e10],
    [0.4, 1.13e10],
    [0.6, 1.15e10],
    [0.7, 1.18e10],
    [0.9, 1.02e10],
    [1.05, 0.922e10],
    [1.07, 0.925e10],
    [1.1, 0.930e10],
    [1.3, 0.935e10],
    [1.5, 0.938e10],
    [1.8, 0.94e10],
    [2.0, 0.942e10],
    [2.5, 0.945e10],
    [3.1, 0.95e10],
    [10.0, 0.96e10]], 
    dtype=np.float)
x = A_44_points[:,0]
y = A_44_points[:,1]

A_44 = interp1d(x,y)


def newton_rhapsody(x_n, func, func_derivative):
    return x_n - func(x_n)/func_derivative(x_n)


if __name__ == "__main__":
    rho = 1025.0
    g = 9.81
    B = 46.0
    T = 10.0
    Lpp = 246.0
    R_44 = 17.1
    m = rho*B*Lpp*T
    W = m*g
    GM_bar_T = B**2/(12*T) - T
    I_x = m*R_44**2

    C = W*GM_bar_T
    M = I_x
    def func(x): return x - np.sqrt(C/(M + A_44(x)))
    def func_derivative(x): return 1 + A_44(x)/(2*(M + A_44(x))) * np.sqrt(C/(M + A_44(x)))

    x_0 = 0.0
    x_n = x_0
    for _ in range(100):
        x_n = newton_rhapsody(x_n, func, func_derivative)
    
    print("w_roll =", x_n)
    print("A_44(w_roll) =", A_44(x_n))
    

