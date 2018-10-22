import matplotlib.pyplot as plt
import math

import StateSpace as ss

def sign(x):
    if x > 0: return 1
    elif x < 0: return -1
    else: return 0

def aPrioriFunction(theta):
    return sign(10-theta[0])+sign(theta[1]*(1-theta[1])) + sign(0.1 - theta[2])


if __name__ == '__main__':
    y0, t0, dt, t1 = [0,0], 0.0, 1, 50.0
    process = ss.MassSpringDamperSeries(m=0.1, d=0.2, k=0.5)

    msd = ss.LinearStateSpace([[0,1],[-1,-1]], [[0, 1]], [1, 0], [0, 0], [[5],[-1]])

    def controll_law(t):
        return 10*math.sin(0.2*t) + 8

    ys, us, ts = [], [], [t0]
    while ts[~0] < t1:
        u = 0
        msd.update(u,dt)
        ys.append(msd.measure(u))
        us.append(u)

        ts.append(ts[~0] + dt)
        #u = controll_law(t)
        #valid = process.update(u,dt)

        #if not valid:
        #    break

        #ys.append(process.measure(u))
        #us.append(u)

    del ts[~0]

    plt.plot(ts,ys)
    plt.legend(['control_position', 'mass_position'])
    plt.show()



    
