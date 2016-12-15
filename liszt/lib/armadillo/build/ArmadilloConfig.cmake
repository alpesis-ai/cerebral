# - Config file for the Armadillo package
# It defines the following variables
#  ARMADILLO_INCLUDE_DIRS - include directories for Armadillo
#  ARMADILLO_LIBRARY_DIRS - library directories for Armadillo (normally not used!)
#  ARMADILLO_LIBRARIES    - libraries to link against

# Tell the user project where to find our headers and libraries
set(ARMADILLO_INCLUDE_DIRS "/home/kelly/Studio/kelly/k/liszt/liszt/lib/armadillo;/home/kelly/Studio/kelly/k/liszt/liszt/lib/armadillo/build")
set(ARMADILLO_LIBRARY_DIRS "/home/kelly/Studio/kelly/k/liszt/liszt/lib/armadillo/build")

# Our library dependencies (contains definitions for IMPORTED targets)
include("/home/kelly/Studio/kelly/k/liszt/liszt/lib/armadillo/build/ArmadilloLibraryDepends.cmake")

# These are IMPORTED targets created by ArmadilloLibraryDepends.cmake
set(ARMADILLO_LIBRARIES armadillo)

