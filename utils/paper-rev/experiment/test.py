import h5py
import numpy as np
import matplotlib.pyplot as plt

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

fig = plt.figure(figsize=(12,10))
ax = fig.add_subplot(111)

ax.plot(rd_13_under_AOE)
ax.plot(pos_13_under_AOE)

plt.show()
