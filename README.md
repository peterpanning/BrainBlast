A small application to view DICOM image scans in 3D, written using C++.

This is my semester project for CSC 621 at San Francisco State University


Installing the necessary tools:

I found these guides and posts to be helpful and up to date as of April '18: 

[Basic installation guide for macOS](http://itkdebug.blogspot.com/2013/02/install-itk-on-mac-os.html)
 
[A particularly troublesome bug with ITK, solved on the forums](https://discourse.itk.org/t/visibility-settings/596) 


[FLTK guide to CMake](https://github.com/IngwiePhoenix/FLTK/blob/master/README.CMake.txt)

[On including OpenGL and GLUT, necessary for FLTK](https://stackoverflow.com/questions/9460242/how-to-compile-glut-opengl-project-with-cmake-and-kdevelop-in-linux)

[Hello World for ITK compilation](https://itk.org/Wiki/ITK/HelloInsight)

[Fully compilable VTK Examples in C++](https://lorensen.github.io/VTKExamples/site/Cxx/)

[Hello World for FLTK](http://www.fltk.org/doc-1.3/basics.html#basics_writing)

[Rendering a Volume from a Dicom file with VTK](https://github.com/fblupi/rendering-volume-from-dicom-vtk/blob/master/RenderingVolumeFromDICOM.cpp)

Many pages on the ITK wiki lead to dead links, incomplete examples, and/or out of date information. The links I provided above were helpful and accurate for me on macOS in April '18. 


Remember to run `make` followed by `make install` to
install binaries locally. 


**Project Structure:**


The project has all of the relevant .cpp and CMakeLists.txt files within a directory managed under git version control, 
with a separate build directory directory **outside of version control** which contains the executables, header files of the libraries to be included,
and files generated during the build process. 

