##===============================================================
# This file aims to obtain the dependencies this project requries
# Note: This file needs to be executed with ROOT previlege
#
# Author: Roice (LUO Bing)
# Date:   2014-11-25 Create this file

#!/bin/sh

# obtaining the dependencies OCTAVE require
# for Debian based LINUX dist
apt-get build-dep octave
# for Redhat based LINUX dist, yum-builddep is part of the yum-utils package
#yum-builddep octave
