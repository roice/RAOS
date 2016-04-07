import h5py
import numpy as np
import matplotlib.pyplot as plt

# remove still points at the beginning
def data_pre_process(data):
    for i in range(data.shape[0]):
        if data[i,1] != data[i+1,1]:
            data = np.delete(data, range(i), 0)
            break
    data = data[0:6540,:]
    return data

# read data
rd_18 = h5py.File('quadrotor_gdm_18.h5', 'r+')['gdm'][...]
rd_20 = h5py.File('quadrotor_gdm_20.h5', 'r+')['gdm'][...]
rd_22 = h5py.File('quadrotor_gdm_22.h5', 'r+')['gdm'][...]
rd_24 = h5py.File('quadrotor_gdm_24.h5', 'r+')['gdm'][...]
rd_26 = h5py.File('quadrotor_gdm_26.h5', 'r+')['gdm'][...]
rd_18_n = h5py.File('quadrotor_gdm_18_no_AOE.h5', 'r+')['gdm'][...]
rd_20_n = h5py.File('quadrotor_gdm_20_no_AOE.h5', 'r+')['gdm'][...]
rd_22_n = h5py.File('quadrotor_gdm_22_no_AOE.h5', 'r+')['gdm'][...]
rd_24_n = h5py.File('quadrotor_gdm_24_no_AOE.h5', 'r+')['gdm'][...]
rd_26_n = h5py.File('quadrotor_gdm_26_no_AOE.h5', 'r+')['gdm'][...]


# pre-process
rd_18 = data_pre_process(rd_18)
rd_20 = data_pre_process(rd_20)
rd_22 = data_pre_process(rd_22)
rd_24 = data_pre_process(rd_24)
rd_26 = data_pre_process(rd_26)
rd_18_n = data_pre_process(rd_18_n)
rd_20_n = data_pre_process(rd_20_n)
rd_22_n = data_pre_process(rd_22_n)
rd_24_n = data_pre_process(rd_24_n)
rd_26_n = data_pre_process(rd_26_n)

# process
rd_18[:,3] = rd_18[:,3] * 2.355;
rd_20[:,3] = rd_20[:,3] * 2.355;
rd_22[:,3] = rd_22[:,3] * 2.355;
rd_24[:,3] = rd_24[:,3] * 2.355;
rd_26[:,3] = rd_26[:,3] * 2.355;
rd_18_n[:,3] = rd_18_n[:,3] * 2.355;
rd_20_n[:,3] = rd_20_n[:,3] * 2.355;
rd_22_n[:,3] = rd_22_n[:,3] * 2.355;
rd_24_n[:,3] = rd_24_n[:,3] * 2.355;
rd_26_n[:,3] = rd_26_n[:,3] * 2.355;

# draw
fig = plt.figure(figsize=(8,6))
ax = fig.add_subplot(111)
t = np.array(range(rd_18.shape[0]))/60.0
period = range(2130,2280)
ax.plot(t[period], rd_18[period, 3], 'b-', label='1.8 m, under AOE')
ax.plot(t[period], rd_20[period, 3], 'g-', label='2.0 m, under AOE')
ax.plot(t[period], rd_22[period, 3], 'r-', label='2.2 m, under AOE')
ax.plot(t[period], rd_24[period, 3], 'y-', label='2.4 m, under AOE')
ax.plot(t[period], rd_26[period, 3], 'k-', label='2.6 m, under AOE')
ax.plot(t[period], rd_18_n[period, 3], 'b--', label='1.8 m, no AOE')
ax.plot(t[period], rd_20_n[period, 3], 'g--', label='2.0 m, no AOE')
ax.plot(t[period], rd_22_n[period, 3], 'r--', label='2.2 m, no AOE')
ax.plot(t[period], rd_24_n[period, 3], 'y--', label='2.4 m, no AOE')
ax.plot(t[period], rd_26_n[period, 3], 'k--', label='2.6 m, no AOE')


ax.set_xlabel("Time (s)")
ax.set_ylabel(r"Concentration ($10^{12}$ $\frac{molecules}{cm^3}$)")
ax.legend()

plt.savefig('gdm_readings.pdf', format='pdf', bbox_inches="tight")

plt.show()
