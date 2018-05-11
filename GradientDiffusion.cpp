#include "gradientDiffusion.h"
// Based on example code from https://itk.org/ITKExamples/src/Filtering/AnisotropicSmoothing/ComputeGradientAnisotropicDiffusion/Documentation.html?highlight=anisotropic

// note for time step, need to use something smaller than .12207 for .dcm files
gradientDiffusion::gradientDiffusion(){
// by default, assuming dicom folder is in the same folder as the source file
  
} // end gradientDiffusion()
  gradientDiffusion::gradientDiffusion(char* dirName){

  }// end gradienDiffusion(char* dirName)
  void gradientDiffustion::applyFilter(){

  }// end applyFilter