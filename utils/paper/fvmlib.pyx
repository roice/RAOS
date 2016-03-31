import numpy as np
cimport numpy as np
cimport cython

cdef extern from "math.h":
    double sqrt(double)
    double pow(double, double)

cdef double PI = 3.14159265358979323846
ctypedef np.float32_t dtype_t
# Biot-Savart
#  Input:
#    a: position vector of point A
#    b: position vector of point B
#    p: position vector of point P
def biot_savart(
        np.ndarray[dtype_t, ndim=1] a,
        np.ndarray[dtype_t, ndim=1] b,
        np.ndarray[dtype_t, ndim=1] p,
        double Gamma ):

    cdef np.ndarray[dtype_t, ndim=1] ab, ap, bp # vector AB, AP, BP
    cdef np.ndarray[dtype_t, ndim=1] e # unit vector indicating the induced vel direction
    cdef double h # perpendicular distance from P to AB
    cdef double cos_theta_1, cos_theta_2 # cos(theta_1), cos(theta_2)

    # check if P is overlapping with A or B
    if (isclose(a[0], b[0]) and isclose(a[1], b[1]) and isclose(a[2], b[2]))\
            or (isclose(a[0], p[0]) and isclose(a[1], p[1]) and isclose(a[2], p[2]))\
            or (isclose(p[0], b[0]) and isclose(p[1], b[1]) and isclose(p[2], b[2])):
        return 0. # P is overlapping with A or B
    # AP, BP and AB vector
    ap = p - a
    bp = p - b
    ab = b - a
    # cos(theta_1) and cos(theta_2)
    cos_theta_1 = np.dot(ap, ab)/(norm_vector(ab)*norm_vector(ap))
    cos_theta_2 = np.dot(-1.*ab, bp)/(norm_vector(ab)*norm_vector(bp))

    # h, perpendicular distance from P to AB
    h = norm_vector(ap) * sqrt(1 - cos_theta_1**2)
    # e, unit vector indicating the dir of induced velocity
    e = np.cross(ap, bp)
    e = e/norm_vector(e)
    # induced velocity of this segment
    return Gamma/(4*PI)*(h*h/sqrt(0.001**4+h**4))*(cos_theta_1+cos_theta_2)*e


# compare two decimals
cdef bint isclose(double a, double b, double rel_tol=1e-09, double abs_tol=0.0) except *:
    return abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)

# 2-norm of a vector
@cython.boundscheck(False)
@cython.wraparound(False)
cdef double norm_vector(np.ndarray[dtype_t, ndim=1] vector) except *:
    cdef double norm = 0.
    cdef Py_ssize_t i
    for i in range(vector.shape[0]):
        norm += vector[i]**2
    return sqrt(norm)
