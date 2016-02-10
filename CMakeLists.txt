cmake_minimum_required(VERSION 3.3)
project(OpenCLTemplate)

# Setting Variables to use later
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(LIB_PATHS $ENV{QTDIR} /usr/lib src/oclshared/lib/linux src/oclshared src/oclcommon/lib src/oclshared/lib)
set(SHARED_INCLUDES src/oclshared/inc)
set(COMMON_INCLUDES src/oclcommon/inc)
set(OPENCL_LIBRARIES OpenCL liboclUtil_x86_64.a libGLEW_x86_64.a libshrutil_x86_64.a)
set(SOURCE_INCLUDES src/oclsrc src/tdpsosrc)
set( CMAKE_PREFIX_PATH /home/research/mobaidul/Qt/5.5/gcc_64)

file(GLOB TDPSO_SOURCE
        "src/tdpsosrc/*.h"
        "src/tdpsosrc/*.cpp"
        "src/tdpsosrc/*.hpp"
        "src/tdpsosrc/*.ui"
        )

set(SOURCE_FILES    src/oclsrc/oclVectorAdd.cpp
                    src/oclsrc/VectorAdd.cl
                    src/oclsrc/MedianFilter.cl
                    src/tdpsosrc/mainview.h
                    )
# QT Import Testing
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC ON )
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5PrintSupport REQUIRED )
find_package( Qt5Xml REQUIRED )
# End of QT Testing

# Directories to look for libraries
link_directories(${LIB_PATHS})
# Directories to include when looking for .h/.cpp/.c files
include_directories(${SHARED_INCLUDES} ${SOURCE_INCLUDES} ${COMMON_INCLUDES} ${LIB_PATHS})
# Add executables to generate
add_executable(OpenCLTemplate ${SOURCE_FILES} ${TDPSO_SOURCE})

qt5_use_modules(OpenCLTemplate Xml PrintSupport Core Widgets Gui)
# Link the libraries to the executable
target_link_libraries (OpenCLTemplate ${OPENCL_LIBRARIES})