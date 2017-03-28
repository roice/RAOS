# -*- coding: utf-8 -*-
import h5py
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

SIM_FREQ = 50
START_TIME = 10

fd = h5py.File('record.h5', 'r+')

wind = fd['robot1/wind'][SIM_FREQ*START_TIME:]
wind_est_incl = fd['robot1/wind_est_incl'][SIM_FREQ*START_TIME:]
wind_est_leso = fd['robot1/wind_est_leso'][SIM_FREQ*START_TIME:]

wind_vel = np.sqrt(wind[:,0]*wind[:,0] + wind[:,1]*wind[:,1], + wind[:,2]*wind[:,2])
wind_est_incl_vel = np.sqrt(wind_est_incl[:,0]*wind_est_incl[:,0] + wind_est_incl[:,1]*wind_est_incl[:,1])
wind_est_leso_vel = np.sqrt(wind_est_leso[:,0]*wind_est_leso[:,0] + wind_est_leso[:,1]*wind_est_leso[:,1])

# Chinese
zhfont = matplotlib.font_manager.FontProperties(fname='../scripts/simkai.ttf')

fig = plt.figure(figsize=(8,5))
ax = fig.add_subplot(111)
t = np.array(range(len(wind)))/float(SIM_FREQ);

ax.plot(t, wind_vel, color='r', label=u'风速');
ax.plot(t, wind_est_incl_vel, color='g', label=u'倾角测量法的风速估计值');
ax.plot(t, wind_est_leso_vel, color='b', label=u'风矢量观测器法的风速估计值');

ax.set_xlabel(u"时间 (s)", fontproperties=zhfont)
ax.set_ylabel(u'风速 (m/s)', fontproperties=zhfont)
ax.legend(loc='upper right', prop=zhfont)
ax.set_xlim([0, 60*8]) # 2 min
#ax.set_ylim([-0.1, 1.45])

plt.savefig('wind-est_hovering_varying_wind_estimation.pdf', format='pdf', bbox_inches="tight")

plt.show()
