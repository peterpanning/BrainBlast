#include "dicomSeries.h"

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
	region = ConnectedThresholdFilter::New();
	// The Houndsfield intensity values for bounds are a total guess, adjust experimentally
	dicomSeries::DicomPixelType lowerBound = 0;
	dicomSeries::DicomPixelType upperBound = 50;
	DicomImage::IndexType index;
	// ImageJ seems to indicate this is x, y, z, 512x512x91 images
	index[0] = 256;
	index[1] = 256;
	index[2] = 22;

	region->SetInput(reader->GetOutput());
	region->SetLower(lowerBound);
	region->SetUpper(upperBound);
	region->SetReplaceValue(255);
	region->SetSeed(index);
	region->Update();

	// Quick mask filter to retrieve Houndsfield values, apparently?

	MaskImageFilter::Pointer mask = MaskImageFilter::New();
	mask->SetInput(reader->GetOutput());
	mask->SetMaskImage(region->GetOutput());
	mask->Update();

	return region->GetOutput();
}