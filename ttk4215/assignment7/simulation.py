from scipy import signal
from scipy.integrate import RK45
import numpy as np
import matplotlib.pyplot as plt



# simulation parameters
t_stop = 20

# adaptive law parameters
lambda1, lambda2 = -2, -4
Gamma = np.array([[1,0],[0,1]], dtype=np.float)
gamma = 1.0


A_lambda = np.array([[lambda1+lambda2, -lambda1*lambda2], [1,0]], dtype=np.float)
B_lambda = np.transpose(np.array([1,0], dtype=np.float))

C_phi = np.array([[-lambda1-lambda2, lambda1*lambda2], [-1, 0]], dtype=np.float)
D_phi = np.array([-1, 0], dtype=np.float)
C_z = np.array([0, 1], dtype=np.float)
C_z1 = np.array([0, 1], dtype=np.float)


def y(t):
    return np.cos(t)

def u(t):
    return np.sin(t)


def func(t,states):
    '''
    states = [theta1, theta2, rho, x_phi, x_z, x_z1]
    '''
    # extract and name states
    theta = states[0:2]
    rho = states[2]
    x_phi = states[3:5]
    x_z = states[5:7]
    x_z1 = states[7:9]

    # get external signals
    y_meas = y(t)
    u_meas = u(t)

    # compute bilinear model signals
    z = np.dot(C_z, x_z)
    z1 = np.dot(C_z1, x_z1)
    phi = np.dot(C_phi, x_phi) + np.dot(D_phi, y_meas)
    xi = np.dot(theta, phi) + z1

    m_squared = 1 + np.dot(phi,phi)

    # estimation
    z_hat = np.dot(rho,xi)
    epsilon = (z - z_hat)/m_squared

    
    # update law and filter
    theta_dot = np.dot(np.dot(Gamma, epsilon), phi) 
    print(epsilon)
    rho_dot = gamma*np.dot(epsilon, xi)

    x_phi_dot = np.dot(A_lambda, x_phi) + np.dot(B_lambda,y_meas)
    x_z_dot = np.dot(A_lambda, x_z) + np.dot(B_lambda, y_meas)
    x_z1_dot = np.dot(A_lambda, x_z1) + np.dot(B_lambda, u_meas)


    # derivatives
    states_dot = np.zeros_like(states)
    states_dot[0:2] = theta_dot
    states_dot[2] = rho_dot
    states_dot[3:5] = x_phi_dot
    states_dot[5:7] = x_z_dot
    states_dot[7:9] = x_z1_dot
    return states_dot;

def extract(solver):
    return solver.t, solver.y[0], solver.y[1], solver.y[2]

y0 = np.zeros(9, dtype=np.float)

solver = RK45(func, 0, y0, t_stop)

ts, ms, betas, rhos = [], [], [], []
t, m, beta, rho = extract(solver)

ts.append(t)
ms.append(m)
betas.append(beta)
rhos.append(rho)
try:
    while solver.step() is None:
        t, m, beta, rho = extract(solver)
        ts.append(t)
        ms.append(m)
        betas.append(beta)
        rhos.append(rho)
except RuntimeError as e:
    print(e)

plt.plot(ts, ms)
plt.show()




