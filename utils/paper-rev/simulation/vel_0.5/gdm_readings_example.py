import h5py
import numpy as np
import matplotlib.pyplot as plt

# remove still points at the beginning
def data_pre_process(data):
    for i in range(data.shape[0]):
        if data[i,1] != data[i+1,1]:
            data = np.delete(data, range(i), 0)
            break
    data = data[0:6540, :]
    return data

# read data
rd_22 = h5py.File('quadrotor_gdm_22.h5', 'r+')['gdm'][...]

# pre-process
rd_22 = data_pre_process(rd_22)

# process, normalize
rd_22[:,3] = rd_22[:,3] * 2.355;

# draw
fig = plt.figure()
ax = fig.add_subplot(111)
t = np.array(range(rd_22.shape[0]))/60.0
ax.plot(t, rd_22[:,3], c='k')
ax.set_xlabel("Time (s)")
ax.set_ylabel(r"Concentration ($10^{12}$ $\frac{molecules}{cm^3}$)")

plt.savefig('gdm_readings_example.pdf', format='pdf', bbox_inches="tight")

print len(t)

plt.show()
