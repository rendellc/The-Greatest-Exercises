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

        print(self.A.dot(self.x0))

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



