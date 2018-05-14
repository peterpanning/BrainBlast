A small application to view DICOM image scans, written using C++. 

This is the semester project for CSC 621 at San Francisco State University, written by "Team Forest:" Peter Mutch and Veronica Yuen


Installing the necessary tools:

I found these guides and posts to be helpful: 
 
https://itk.org/Wiki/ITK/Complete_Setup

https://discourse.itk.org/t/visibility-settings/596 (notes a bug with installing ITK that no other guide had) 

http://itkdebug.blogspot.com/2013/02/install-itk-on-mac-os.html

https://github.com/IngwiePhoenix/FLTK/blob/master/README.CMake.txt 

https://stackoverflow.com/questions/9460242/how-to-compile-glut-opengl-project-with-cmake-and-kdevelop-in-linux

https://itk.org/Wiki/ITK/HelloInsight

https://lorensen.github.io/VTKExamples/site/Cxx/  

http://www.fltk.org/doc-1.3/basics.html#basics_writing 

https://github.com/fblupi/rendering-volume-from-dicom-vtk/blob/master/RenderingVolumeFromDICOM.cpp

If you're reading this and are an ITK/VTK/FLTK maintainer, please consider updating your documentation with these findings. 


On the other hand, if you're like me and haven't compiled a library from source in a long time (or ever), remember after you run `make` to also run `make install` to install the binaries locally. This helps your CMake scripts find them with `find_package`. 


**Project Structure:**


The project has all of the relevant .cpp and CMakeLists.txt files within a directory managed under git version control, 
*with a separate build directory directory outside of version control* which contains the executables, header files of the libraries to be included, 
and files generated during the build process. 

To view the tree diagram of a sample project/build structure below, open this file in a text editor. 
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