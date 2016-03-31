import h5py
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
import math
import fvmlib

# read data
file = h5py.File('singlerotor_markers.h5', 'r+')
dataset = file['vortice_0']
m_a = dataset[...]
dataset = file['vortice_1']
m_b = dataset[...]

# get the xyz lim of filaments
lim_x = [-0.2, 0.2]
lim_y = [-0.2, 0.2]
lim_z = [1.4, 2.2]

lim_d = 0.005

fig = plt.figure(figsize=(6, 9))
ax0 = fig.add_subplot(211)
ax1 = fig.add_subplot(212, sharex=ax0)

# get xz plane streamlines
y, x = np.mgrid[lim_z[0]:lim_z[1]:lim_d, lim_x[0]:lim_x[1]:lim_d]
u = np.zeros_like(x)
v = np.zeros_like(y)
for i in range(x.shape[0]):
    for j in range(x.shape[1]):
        p = np.array([x[i,j], 0., y[i,j]], dtype = np.float32)
        ind_v = np.zeros(3)
        for k in range(m_a.shape[0]-1):
            a = m_a[k]
            b = m_a[k+1]
            ind_v += fvmlib.biot_savart(a,b,p,-1.0535)
        for k in range(m_b.shape[0]-1):
            a = m_b[k]
            b = m_b[k+1]
            ind_v += fvmlib.biot_savart(a,b,p,-1.0535)
        u[i,j] = ind_v[0]
        v[i,j] = ind_v[2]
ax0.streamplot(x,y,u,v, color='black')
ax0.set_xlim(lim_x[0], lim_x[1])
ax0.set_ylim(lim_z[0], lim_z[1])
#ax0.set_xlabel("X (m)")
ax0.set_ylabel("Z (m)")
[label.set_visible(False) for label in ax0.get_xticklabels()]
ax0.text(0, 2.0, "                                    rotor                                    ", color = 'k', size=10, rotation=0,
        ha="center", va="center",
        bbox=dict(boxstyle="square", ec="0.5", fc="w", alpha=0.9))


plt.draw()

# get xy plane streamlines
y, x = np.mgrid[lim_y[0]:lim_y[1]:lim_d, lim_x[0]:lim_x[1]:lim_d]
u = np.zeros_like(x)
v = np.zeros_like(y)
for i in range(x.shape[0]):
    for j in range(x.shape[1]):
        p = np.array([x[i,j], y[i,j], 2.05], dtype = np.float32)
        ind_v = np.zeros(3)
        for k in range(m_a.shape[0]-1):
            a = m_a[k]
            b = m_a[k+1]
            ind_v += fvmlib.biot_savart(a,b,p,-1.0535)
        for k in range(m_b.shape[0]-1):
            a = m_b[k]
            b = m_b[k+1]
            ind_v += fvmlib.biot_savart(a,b,p,-1.0535)
        u[i,j] = ind_v[0]
        v[i,j] = ind_v[1]
ax1.streamplot(x,y,u,v, color='black')
ax1.set_xlim(lim_x[0], lim_x[1])
ax1.set_ylim(lim_y[0], lim_y[1])
ax1.set_xlabel("X (m)")
ax1.set_ylabel("Y (m)")
ax1.set_aspect('equal')
# draw rotor
theta = np.linspace(0, 2*np.pi, 1000)
ax1.plot(0.1*np.cos(theta), 0.1*np.sin(theta), lw=1.5, color='grey', ls='--', label="rotor tip locus")
ax1.legend()

plt.tight_layout()
plt.subplots_adjust(hspace = 0.03)

plt.savefig('single_rotor_streamlines.pdf', format='pdf', bbox_inches="tight")

plt.show()
