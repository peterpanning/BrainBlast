A small application to view DICOM image scans, written using C++. 

This is the semester project for CSC 621 at San Francisco State University, written by "Team Forest:" Flavy Tonfack, Amelia Rawling, Veronica Yuen, and Peter Mutch



**Installing the necessary tools:**

This project requires ITK, VTK, and FLTK. 

A quick word on the installation process:

Everyone in our group was using MacOS, and the guides provided by the instructor and TA applied only to the Windows platform. The guides that they provided links to
similarly only applied to Windows, and many of them were fraught with errors like: 

In CMakeLists.txt files, the examples indicated we should use `INCLUDE ($USE_ITK_FILE)`, which causes errors. The correct command, which was on the ITK wiki, is 
`INCLUDE ($ITK_USE_FILE)`. 

Examples on the ITK wiki used hardcoded variables like `INCLUDE_DIRECTORIES(/home/alex/itk+vtk_cone)` without noting the hardcoded nature of those lines,
causing additional errors during the compilation process and also not showing the correct version of those commands. 

The ITK wiki example of building a project using ITK and VTK refers to the header file `vtkVolumeRayCastCompositeFunction.h`, which is not part of the 
standard VTK installation. Is the example out of date? Did I install the wrong version of VTK? Who knows? 

Blank pages like the link to "How to Combine ITK and VTK In My Application", presumably for 
use with the ITK/VTK example code. 
https://itk.org/Wiki/Itk_FAQ#How_to_combine_ITK_and_VTK_in_my_application

The FLTK guides here http://www.fltk.org/doc-1.3/basics.html#basics_writing or here https://cmake.org/Wiki/CMakeForFLTK, 
which have broken CMakeList examples if they have them at all. This is important because FLTK has particular quirks with how it must be compiled, 
which are detailed here https://github.com/IngwiePhoenix/FLTK/blob/master/README.CMake.txt, on their GitHub, which also gives an outdated version 
of the CMake file according to https://stackoverflow.com/questions/9460242/how-to-compile-glut-opengl-project-with-cmake-and-kdevelop-in-linux.

Worth noting: NONE of these had the version of the CMake commands which eventually worked for me, which can be found in the CMakeLists.txt
file in this repository.

These issues may sound trivial, but stating that the provided guides should be sufficient to install the required tools and then providing 
outdated, inaccurate guides significantly complicates the process of installing and configuring these tools to a degree which cannot be overstated, causing no end
of frustration and overall lower quality of work because of additional time spent troubleshooting these errors rather than developing software. In addition, these
guides are in the form of PowerPoint presentations, which means there is no opportunity to update them or communicate with other users or developers of the 
software. 


Moving on to something that DID work:

To install ITK, I followed these guides: 

https://itk.org/Wiki/ITK/Complete_Setup
https://discourse.itk.org/t/visibility-settings/596 (notes a bug with installing ITK that no other guide had) 
http://itkdebug.blogspot.com/2013/02/install-itk-on-mac-os.html

Even following these three separate guides, none of them noted that it is generally recommended to run `make install` to install binaries locally, 
making it easier to locate the binaries in your CMake scripts. So take note of that.

**Building the Project:**

Remember to run cmake as `cmake -DCMAKE_CXX_FLAGS=-std=c++11` from within the build directory rather than the source directory (see below), 
followed by `make` to generate the executable.



This page has a short, succint Hello World program in ITK and an accompanying CMakeList.txt file to boot. 

https://itk.org/Wiki/ITK/HelloInsight

The VTK examples hosted here https://lorensen.github.io/VTKExamples/site/Cxx/ have simple, straightforward examples, with accompanying CMakeList.txt files to boot. 

FLTK has an example here http://www.fltk.org/doc-1.3/basics.html#basics_writing 



**Project Structure:**


The project has all of the relevant .cpp and CMakeLists.txt files within a directory managed under git version control, 
*with a separate build directory directory outside of version control* which contains the executables, header files of the libraries to be included, 
and files generated during the build process. 

An example structure (Note the "HelloInsight" directory and "HelloInsightBuild" directories):

.
├── HelloInsight
│   ├── CMakeLists.txt
│   └── HelloInsight.cpp
└── HelloInsightBuild
    ├── CMakeCache.txt
    ├── CMakeFiles
    │   ├── 3.10.2
    │   │   ├── CMakeCCompiler.cmake
    │   │   ├── CMakeCXXCompiler.cmake
    │   │   ├── CMakeDetermineCompilerABI_C.bin
    │   │   ├── CMakeDetermineCompilerABI_CXX.bin
    │   │   ├── CMakeSystem.cmake
    │   │   ├── CompilerIdC
    │   │   │   ├── CMakeCCompilerId.c
    │   │   │   ├── a.out
    │   │   │   └── tmp
    │   │   └── CompilerIdCXX
    │   │       ├── CMakeCXXCompilerId.cpp
    │   │       ├── a.out
    │   │       └── tmp
    │   ├── CMakeDirectoryInformation.cmake
    │   ├── CMakeOutput.log
    │   ├── CMakeTmp
    │   ├── HelloInsight.dir
    │   │   ├── CXX.includecache
    │   │   ├── DependInfo.cmake
    │   │   ├── HelloInsight.cpp.o
    │   │   ├── build.make
    │   │   ├── cmake_clean.cmake
    │   │   ├── depend.internal
    │   │   ├── depend.make
    │   │   ├── flags.make
    │   │   ├── link.txt
    │   │   └── progress.make
    │   ├── Makefile.cmake
    │   ├── Makefile2
    │   ├── TargetDirectories.txt
    │   ├── cmake.check_cache
    │   ├── feature_tests.bin
    │   ├── feature_tests.c
    │   ├── feature_tests.cxx
    │   └── progress.marks
    ├── HelloInsight
    ├── ITKFactoryRegistration
    │   ├── itkImageIOFactoryRegisterManager.h
    │   └── itkTransformIOFactoryRegisterManager.h
    ├── Makefile
    └── cmake_install.cmake