# Config file for the Build-tree cryptominisat Package
# It defines the following variables
#  CRYPTOMINISAT5_INCLUDE_DIRS - include directories for cryptominisat5
#  CRYPTOMINISAT5_LIBRARIES    - libraries to link against
#  CRYPTOMINISAT5_EXECUTABLE   - the cryptominisat executable

# Compute paths
get_filename_component(SCALMC_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(SCALMC_INCLUDE_DIRS "/root/approxmc/build/include")

# Our library dependencies (contains definitions for IMPORTED targets)
include("${CRYPTOMINISAT5_CMAKE_DIR}/")

# These are IMPORTED targets created by 
set(SCALMC_VERSION_MAJOR 3)
set(SCALMC_VERSION_MINOR 0)
set(SCALMC_EXECUTABLE scalmc)
