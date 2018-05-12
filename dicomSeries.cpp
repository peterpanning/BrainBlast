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