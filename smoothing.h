#ifndef FINALPROJECT_SMOOTHING_H 
#define FINALPROJECT_SMOOTHING_H

#include "itkImageSeriesReader.h"
#include "itkImageSeriesWriter.h"
#include "itkImage.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

class smoothing{
  // need to define the new types
  const static unsigned int Dimension = 3; 
  using PixelType = float ;
  using ImageType = itk::Image< PixelType, Dimension>;
  using ReaderType = itk::ImageSeriesReader<ImageType>;
  using GradientFilterType = itk::GradientAnisotropicDiffusionImageFilter<ImageType, ImageType>;
  using RescaleType = itk::RescaleIntensityImageFilter<ImageType, ImageType>;
  using WriterType = itk::ImageSeriesWriter< ImageType, ImageType >;

public:
  void applySmoothing(ReaderType::Pointer);
};
#endif