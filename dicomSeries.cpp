#include "dicomSeries.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkGrayscaleErodeImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalOpeningImageFilter.h"
#include "itkNeighborhoodConnectedImageFilter.h"

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

	// Anisotropic difficusion supposedly preserves edges. uses iterations/time
	using SmoothingFilter = itk::GradientAnisotropicDiffusionImageFilter<DicomImage, DicomImage>; // decent output, still has most of the chest cavity
	// curvature gradient used in master's thesis. uses iterations/time
	//using SmoothingFilter = itk::CurvatureFlowImageFilter<DicomImage, DicomImage>; // mediocre output
	// gaussian filters appeared to have no output, use sigma/variance
	//using SmoothingFilter = itk::SmoothingRecursiveGaussianImageFilter<DicomImage, DicomImage>; // no output? 
	//using SmoothingFilter = itk::DiscreteGaussianImageFilter<DicomImage, DicomImage>; // no output?

	// opening also supposedly preserves edges while reducing noise, though it might not smooth?

	using StructuringElement = itk::BinaryBallStructuringElement<DicomPixelType, Dimension>;
	StructuringElement structure;
	structure.SetRadius(3);
	structure.CreateStructuringElement();

	std::cout << "Opening...\n";

	using OpeningFilter = itk::BinaryMorphologicalOpeningImageFilter <DicomImage, DicomImage, StructuringElement>;
    OpeningFilter::Pointer opening = OpeningFilter::New();
    opening->SetInput(reader->GetOutput());
    opening->SetKernel(structure);
    opening->Update();

    std::cout << "Smoothing...\n";


	SmoothingFilter::Pointer smoothing = SmoothingFilter::New();

	smoothing->SetInput(opening->GetOutput());
	smoothing->SetNumberOfIterations(2);
	smoothing->SetTimeStep(.06);
	//smoothing->SetVariance(4);
	smoothing->Update();

	// Trying connected neighbor for region growing

	// Connected Component threshold filter for region growing 
	using ConnectedFilterType = itk::ConnectedThresholdImageFilter< DicomImage, DicomImage >;
	// using ConnectedFilterType = itk::NeighborhoodConnectedImageFilter<DicomImage, DicomImage >;
	ConnectedFilterType::Pointer region = ConnectedFilterType::New();


	// The Houndsfield intensity values for bounds are a total guess, adjust experimentally
	dicomSeries::DicomPixelType lowerBound = 25;
	dicomSeries::DicomPixelType upperBound = 45;
	DicomImage::IndexType index;
	// ImageJ seems to indicate this is x, y, z, 512x512x91 images
	index[0] = 256;
	index[1] = 256;
	index[2] = 20;

	DicomImage::SizeType radius;

	radius[0] = 1;
	radius[1] = 1;

	//region->SetRadius(radius);

	std::cout << "Connecting...\n";

	region->SetInput(smoothing->GetOutput());
	region->SetLower(lowerBound);
	region->SetUpper(upperBound);
	region->SetReplaceValue(255);
	region->SetSeed(index);
	region->Update();

	// Quick mask filter to retrieve Houndsfield values, apparently?

	std::cout << "Masking...\n";

	MaskImageFilter::Pointer mask = MaskImageFilter::New();
	mask->SetInput(reader->GetOutput());
	mask->SetMaskImage(region->GetOutput());
	mask->Update();

	std::cout << "Done region growing.\n";

	return mask->GetOutput();
}
