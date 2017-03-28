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

wind_dir = []
wind_dir_mask = []
for i in range(len(wind)):
    if (np.sqrt(wind[i,0]*wind[i,0]+wind[i,1]*wind[i,1]) < 0.001):
        mask = False
    else:
        mask = True
    ang = math.atan2(-wind[i,0], wind[i,1])
    wind_dir.append(ang)
    wind_dir_mask.append(mask)
wind_dir = np.asarray(wind_dir)
wind_dir_mask = np.asarray(wind_dir_mask)

np.set_printoptions(threshold='nan')


wind_est_incl_dir = []
wind_est_incl_dir_mask = []
for i in range(len(wind_est_incl)):
    if (np.sqrt(wind_est_incl[i,0]*wind_est_incl[i,0]+wind_est_incl[i,1]*wind_est_incl[i,1]) < 0.001):
        mask = False
    else:
        mask = True
    ang = math.atan2(-wind_est_incl[i,0], wind_est_incl[i,1])
    wind_est_incl_dir.append(ang)
    wind_est_incl_dir_mask.append(mask)
wind_est_incl_dir = np.asarray(wind_est_incl_dir)
wind_est_incl_dir_mask = np.asarray(wind_est_incl_dir_mask)

wind_est_leso_dir = []
wind_est_leso_dir_mask = []
for i in range(len(wind_est_leso)):
    if (np.sqrt(wind_est_leso[i,0]*wind_est_leso[i,0]+wind_est_leso[i,1]*wind_est_leso[i,1]) < 0.001):
        mask = False
    else:
        mask = True
    ang = math.atan2(-wind_est_leso[i,0], wind_est_leso[i,1])
    wind_est_leso_dir.append(ang)
    wind_est_leso_dir_mask.append(mask)
wind_est_leso_dir = np.asarray(wind_est_leso_dir)
wind_est_leso_dir_mask = np.asarray(wind_est_leso_dir_mask)

# Chinese
zhfont = matplotlib.font_manager.FontProperties(fname='../scripts/simkai.ttf', size=14)

fig = plt.figure(figsize=(8,5))
ax = fig.add_subplot(111)
t = np.array(range(len(wind)))/float(SIM_FREQ);

ax.plot(t[wind_dir_mask], wind_dir[wind_dir_mask]*180./np.pi, color='r', label=u'风向');
ax.plot(t[wind_est_incl_dir_mask], wind_est_incl_dir[wind_est_incl_dir_mask]*180./np.pi, color='g', label=u'倾角测量法的风向估计值');
ax.plot(t[wind_est_leso_dir_mask], wind_est_leso_dir[wind_est_leso_dir_mask]*180./np.pi, color='b', label=u'风矢量观测器法的风向估计值');

ax.set_xlabel(u"时间 (s)", fontproperties=zhfont)
ax.set_ylabel(u'风向 '+r'($^\circ$)', fontproperties=zhfont)
ax.legend(loc='upper left', prop=zhfont)
ax.set_xlim([0, 60*2]) # 2 min
ax.set_ylim([-96, -80.0])

plt.savefig('wind-est_hovering_varying_wind_dir.pdf', format='pdf', bbox_inches="tight")

plt.show()
