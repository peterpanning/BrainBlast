A small application to view DICOM image scans, written using C++. 

This is the semester project for CSC 621 at San Francisco State University, written by "Team Forest:" Flavy Tonfack, Amelia Rawling, Veronica Yuen, and Peter Mutch


##Installing the necessary tools:

This project requires ITK, VTK, and FLTK. 

A quick word on the installation process:

I did not find the recommended installation guides helpful. They seemed to be created with Windows users in mind (my team was all on macOS) and did not provide any guidance on integrating the three libraries together within the same program, which I found extremely difficult. I have experience compiling programs at the command line but this was my first time using multiple locally installed libraries in a C++ program. Here are some of the problems I encountered while searching for a guide on this:

TODO: Find links/screenshots for these first few examples

The recommended installation guide indicated that in CMakeLists.txt files we should use `INCLUDE ($USE_ITK_FILE)`, which caused errors. The correct command, which was on the ITK wiki, is `INCLUDE ($ITK_USE_FILE)`. 

The ITK wiki example of building a project using ITK and VTK referred to the header file `vtkVolumeRayCastCompositeFunction.h`, which was not part of my VTK installation. Was the example out of date? Did I install the wrong version of VTK? The answer is unclear.

Other examples on the ITK wiki used hardcoded variables like `INCLUDE_DIRECTORIES(/home/alex/itk+vtk_cone)` instead of showing the variable version of those commands, meaning I could not depend on that command to work on my teammate's computers. 

The ITK wiki tutorials [link to blank pages at critical junctures](https://itk.org/Wiki/Itk_FAQ#How_to_combine_ITK_and_VTK_in_my_application)

The FLTK guides [on their website](http://www.fltk.org/doc-1.3/basics.html#basics_writing) and [on CMake's website](https://cmake.org/Wiki/CMakeForFLTK) have broken CMakeList examples if they have them at all. 




###I found these guides and posts to be helpful: 
 
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



##Building the Project:

Remember to run `cmake -DCMAKE_CXX_FLAGS=-std=c++11` from within the build directory rather than the source directory (see below), followed by `make` to generate the executable.




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