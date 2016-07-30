import h5py
import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage.filters import gaussian_filter

# read record
rd_13_no_AOE = h5py.File('Record_2016-07-08_15-47-10.h5', 'r+')['sensors_of_robot_0'][...]
rd_14_no_AOE = h5py.File('Record_2016-07-08_15-51-04.h5', 'r+')['sensors_of_robot_0'][...]
rd_15_no_AOE = h5py.File('Record_2016-07-08_15-54-44.h5', 'r+')['sensors_of_robot_0'][...]
rd_16_no_AOE = h5py.File('Record_2016-07-08_16-03-04.h5', 'r+')['sensors_of_robot_0'][...]
rd_17_no_AOE = h5py.File('Record_2016-07-08_16-10-39.h5', 'r+')['sensors_of_robot_0'][...]
rd_13_under_AOE = h5py.File('Record_2016-07-08_15-24-37.h5', 'r+')['sensors_of_robot_0'][...]
rd_14_under_AOE = h5py.File('Record_2016-07-08_15-27-30.h5', 'r+')['sensors_of_robot_0'][...]
rd_15_under_AOE = h5py.File('Record_2016-07-08_15-30-28.h5', 'r+')['sensors_of_robot_0'][...]
rd_16_under_AOE = h5py.File('Record_2016-07-08_15-32-12.h5', 'r+')['sensors_of_robot_0'][...]
rd_17_under_AOE = h5py.File('Record_2016-07-08_15-38-16.h5', 'r+')['sensors_of_robot_0'][...]
pos_13_no_AOE = h5py.File('Record_2016-07-08_15-47-10.h5', 'r+')['enu_of_robot_0'][...]
pos_14_no_AOE = h5py.File('Record_2016-07-08_15-51-04.h5', 'r+')['enu_of_robot_0'][...]
pos_15_no_AOE = h5py.File('Record_2016-07-08_15-54-44.h5', 'r+')['enu_of_robot_0'][...]
pos_16_no_AOE = h5py.File('Record_2016-07-08_16-03-04.h5', 'r+')['enu_of_robot_0'][...]
pos_17_no_AOE = h5py.File('Record_2016-07-08_16-10-39.h5', 'r+')['enu_of_robot_0'][...]
pos_13_under_AOE = h5py.File('Record_2016-07-08_15-24-37.h5', 'r+')['enu_of_robot_0'][...]
pos_14_under_AOE = h5py.File('Record_2016-07-08_15-27-30.h5', 'r+')['enu_of_robot_0'][...]
pos_15_under_AOE = h5py.File('Record_2016-07-08_15-30-28.h5', 'r+')['enu_of_robot_0'][...]
pos_16_under_AOE = h5py.File('Record_2016-07-08_15-32-12.h5', 'r+')['enu_of_robot_0'][...]
pos_17_under_AOE = h5py.File('Record_2016-07-08_15-38-16.h5', 'r+')['enu_of_robot_0'][...]

# get data
rd_13_no_AOE = 3.3 - rd_13_no_AOE[75:440, 0]
pos_13_no_AOE = - pos_13_no_AOE[75:440, 1] - 1.2
rd_14_no_AOE = 3.3 - rd_14_no_AOE[85:490, 0]
pos_14_no_AOE = - pos_14_no_AOE[85:490, 1] - 1.2
rd_15_no_AOE = 3.3 - rd_15_no_AOE[85:490, 0]
pos_15_no_AOE = - pos_15_no_AOE[85:490, 1] - 1.2
rd_16_no_AOE = 3.3 - rd_16_no_AOE[155:390, 0]
pos_16_no_AOE = - pos_16_no_AOE[155:390, 1] - 1.2
rd_17_no_AOE = 3.3 - rd_17_no_AOE[145:350, 0]
pos_17_no_AOE = - pos_17_no_AOE[145:350, 1] - 1.2
rd_13_under_AOE = 3.3 - rd_13_under_AOE[348:445, 0]
pos_13_under_AOE = - pos_13_under_AOE[348:445, 1] - 1.2
rd_14_under_AOE = 3.3 - rd_14_under_AOE[359:450, 0]
pos_14_under_AOE = - pos_14_under_AOE[359:450, 1] - 1.2
rd_15_under_AOE = 3.3 - rd_15_under_AOE[569:661, 0]
pos_15_under_AOE = - pos_15_under_AOE[569:661, 1] - 1.2
rd_16_under_AOE = 3.3 - rd_16_under_AOE[135:223, 0]
pos_16_under_AOE = - pos_16_under_AOE[135:223, 1] - 1.2
rd_17_under_AOE = 3.3 - rd_17_under_AOE[363:449, 0]
pos_17_under_AOE = - pos_17_under_AOE[363:449, 1] - 1.2

# smooth
rd_13_no_AOE = gaussian_filter(rd_13_no_AOE, sigma=10)
rd_14_no_AOE = gaussian_filter(rd_14_no_AOE, sigma=10)
rd_15_no_AOE = gaussian_filter(rd_15_no_AOE, sigma=10)
rd_16_no_AOE = gaussian_filter(rd_16_no_AOE, sigma=10)
rd_17_no_AOE = gaussian_filter(rd_17_no_AOE, sigma=10)
pos_13_no_AOE = gaussian_filter(pos_13_no_AOE, sigma=10)
pos_14_no_AOE = gaussian_filter(pos_14_no_AOE, sigma=10)
pos_15_no_AOE = gaussian_filter(pos_15_no_AOE, sigma=10)
pos_16_no_AOE = gaussian_filter(pos_16_no_AOE, sigma=10)
pos_17_no_AOE = gaussian_filter(pos_17_no_AOE, sigma=10)
rd_13_under_AOE = gaussian_filter(rd_13_under_AOE, sigma=10)
rd_14_under_AOE = gaussian_filter(rd_14_under_AOE, sigma=10)
rd_15_under_AOE = gaussian_filter(rd_15_under_AOE, sigma=10)
rd_16_under_AOE = gaussian_filter(rd_16_under_AOE, sigma=10)
rd_17_under_AOE = gaussian_filter(rd_17_under_AOE, sigma=10)
pos_13_under_AOE = gaussian_filter(pos_13_under_AOE, sigma=10)
pos_14_under_AOE = gaussian_filter(pos_14_under_AOE, sigma=10)
pos_15_under_AOE = gaussian_filter(pos_15_under_AOE, sigma=10)
pos_16_under_AOE = gaussian_filter(pos_16_under_AOE, sigma=10)
pos_17_under_AOE = gaussian_filter(pos_17_under_AOE, sigma=10)

# remove baseline
rd_13_no_AOE = rd_13_no_AOE - min(rd_13_no_AOE)
rd_14_no_AOE = rd_14_no_AOE - min(rd_14_no_AOE)
rd_15_no_AOE = rd_15_no_AOE - min(rd_15_no_AOE)
rd_16_no_AOE = rd_16_no_AOE - min(rd_16_no_AOE)
rd_17_no_AOE = rd_17_no_AOE - min(rd_17_no_AOE)
rd_13_under_AOE = rd_13_under_AOE - min(rd_13_under_AOE)
rd_14_under_AOE = rd_14_under_AOE - min(rd_14_under_AOE)
rd_15_under_AOE = rd_15_under_AOE - min(rd_15_under_AOE)
rd_16_under_AOE = rd_16_under_AOE - min(rd_16_under_AOE)
rd_17_under_AOE = rd_17_under_AOE - min(rd_17_under_AOE)

fig = plt.figure(figsize=(12,10))
ax = fig.add_subplot(111)

ax.plot(pos_13_under_AOE, rd_13_under_AOE, 'b-', label='-0.2 m, under AOE')
ax.plot(pos_14_under_AOE, rd_14_under_AOE, 'g-', label='-0.1 m, under AOE')
ax.plot(pos_15_under_AOE, rd_15_under_AOE, 'r-', label='0 m, under AOE')
ax.plot(pos_16_under_AOE, rd_16_under_AOE, 'y-', label='0.1 m, under AOE')
ax.plot(pos_17_under_AOE, rd_17_under_AOE, 'k-', label='0.2 m, under AOE')
ax.plot(pos_13_no_AOE, rd_13_no_AOE, 'b--', label='-0.2 m, no AOE')
ax.plot(pos_14_no_AOE, rd_14_no_AOE, 'g--', label='-0.1 m, no AOE')
ax.plot(pos_15_no_AOE, rd_15_no_AOE, 'r--', label='0 m, no AOE')
ax.plot(pos_16_no_AOE, rd_16_no_AOE, 'y--', label='0.1 m, no AOE')
ax.plot(pos_17_no_AOE, rd_17_no_AOE, 'k--', label='0.2 m, no AOE')

ax.set_xlabel("Y component of position (m)")
ax.set_ylabel("Smoothed and shifted reading (V)")
ax.legend()

plt.savefig('experiment_smoothed_readings.pdf', format='pdf', bbox_inches="tight")

plt.show()
