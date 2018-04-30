#include "dicomSeries.h"

// ITK libraries for converting a DICOM series to a 3D itkImage

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
	dirName = new char('.');
	nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
  	nameGenerator->AddSeriesRestriction("0008|0021");
  	nameGenerator->SetGlobalWarningDisplay(false);
  	nameGenerator->SetDirectory(dirName);
}

dicomSeries::dicomSeries(char* directoryName) {
	dirName = directoryName;
	nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
  	nameGenerator->AddSeriesRestriction("0008|0021");
  	nameGenerator->SetGlobalWarningDisplay(false);
  	nameGenerator->SetDirectory(dirName);
}

void dicomSeries::printSeries() {

	// TODO: Defining these here is technically redundant, but 
	// I'm not sure how to use an automatically typed variable
	// as a parameter, so this is what we're doing for now
	const SeriesIdContainer &seriesUID = nameGenerator->GetSeriesUIDs();
	auto seriesItr = seriesUID.begin();
    auto seriesEnd = seriesUID.end();	
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
	    seriesItr = seriesUID.begin();
	}
    return;
}

int dicomSeries::to3D() {

	// This function converts a dicomSeries object from memory and writes them to a 3D image file
  	constexpr unsigned int Dimension = 3;
  	// PixelType defined in dicomSeries.h
  	using ImageType = itk::Image< PixelType, Dimension >; 
  	const SeriesIdContainer &seriesUID = nameGenerator->GetSeriesUIDs();
  	auto seriesItr = seriesUID.begin();
    auto seriesEnd = seriesUID.end();

  	try {
  		while (seriesItr != seriesEnd) {
  			std::string seriesIdentifier = seriesItr->c_str();
  			seriesItr++;
  			std::cout << "\nReading: ";
      		std::cout << seriesIdentifier << std::endl;
      		using FileNamesContainer = std::vector< std::string >;
      		FileNamesContainer fileNames =
       		nameGenerator->GetFileNames(seriesIdentifier);

      		using ReaderType = itk::ImageSeriesReader< ImageType >;
      		ReaderType::Pointer reader = ReaderType::New();
      		using ImageIOType = itk::GDCMImageIO;
      		ImageIOType::Pointer dicomIO = ImageIOType::New();
      		reader->SetImageIO(dicomIO);
      		reader->SetFileNames(fileNames);

      		using WriterType = itk::ImageFileWriter< ImageType >;
      		WriterType::Pointer writer = WriterType::New();

      		std::string outFileName = dirName + std::string("/") + seriesIdentifier + ".nrrd";

      		writer->SetFileName(outFileName);
      		writer->UseCompressionOn();
      		writer->SetInput(reader->GetOutput());
      		std::cout << "Writing: " << outFileName << std::endl;

      		try { writer->Update(); }
      		catch (itk::ExceptionObject &ex) {
        		std::cout << ex << std::endl;
        		continue;
        	}
  		}
  	}
  	catch (itk::ExceptionObject &ex) {
    	std::cout << ex << std::endl;
    	return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}
