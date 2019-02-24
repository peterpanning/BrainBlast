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

#find_package(OpenGL REQUIRED)

# TODO
# https://stackoverflow.com/questions/9460242/how-to-compile-glut-opengl-project-with-cmake-and-kdevelop-in-linux Should we be using 
# include_directories for all of these? 
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(finalProject main.cpp dicomSeries.cpp vtkDicomRenderer.cpp itkToVtkBridge.cpp)

# CMake apparently uses its own internal names for libraries in this command, according to 
# https://github.com/IngwiePhoenix/FLTK/blob/master/README.CMake.txt

target_link_libraries (finalProject ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OPENGL_LIBRARIES})
