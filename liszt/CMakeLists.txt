CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )

# ------------------------------------------------------------------
# Project settings

PROJECT ( LISZT )
# SET ( LISZT_VERSION_MAJOR 1 )
# SET ( LISZT_VERSION_MINOR 0 )

# ------------------------------------------------------------------
# Libraries

LINK_DIRECTORIES ( /usr/lib )

# armadillo
FIND_PACKAGE ( Armadillo REQUIRED )
INCLUDE_DIRECTORIES ( ${ARMADILLO_INCLUDE_DIRS} )

# cuda
FIND_PACKAGE ( CUDA REQUIRED )
INCLUDE ( FindCUDA )
INCLUDE_DIRECTORIES ( ${CUDA_INCLUDE_DIRS} )

# ------------------------------------------------------------------
# Source settings

# configure a header file to pass some of the CMake settings to the source code
# CONFIGURE_FILE ()
FILE (COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# add the binary tree to the search path for include files
# so that we will find the header files
INCLUDE_DIRECTORIES (
    "${PROJECT_SOURCE_DIR}/core/model/"
    "${PROJECT_SOURCE_DIR}/core/nn/" 
    "${PROJECT_SOURCE_DIR}/core/ops/io/" 
    "${PROJECT_SOURCE_DIR}/examples/mnist/" 
)

# include all files
# FILE ( GLOB SOURCES
#    "${PROJECT_SOURCE_DIR}/core/model/*.h"
#    "${PROJECT_SOURCE_DIR}/core/model/*.cpp"
#    "${PROJECT_SOURCE_DIR}/core/model/*.cuh"
#    "${PROJECT_SOURCE_DIR}/core/model/*.cu"
#)

# ------------------------------------------------------------------
# Compile Settings

# c++
SET ( CMAKE_CXX_STANDARD 11 )

# nvcc
# SET ( CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=compute_20,code=sm_20 )
LIST ( APPEND CUDA_NVCC_FLAGS "-arch=sm_20;-std=c++11;-O2;-DVERBOSE" )

# ------------------------------------------------------------------
# Executable Settings

# add the executable
# mnist
ADD_EXECUTABLE ( MNIST examples/mnist/mnist.cpp )

# regression
# ADD_EXECUTABLE ( REG examples/regression/reg.cpp core/model/elm.cpp)
# TARGET_LINK_LIBRARIES( REG ${ARMADILLO_LIBRARIES} )
# regression: GPU
CUDA_ADD_EXECUTABLE ( REG examples/regression/reg.cpp core/model/elm.cpp core/model/elm.cu)
TARGET_LINK_LIBRARIES ( REG ${ARMADILLO_LIBRARIES} ${CUDA_LIBRARIES} )
