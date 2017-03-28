import h5py
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

fd = h5py.File('record.h5', 'r+')

c = fd['robot1/wind_est_leso'][...]

fig = plt.figure(figsize=(8,6))
ax = fig.add_subplot(111)

ax.plot(c[:,0], color='r') # cx
ax.plot(c[:,1], color='g') # cy
ax.plot(c[:,2], color='b') # cz

plt.show()
