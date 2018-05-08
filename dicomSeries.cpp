#include "dicomSeries.h"

// We want a class capable of storing and reusing a series of DICOM 
// images, using the relevant ITK or VTK libraries as appropriate

// This will enable us to call a variety of different ITK and VTK 
// functions on it including registration, segmentation, and rendering/display

// This class should have a default constructor which receives no 
// folder or images and initializes its various attributes to their
// null values

// It should also have a constructor which receives a directory
// name and converts all DICOM images within to a series

// It should also have a constructor which recieves a file name 
// and converts the single DICOM image to a one-image series 

// It should also have a copy constructor to take in another 
// dicomSeries object and set its attributes equal to all of the
// attributes of the other object

dicomSeries::dicomSeries() {
	// TODO: This should be a failsafe only and not usable 
	// in the actual program
	dirName = new char('.');
	reader = ReaderType::New();
	// PixelType defined in dicomSeries.h
	// using ImageType = itk::Image< PixelType, Dimension >;
	// nameGenerator comes from an ITK library and may not be 
	// suitable for VTK interactions with the series
	nameGenerator = InputNamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
  	nameGenerator->AddSeriesRestriction("0008|0021");
  	nameGenerator->SetGlobalWarningDisplay(false);
  	nameGenerator->SetDirectory(dirName);
}

dicomSeries::dicomSeries(char* directoryName) {
	dirName = directoryName;
	// nameGenerator comes from an ITK library and may not be 
	// suitable for VTK interactions with the series
	nameGenerator = InputNamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
  	nameGenerator->AddSeriesRestriction("0008|0021");
  	nameGenerator->SetGlobalWarningDisplay(false);
  	nameGenerator->SetDirectory(dirName);
  	// const SeriesIdContainer &seriesUID = nameGenerator->GetSeriesUIDs();
  	/*
  	auto seriesItr = seriesUID.begin();
    auto seriesEnd = seriesUID.end();
    */

    fileNames = nameGenerator->GetInputFileNames();
    reader = ReaderType::New();
	dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);
	reader->SetFileNames(fileNames);
	reader->Update();
}
/*
dicomSeries::ReaderType::Pointer getReader() { 
	return reader; 
}
*/
/*
void dicomSeries::printSeries() {	
    if (seriesItr == seriesEnd) {
    	std::cout << "No DICOMs in: " << dirName << std::endl;
    	return;
    }
    else {
		std::cout << "The directory: ";
		std::cout << dirName << std::endl;
		std::cout << "Contains the following DICOM Series: ";
		std::cout << std::endl;
	    while (seriesItr != seriesEnd)
	      {
	      std::cout << seriesItr->c_str() << std::endl;
	      ++seriesItr;
	      }
	    // seriesItr = seriesUID.begin();
	}
    return;
}
*/
