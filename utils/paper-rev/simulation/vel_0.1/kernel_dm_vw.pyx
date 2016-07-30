import numpy as np
cimport numpy as np
cimport cython

cdef extern from "math.h":
    double sqrt(double)
    double pow(double, double)

cdef double PI = 3.14159265358979323846
ctypedef np.double_t dtype_t

def kernel(
        np.ndarray[dtype_t, ndim=1] x,
        np.ndarray[dtype_t, ndim=2] data,
        double radius):
    cdef double w, wr
    cdef int i
    cdef np.ndarray[dtype_t, ndim=1] p
    cdef np.ndarray[dtype_t, ndim=2] delta
    # calculate GDM kernel
    cdef np.ndarray[dtype_t, ndim=2] SIGMA, SIGMA_inv
    cdef double SIGMA_det
    SIGMA = np.array([[0.7, 0., 0.], [0., 0.107, 0.], [0., 0., 0.107]])
    SIGMA_det = np.linalg.det(SIGMA)
    SIGMA_inv = np.linalg.inv(SIGMA)
    w = 0
    wr = 0
    for i in range(data.shape[0]):
        p = data[i,0:3]
        delta = np.array([x - p])
        power = -np.dot(np.dot(delta, SIGMA_inv), delta.T)[0,0]
        w_t = 1.0/pow(8*pow(PI, 3)*SIGMA_det, 1./2.)*np.exp(power);
        w += w_t
        wr += w_t*data[i,3]
    return wr/w

def kernel_dm_vw(
        np.ndarray[dtype_t, ndim=2] X,
        np.ndarray[dtype_t, ndim=2] Y,
        double z,
        np.ndarray[dtype_t, ndim=2] data):
    cdef np.ndarray[dtype_t, ndim=2] C
    cdef int idx_x, idx_y

    C = np.zeros_like(X)
    for idx_x in range(C.shape[0]):
        for idx_y in range(C.shape[1]):
            C[idx_x, idx_y] = kernel(np.array([X[idx_x, idx_y], Y[idx_x, idx_y], z]), data, 0.5)
    return C
