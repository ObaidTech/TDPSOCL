cmake_minimum_required(VERSION 3.3)
project(OpenCLTemplate)

# Setting Variables to use later
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(LIB_PATHS /usr/lib src/oclshared/lib/x64 src/oclshared/lib/linux src/oclshared src/oclcommon/lib src/oclshared/lib)
set(SHARED_INCLUDES src/oclshared/inc)
set(COMMON_INCLUDES src/oclcommon/inc)
set(OPENCL_LIBRARIES libOpenCL.so liboclUtil_x86_64.a libGLEW_x86_64.a libshrutil_x86_64.a)
set(SOURCE_INCLUDES src/oclsrc)
set(SOURCE_FILES    src/oclsrc/oclVectorAdd.cpp
                    src/oclsrc/VectorAdd.cl
                    src/oclsrc/MedianFilter.cl)

# Directories to look for libraries
link_directories(${LIB_PATHS})
# Directories to include when looking for .h/.cpp/.c files
include_directories(${SHARED_INCLUDES} ${SOURCE_INCLUDES} ${COMMON_INCLUDES} ${LIB_PATHS})
# Add executables to generate
add_executable(OpenCLTemplate ${SOURCE_FILES})
# Link the libraries to the executable
target_link_libraries (OpenCLTemplate ${OPENCL_LIBRARIES})