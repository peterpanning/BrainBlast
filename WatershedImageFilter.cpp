// Initial copy of the Watershed filter side program.  Not incorporated with the project CMakeLists file yet.  Need to separate things into header files.

// watershed from 
// https://itk.org/ITKExamples/src/Segmentation/Watersheds/SegmentWithWatershedImageFilter/Documentation.html 
// https://itk.org/Doxygen/html/WikiExamples_2Segmentation_2WatershedImageFilter_8cxx-example.html#_a10
#include <iostream>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkVectorCastImageFilter.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkWatershedImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"

// Get current path needed
// http://www.codebind.com/cpp-tutorial/c-get-current-directory-linuxwindows/
#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
#include <string>

// Using VolumeFrom slices 
// https://itk.org/Wiki/ITK/Examples/IO/VolumeFromSlices

// Run with:
// ./WatershedImageFilter threshold level
// e.g.
// ./WatershedImageFilter 0.005 .5
// (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)


/*using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;
using LabeledImageType = itk::Image<itk::IdentifierType, 2>;*/
constexpr unsigned int Dimension = 2;

  using InputImageType = itk::Image< unsigned char, Dimension >;
  using FloatImageType = itk::Image< float, Dimension >;
  using RGBPixelType = itk::RGBPixel< unsigned char >;
  using RGBImageType = itk::Image< RGBPixelType, Dimension >;
  using LabeledImageType = itk::Image< itk::IdentifierType, Dimension >;

// declaring functions 
// static void CreateImage(UnsignedCharImageType::Pointer image);
static void PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level);
std::string GetCurrentWorkingDir( void );

int main( int argc, char *argv[] )
{
  // Verify arguments
  if (argc < 3 )
    {
    std::cerr << "Parameters " << std::endl;
    std::cerr << " threshold level" << std::endl;
    return 1;
    }
  // Parse arguments
  std::string strThreshold = argv[1];
  float threshold = 0.0;
  std::stringstream ssThreshold;
  ssThreshold << strThreshold;
  ssThreshold >> threshold;
  
  std::string strLevel = argv[2];
  float level = 0.0;
  std::stringstream ssLevel;
  ssLevel << strLevel;
  ssLevel >> level;
  
  // Output arguments
  std::cout << "Running with:" << std::endl
            << "Threshold: " << threshold << std::endl
            << "Level: " << level << std::endl;
  
  // UnsignedCharImageType::Pointer image = UnsignedCharImageType::New();
  // CreateImage(image);
  std::string base = GetCurrentWorkingDir();
  std::string dataFolder = base + "data/";
  std::string imagePath = dataFolder + "trial.dcm";
  std::cout << "image path: " << imagePath << std::endl;

  using FileReaderType = itk::ImageFileReader< InputImageType >;
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName( imagePath );
  
  using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<
    InputImageType, FloatImageType >;
  GradientMagnitudeImageFilterType::Pointer gradientMagnitudeImageFilter = GradientMagnitudeImageFilterType::New();
  gradientMagnitudeImageFilter->SetInput( reader->GetOutput());
  gradientMagnitudeImageFilter->Update();
  // Custom parameters
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), threshold, level);
  
  // Fixed parameters
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .0040, .40);
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .0035, .35);
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .0040, .40);
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .0045, .45);
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .005, .5);
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .0055, .55);
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), .006, .6);
  
  return EXIT_SUCCESS;
} // end main

/*void CreateImage(UnsignedCharImageType::Pointer image)
{
  // Create a white image with 3 dark regions of different values
  
  itk::Index<2> start;
  start.Fill(0);
  itk::Size<2> size;
  size.Fill(200);
  itk::ImageRegion<2> region(start,size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(255);
  itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(image,region);
 
  while(!imageIterator.IsAtEnd())
    {
    if(imageIterator.GetIndex()[0] > 20 && imageIterator.GetIndex()[0] < 50 &&
       imageIterator.GetIndex()[1] > 20 && imageIterator.GetIndex()[1] < 50)
    imageIterator.Set(50);
 
    ++imageIterator;
    }
    
  imageIterator.GoToBegin();
  
  while(!imageIterator.IsAtEnd())
    {
    if(imageIterator.GetIndex()[0] > 60 && imageIterator.GetIndex()[0] < 80 &&
       imageIterator.GetIndex()[1] > 60 && imageIterator.GetIndex()[1] < 80)
    imageIterator.Set(100);
 
    ++imageIterator;
    }
    
  imageIterator.GoToBegin();
  
  while(!imageIterator.IsAtEnd())
    {
    if(imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 130 &&
       imageIterator.GetIndex()[1] > 100 && imageIterator.GetIndex()[1] < 130)
    imageIterator.Set(150);
 
    ++imageIterator;
    }
    
  using FileWriterType = itk::ImageFileWriter<UnsignedCharImageType>;
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName("input.png");
  writer->SetInput(image);
  writer->Update();
} // end CreateImage*/

void PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level)
{
  using WatershedFilterType = itk::WatershedImageFilter<FloatImageType>;
  WatershedFilterType::Pointer watershed = WatershedFilterType::New();
  watershed->SetThreshold(threshold);
  watershed->SetLevel(level);
  watershed->SetInput(image);
  watershed->Update();

  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
  RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetInput(watershed->GetOutput());
  colormapImageFilter->SetColormap( RGBFilterType::Jet );
  colormapImageFilter->Update();
  std::stringstream ss;
  ss << "output_" << threshold << "_" << level << ".dcm";
  
  using FileWriterType = itk::ImageFileWriter<RGBImageType>;
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName(ss.str());
  writer->SetInput(colormapImageFilter->GetOutput());
  writer->Update();
    
} // end PerformSegmentation

std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  if(current_working_dir.find("build") != std::string::npos){
    // remove build
    current_working_dir.erase(current_working_dir.length()-5);
  }
  return current_working_dir;
}// end GetCurrentWorkingDir

// cmake file for the side program.  Will work on incorporating this file into the project CMakeLists.
/*cmake_minimum_required(VERSION 2.8.9)

project(SegmentWithWatershedImageFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SegmentWithWatershedImageFilter WatershedImageFilter.cxx)
target_link_libraries(SegmentWithWatershedImageFilter ${ITK_LIBRARIES})

install(TARGETS SegmentWithWatershedImageFilter
  DESTINATION bin/ITKExamples/Segmentation/Watersheds
  COMPONENT Runtime
  )

install(FILES WatershedImageFilter.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Segmentation/Watersheds/SegmentWithWatershedImageFilter/
  COMPONENT Code
  )
*/