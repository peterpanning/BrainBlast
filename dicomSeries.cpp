#include "dicomSeries.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkGrayscaleErodeImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalOpeningImageFilter.h"
#include "itkNeighborhoodConnectedImageFilter.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"

dicomSeries::dicomSeries() {
	// This is a failsafe only, should only be called in the process of 
	// initializing 

	// Initialized to . by default to satisfy initialization rules.
	// Would make more sense to initialize it to the normal DICOM 
	// directory location
	dirName = new char('.');

	// We need an itk reader to read the series
	reader = ReaderType::New();
	nameGenerator = DicomNamesGeneratorType::New();
  	nameGenerator->SetDirectory(dirName);
}

dicomSeries::dicomSeries(char* directoryName) {
	dirName = directoryName;
	nameGenerator = DicomNamesGeneratorType::New();
  	nameGenerator->SetDirectory(dirName);

  	// Each dicom series is a series of files which must be read in 
    fileNames = nameGenerator->GetInputFileNames();
    reader = ReaderType::New();
	dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);
	reader->SetFileNames(fileNames);
	reader->Update();
}

dicomSeries::DicomImage::Pointer dicomSeries::GetOutput() {
	return reader->GetOutput();
}

dicomSeries::DicomImage::Pointer dicomSeries::RegionGrow() {

	// Morphological Operations requires a structuring element
	using StructuringElement = itk::BinaryBallStructuringElement 
	<DicomPixelType, Dimension>;
	StructuringElement structure;
	structure.SetRadius(2);
	structure.CreateStructuringElement();

	std::cout << "Opening...\n";

	using OpeningFilter = itk::BinaryMorphologicalOpeningImageFilter 
	<DicomImage, DicomImage, StructuringElement>;
    OpeningFilter::Pointer opening = OpeningFilter::New();
    opening->SetInput(reader->GetOutput());
    opening->SetKernel(structure);
    opening->Update();

    std::cout << "Closing...\n";

    using ClosingFilter = itk::BinaryMorphologicalClosingImageFilter 
    <DicomImage, DicomImage, StructuringElement>;
    ClosingFilter::Pointer closing = ClosingFilter::New();
    closing->SetInput(opening->GetOutput());
    closing->SetKernel(structure);
    closing->Update();

    std::cout << "Smoothing...\n";

	// Anisotropic edge-preserving smoothing
	using SmoothingFilter = itk::GradientAnisotropicDiffusionImageFilter
	<DicomImage, DicomImage>; 
	SmoothingFilter::Pointer smoothing = SmoothingFilter::New();

	smoothing->SetInput(closing->GetOutput());
	// fewer iterations seems to result in a blurrier, 
	// more pixelated image, but supposedly should avoid causing
	// flat edges. Flat edges are still visible across the top 
	// of the brain. maybe a smaller time step would solve this
	smoothing->SetNumberOfIterations(2);  
	smoothing->SetTimeStep(.06);
	smoothing->Update();

	// Connected Component threshold filter for region growing 
	using ConnectedFilterType = itk::ConnectedThresholdImageFilter
	< DicomImage, DicomImage >;
	ConnectedFilterType::Pointer region = ConnectedFilterType::New();

	// Houndsfield intensity values determined experimentally
	// Most grey matter is between 25 and 45
	dicomSeries::DicomPixelType lowerBound = 25;
	dicomSeries::DicomPixelType upperBound = 45;
	DicomImage::IndexType index;

	// 0 = x, 1 = y, 2 = z (image number in the series)
	index[0] = 256;
	index[1] = 256;
	index[2] = 19; // earliest we can seed without missing region entirely

	std::cout << "Connecting...\n";

	region->SetInput(smoothing->GetOutput());
	region->SetLower(lowerBound);
	region->SetUpper(upperBound);
	region->SetReplaceValue(255);
	region->SetSeed(index);
	region->Update();

	std::cout << "Masking...\n";

	MaskImageFilter::Pointer mask = MaskImageFilter::New();
	mask->SetInput(reader->GetOutput());
	mask->SetMaskImage(region->GetOutput());
	mask->Update();

	std::cout << "Done region growing.\n";

	return mask->GetOutput();
}
