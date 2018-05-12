// https://itk.org/ITKExamples/src/Filtering/Thresholding/ThresholdAnImageUsingBinary/Documentation.html?highlight=threshold%20binary
// output at 50 looks to give the best result. 

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"

using PixelType = unsigned char;
constexpr unsigned int Dimension = 3; 

using ImageType = itk::Image< PixelType, Dimension>;
using ReaderType = itk::itkImageFileReader<ImageType>;

using BinaryThresholdFilterType = itk::itkBinaryThresholdImageFilter< ImageType, ImageType>;
using WriterType = itk::ImageFileWriter< ImageType >;


int main( int argc, char * argv[] )
{
  // Binary Thresholding
  // low, high, out, in
  // 30 150 0 255
  applyBinaryThresholding();
  

  return EXIT_SUCCESS;
}

smoothing::applyBinaryThresholding(char* inImage,int lowThreshold, int highThreshold, int outValue, int inValue, char* outImage){ 
  // ttps://itk.org/ITKExamples/src/Filtering/Thresholding/ThresholdAnImageUsingBinary/Documentation.html?highlight=threshold%20binary

  auto lowerThresh = static_cast<PixelType>(30);
  auto upperThresh = static_cast<PixelType>(150);
  auto OutsideValue = static_cast<PixelType>(0);
  auto InsideValue = static_cast<PixelType>(255);

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inImage);

  BinaryThresholdFilterType::Pointer filter = BinaryThresholdFilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetLowerThreshold( LowerThreshold );
  filter->SetUpperThreshold( UpperThreshold );
  filter->SetOutsideValue( OutsideValue );
  filter->SetInsideValue( InsideValue );

  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outImage );
  writer->SetInput( filter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }

}// end applyBinaryThresholding