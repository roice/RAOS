from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy

ext_modules = [
        Extension("fvmlib", ["fvmlib.pyx"],
            include_dirs = [numpy.get_include(), '.'])
        ]

setup(
        name = 'Cython Implementation for Free Vortex Method',
        cmdclass = {'build_ext': build_ext},
        ext_modules = ext_modules
        )
