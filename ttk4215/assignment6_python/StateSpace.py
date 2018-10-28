from scipy.integrate import ode
import numpy as np

class SimBase:
    def __init__(self, update_law, y0, t0):
        self.solver = ode(update_law).set_integrator('dopri5').set_initial_value(y0,t0)

    def update(self, u, dt):
        self.solver.set_f_params(u)
        self.solver.integrate(self.solver.t + dt)
        
        return self.solver.successful()

    def get_states(self):
        return self.solver.y

class LinearStateSpace(SimBase):
    def __init__(self, A,B,C,D, x0, t0=0):
        self.A = np.array(A, dtype=np.float)
        self.B = np.array(B, dtype=np.float)
        self.C = np.array(C, dtype=np.float)
        self.D = np.array(D, dtype=np.float)
        self.x0 = np.array(x0, dtype=np.float)

        def update_law(t, y, u):
            """
            x_dot = A x + B u
            """
            return self.A.dot(y) + self.B.dot(np.array(u))

        SimBase.__init__(self, update_law, self.x0, t0)

    def measure(self, u):
        """
        y = C x + D u
        """
        x = SimBase.get_states(self)
        return self.C.dot(x) + self.D.dot(u)


class MassSpringDamperParallel(LinearStateSpace):
    def __init__(self, m, d, k, pos0=0, vel0=0, t0=0):
        A = np.array([[0, 1], [-k/m, -d/m]], dtype=np.float)
        B = np.array([[0],[1]], dtype=np.float)
        C = np.eye(2, dtype=np.float)
        D = np.zeros([2,1], dtype=np.float)

        print(A)
        print(B)
        print(C)
        print(D)

        x0 = np.array([pos0,vel0], dtype=np.float).transpose()
        LinearStateSpace.__init__(self, A,B,C,D, x0, t0)

    def measure(self, u):
        y = LinearStateSpace.get_states(self)
        return y[0]



class MassSpringDamperSeries(SimBase):
    def __init__(self, m, d, k, pos0=0, vel0=0, t0=0):
        self.m, self.d, self.k = m, d, k

        def update_law(t, y, u):
            """
            x = [y2, y2_dot]
            y2_dot = y2_dot
            y2_ddot = -beta/m y2_dot + 1/m u

            y1 = 1/k u + y2
            """
            return [y[1], -m/d*y[1] + 1.0/m * u]

        SimBase.__init__(self, update_law, [pos0, vel0], t0)

    def measure(self, u):
        y = SimBase.get_states(self)
        return [1.0/self.k * u + y[1], y[1]]



