cmake_minimum_required(VERSION 2.8)

project(finalProject)

find_package(ITK REQUIRED)
if(ITK_FOUND)
    INCLUDE(${ITK_USE_FILE})
endif(ITK_FOUND)

find_package(VTK REQUIRED)
if(VTK_FOUND)
    include(${VTK_USE_FILE})
endif(VTK_FOUND)

# The FLTK CMake guide recommends running this with NO_MODULE, but doing so causes problems
# when running CMake. So, I dunno, man. 

find_package(FLTK REQUIRED)

# If find_package can't find FLTK, setting the path to it may fix that. 
# The path to fltk is wherever the FLTKConfig.cmake file is. 

if(NOT FLTK_FOUND)
    set(FLTK_DIR /usr/local/opt/fltk)
    find_package(FLTK REQUIRED)
endif(NOT FLTK_FOUND)

# Apparently the include statement here is deprecated, according to CMake (not according to the
# FLTK CMake guide, though)
# include(${FLTK_USE_FILE})

find_package(OpenGL REQUIRED)

# TODO
# https://stackoverflow.com/questions/9460242/how-to-compile-glut-opengl-project-with-cmake-and-kdevelop-in-linux Should we be using 
# include_directories for all of these? 
include_directories(${FLTK_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

add_executable(finalProject main.cpp dicomSeries.cpp vtkExample.cpp vtkDicomRenderer.cpp)

# CMake apparently uses its own internal names for libraries in this command, according to 
# https://github.com/IngwiePhoenix/FLTK/blob/master/README.CMake.txt

target_link_libraries (finalProject ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OPENGL_LIBRARIES} fltk)
