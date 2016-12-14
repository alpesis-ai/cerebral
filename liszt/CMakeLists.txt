CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )

# ------------------------------------------------------------------
# Project settings

PROJECT ( LISZT )
# SET ( LISZT_VERSION_MAJOR 1 )
# SET ( LISZT_VERSION_MINOR 0 )

# ------------------------------------------------------------------
# Compile settings

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

# add the executable
ADD_EXECUTABLE ( MNIST examples/mnist/mnist.cpp )
