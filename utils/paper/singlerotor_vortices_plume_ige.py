import h5py
import numpy as np
import matplotlib.pyplot as plt

# read data
file = h5py.File('singlerotor_vortices_plume_ige.h5', 'r+')
dataset = file['vortice_0']
m_a = dataset[...]
dataset = file['vortice_1']
m_b = dataset[...]
dataset = file['plume']
plume_affected = dataset[...]
file = h5py.File('singlerotor_original_plume_ige.h5', 'r+')
dataset = file['plume']
plume_original = dataset[...]

# draw vortices
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(m_a[:,0], m_a[:,2], lw=1.1, color='grey', alpha=0.5)
ax.plot(m_b[:,0], m_b[:,2], lw=1.1, color='grey', alpha=0.5)
ax.scatter(plume_original[:,0], plume_original[:,2], 1000*plume_original[:,3], marker='o', c='red', edgecolors='red', label='no aero-olfactory effect')
ax.scatter(plume_affected[:,0], plume_affected[:,2], 1000*plume_affected[:,3], marker='o', c='green', edgecolors='green', label='under aero-olfactory effect')
ax.set_xlabel("X (m)")
ax.set_ylabel("Z (m)")
ax.set_xlim([-0.6, 1.2])
ax.set_ylim([-0.1, 0.6])
ax.set_aspect('equal')
ax.annotate('gas source', xy=(-0.5, 0.5), xytext=(-0.55, 0.35), xycoords='data', arrowprops=dict(arrowstyle='->'))
lgnd = ax.legend(loc='lower left', fontsize=11, scatterpoints=1)
lgnd.legendHandles[0]._sizes = [30]
lgnd.legendHandles[1]._sizes = [30]

plt.savefig('single_rotor_plumes_IGE.pdf', format='pdf', bbox_inches="tight")

plt.show()
