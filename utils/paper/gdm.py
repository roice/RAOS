import h5py
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

# calculate GDM kernel
SIGMA = np.array([[0.7, 0., 0.], [0., 0.107, 0.], [0., 0., 0.107]])
SIGMA_det = np.linalg.det(SIGMA)
SIGMA_inv = np.linalg.inv(SIGMA)
def kernel_dm(x, data, radius):
    w = 0
    wr = 0
    for i in range(data.shape[0]):
        p = data[i,0:3]
        delta = np.array([x - p])
        power = -np.dot(np.dot(delta, SIGMA_inv), delta.T)[0,0]
        w_t = 1.0/np.power(8*np.power(np.pi, 3)*SIGMA_det, 1./2.)*np.exp(power);
        w += w_t
        wr += w_t*data[i,3]
    return wr/w

# Gas Distribution Mapping
def gdm(X, Y, z, data):
    C = np.zeros_like(X)
    for idx_x in range(C.shape[0]):
        for idx_y in range(C.shape[1]):
            C[idx_x, idx_y] = kernel_dm(np.array([X[idx_x, idx_y], Y[idx_x, idx_y], z]), data, 0.5)
    return C

# remove useless points
def data_pre_process(data):
    out = np.array([[0,0,0,0]]);
    for i in range(data.shape[0]):
        if data[i,3] > 0.1:
            out = np.append(out, [data[i,:]], axis=0)
    return out

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

# figure settings
fig, axes = plt.subplots(nrows=3, ncols=2, figsize=(8, 12))

for ax in axes[:,0]:
    ax.set_ylabel("Y (m)")
for ax in axes[2,:]:
    ax.set_xlabel("X (m)")
for ax in axes.reshape(1,-1)[0]:
    ax.set_aspect('equal')
    ax.set_xlim([-5, 5])
    ax.set_ylim([-5, 5])
for ax in (axes[0:2, :]).reshape(1,-1)[0]:
    plt.setp( ax.get_xticklabels(), visible=False)
for ax in (axes[:, 1:3]).reshape(1,-1)[0]:
    plt.setp( ax.get_yticklabels(), visible=False)


# mapping

delta = 0.05 # m
x = y = np.arange(-5.0, 5.0, delta)
X, Y = np.meshgrid(x, y)

C_18_n = gdm(X, Y, 1.8, rd_18_n)
C_22_n = gdm(X, Y, 2.2, rd_22_n)
C_26_n = gdm(X, Y, 2.6, rd_26_n)
C_18 = gdm(X, Y, 1.8, rd_18)
C_22 = gdm(X, Y, 2.2, rd_22)
C_26 = gdm(X, Y, 2.6, rd_26)
map_vmin = 0
map_vmax = abs(C_22_n).max()

# draw
axes[0,0].imshow(C_26, interpolation='bilinear', cmap=cm.Greens,
                origin='lower', extent=[-5, 5, -5, 5], vmin=map_vmin, vmax=map_vmax)
axes[0,1].imshow(C_26_n, interpolation='bilinear', cmap=cm.Greens,
                origin='lower', extent=[-5, 5, -5, 5], vmin=map_vmin, vmax=map_vmax)
axes[1,0].imshow(C_22, interpolation='bilinear', cmap=cm.Greens,
                origin='lower', extent=[-5, 5, -5, 5], vmin=map_vmin, vmax=map_vmax)
axes[1,1].imshow(C_22_n, interpolation='bilinear', cmap=cm.Greens,
                origin='lower', extent=[-5, 5, -5, 5], vmin=map_vmin, vmax=map_vmax)
axes[2,0].imshow(C_18, interpolation='bilinear', cmap=cm.Greens,
                origin='lower', extent=[-5, 5, -5, 5], vmin=map_vmin, vmax=map_vmax)
axes[2,1].imshow(C_18_n, interpolation='bilinear', cmap=cm.Greens,
                origin='lower', extent=[-5, 5, -5, 5], vmin=map_vmin, vmax=map_vmax)

height = [ 2.6, 2.2, 1.8 ]
c_max = [ [ abs(C_26).max(), abs(C_26_n).max() ],\
          [ abs(C_22).max(), abs(C_22_n).max() ],\
          [ abs(C_18).max(), abs(C_18_n).max() ]]

for i in range(3):
    for j in range(2):
        if j == 0:
            axes[i,j].set_title('height: '+str(height[i])+' m'+', under AOE')
        else:
            axes[i,j].set_title('height: '+str(height[i])+' m'+', no AOE')
        axes[i,j].text(-4.5, 4.0, r'max: '+'{:.1f}'.format(c_max[i][j])+r'$\times10^{12}$ $\frac{molecules}{cm^3}$')
plt.subplots_adjust(wspace=0.3, hspace=0.3)
plt.tight_layout()
# save

plt.savefig('quadrotor_gdm_maps.pdf', format='pdf', bbox_inches="tight")

# show

plt.show()
