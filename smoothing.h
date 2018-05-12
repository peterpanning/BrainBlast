#ifndef FINALPROJECT_SMOOTHING_H 
#define FINALPROJECT_SMOOTHING_H

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

class smoothing{
  // need to define the new types
  const static unsigned int Dimension = 3; 
  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension>;
  using ReaderType = itk::itkImageFileReader<ImageType>;
  using GradientFilterType = itk::itkGradientAnisotropicDiffusionImageFilter<ImageType, ImageType>;
  using RescaleType = itk::RescaleIntensityImgeFilter<ImageType, ImageType>;
  using WriterType = itk::ImageFileWriter< ImageType >;

public:
  applySmoothing(ReaderType::point);
};