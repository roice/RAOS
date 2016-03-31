import h5py
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from mpl_toolkits.mplot3d import proj3d # for annotation in 3D

N_r = 4 # number of rotors
N_b = 2 # blades per rotor

# read data
file = h5py.File('quadrotor_vortices_plume.h5', 'r+')
vortices = []
for i in range(N_r*N_b):
    dataset = file['vortice_'+str(i)]
    vortices.append(dataset[...])
dataset = file['plume']
plume_affected = dataset[...]
file = h5py.File('quadrotor_original_plume.h5', 'r+')
dataset = file['plume']
plume_original = dataset[...]

xlim=[-1.2, 2.2]
ylim=[-0.6, 0.6]
zlim=[1.0, 2.2]

# truncate plumes according to axes lim
length = plume_affected.shape[0]
i = 0
while i != length:
    if plume_affected[i,0] > xlim[1]: # wind is along x-axis
        plume_affected = np.delete(plume_affected, i, 0)
        length -= 1
    else:
        i += 1
length = plume_original.shape[0]
i = 0
while i != length:
    if plume_original[i,0] > xlim[1]: # wind is along x-axis
        plume_original = np.delete(plume_original, i, 0)
        length -= 1
    else:
        i += 1

# draw vortices
fig = plt.figure(figsize=(16, 12), facecolor='w')
ax = fig.gca(projection='3d')
ax.view_init(elev=30, azim=-90)
for i in range(N_r*N_b):
    ax.plot(vortices[i][:,0], vortices[i][:,1], vortices[i][:,2], lw=1.1, color='grey', alpha=0.5)
ax.scatter(plume_original[:,0], plume_original[:,1], plume_original[:,2], s=1000*plume_original[:,3], marker='o', c='red', edgecolors='red', label='no aero-olfactory effect')
ax.scatter(plume_affected[:,0], plume_affected[:,1], plume_affected[:,2], s=1000*plume_affected[:,3], marker='o', c='green', edgecolors='green', label='under aero-olfactory effect')
ax.set_xlabel("\nX (m)",)
ax.set_ylabel('Y (m)')
ax.set_zlabel("Z (m)")
ax.set_yticks([-0.4, 0, 0.4])
ax.set_xlim(xlim)
ax.set_ylim(ylim)
ax.set_zlim(zlim)
ax.set_aspect('equal')

x, y, _ = proj3d.proj_transform(-1.0, 0, 2.2, ax.get_proj())
ax.annotate('gas source', xy=(x, y), xytext=(-0.045, 0.02), xycoords='data', arrowprops=dict(arrowstyle='->'))
lgnd = ax.legend(loc=(0.24, 0.15), fontsize=11, scatterpoints=1)
lgnd.legendHandles[0]._sizes = [30]
lgnd.legendHandles[1]._sizes = [30]



plt.savefig('quadrotor_plumes.pdf', format='pdf', bbox='tight')

plt.show()
