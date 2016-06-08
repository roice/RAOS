import numpy as np
import matplotlib.pyplot as plt

# MOX sensor model: low pass filter
#  d c(t)
# ------- = - alpha * c(t) + alpha * C(x_s(t))
#   d t
#          c(t) if c(t) > tau
#  y(t) =
#          0 otherwise
class Sensor_MOX:
    def __init__(self):
        self.c_t = 0.; # c(t)
        self.y_t = 0.; # y(t)
        self.alpha = 0.5;
        self.tau = 0.;
    # use 1-order forward difference
    # c(t+delta_t) = (1-alpha) * c(t) + alpha * C(x_s(t))
    # input argument:
    #  conc: instantaneous concentration
    def update(self, conc):
        c_next = (1-self.alpha) * self.c_t + self.alpha * conc;
        self.c_t = c_next
        if self.c_t > self.tau:
            self.y_t = self.c_t
        else:
            self.y_t = 0.

# step function
def step(t):
    if t >= 0:
        return 1.
    else:
        return 0.
# step pulse
def step_pulse(t):
    if t >= 0 and t <= 4:
        return 1.
    else:
        return 0.

# time
t = np.arange(-2, 10, 0.1) # -2~10 s, 0.1 s step
# actual concentration, stimulate
C = np.zeros_like(t)
# sensor response
R = np.zeros_like(t)
# simulate sensor response
sensor = Sensor_MOX()
for i in range(t.size):
    #C[i] = step(t[i]) # step concentration
    C[i] = step_pulse(t[i]) # step pulse concentration
    sensor.update(C[i]) # sensor resp update
    R[i] = sensor.y_t

# draw
fig = plt.figure()
ax = fig.add_subplot(1,1,1)
#with plt.style.context('fivethirtyeight'):
ax.plot(t, C)
ax.plot(t, R)
ax.set_ylim(0, 1.2)
plt.show()
