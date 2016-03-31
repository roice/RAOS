import h5py
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

N_r = 4 # number of rotors
N_b = 2 # blades per rotor

# read data
file = h5py.File('quadrotor_markers.h5', 'r+')
vortices = []
for i in range(N_r*N_b):
    dataset = file['vortice_'+str(i)]
    vortices.append(dataset[...])

# get the xyz lim of filaments

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
#ax.set_xlim(-0.45, 0.45)
#ax.set_ylim(-0.45, 0.45)
#ax.set_zlim(1.3, 2.0)

# perspective
for i in range(4, 6):
    ax.plot(vortices[i][:, 0], vortices[i][:, 1], vortices[i][:, 2], lw=1.5, alpha = 0.7)
for i in range(2, 4):
    ax.plot(vortices[i][:, 0], vortices[i][:, 1], vortices[i][:, 2], lw=1.5, alpha = 0.7)
for i in range(0, 2):
    ax.plot(vortices[i][:, 0], vortices[i][:, 1], vortices[i][:, 2], lw=1.5, alpha = 0.7)
for i in range(6, 8):
    ax.plot(vortices[i][:, 0], vortices[i][:, 1], vortices[i][:, 2], lw=1.5, alpha = 0.7)

ax.view_init(elev=60., azim=-90+30)

plt.savefig('quad_rotor_vortices.pdf', format='pdf', bbox_inches="tight")

plt.show()
