import h5py
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

# calculate GDM kernel
SIGMA = np.array([[0.7, 0., 0.], [0., 0.107, 0.], [0., 0., 0.107]])
SIGMA_det = np.linalg.det(SIGMA)
SIGMA_inv = np.linalg.inv(SIGMA)
def kernel_dm(x, p, radius):
    delta = np.array([x - p])
    power = -np.dot(np.dot(delta, SIGMA_inv), delta.T)[0,0]
    c = 1.0/np.power(8*np.power(np.pi, 3)*SIGMA_det, 1./2.)*np.exp(power);
    return c

# read data
file = h5py.File('quadrotor_gdm_18.h5', 'r+')
dataset = file['plume']
plume = dataset[...]
dataset = file['gdm']
gdm = dataset[...]

# draw vortices
fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_xlabel("X (m)")
ax.set_ylabel("Y (m)")
ax.set_xlim([-5, 5])
ax.set_ylim([-5, 5])
ax.set_aspect('equal')
#ax.annotate('gas source', xy=(-0.5, 2.1), xytext=(-0.55, 1.95), xycoords='data', arrowprops=dict(arrowstyle='->'))
#lgnd = ax.legend(loc='lower left', fontsize=11, scatterpoints=1)
#lgnd.legendHandles[0]._sizes = [30]
#lgnd.legendHandles[1]._sizes = [30]

delta = 0.1 # m
x = y = np.arange(-5.0, 5.0, delta)
X, Y = np.meshgrid(x, y)
C = np.zeros_like(X)
# Gas Distribution Mapping
for i in range(gdm.shape[0]): # traverse every sample point
    for idx_x in range(C.shape[0]):
        for idx_y in range(C.shape[1]):
            C[idx_x, idx_y] += kernel_dm(np.array([X[idx_x, idx_y], Y[idx_x, idx_y], 1.8]), gdm[i,0:3], 0.5);

ax.imshow(C, interpolation='bilinear', cmap=cm.RdYlGn,
                origin='lower', extent=[-5, 5, -5, 5],
                vmax=abs(C).max(), vmin=-abs(C).max())

#plt.savefig('quadrotor_gdm.pdf', format='pdf', bbox_inches="tight")

plt.show()
