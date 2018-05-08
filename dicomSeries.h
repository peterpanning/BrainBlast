#ifndef FINALPROJECT_DICOMSERIES_H 
#define FINALPROJECT_DICOMSERIES_H

// TODO: Is storing these header files here best practice?

#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"

class dicomSeries{
	// Using allows us to basically define types as variables.


	// DICOMs use floats to represent pixels
	using InPixelType = float;
	// And VTK uses signed shorts
	using OutPixelType = signed short;
	
	// Used later to set the reader's filenames
	using InputNamesGeneratorType = itk::GDCMSeriesFileNames;
	// TODO: Are we still using these? 
	//using SeriesIdContainer = std::vector< std::string >;
	// Used to hold the names of files before passing them to reader
	using FileNamesContainer = std::vector< std::string >;

	// Used later to set the reader's IO
	using ImageIOType = itk::GDCMImageIO;
	


	// TODO: Are we still using this? 
	// const SeriesIdContainer &seriesUID;

public:
	// These variables, especially Input/OutputImageType and
	// ReaderType, are public because they will be used in 
	// many other classes 
	// We are reading in a 3D image represented with floats, and
	// converting it to a 3D image represent with signed shorts
	const static unsigned int Dimension = 3;
	using InputImageType = itk::Image<InPixelType, Dimension>;
	using OutputImageType = itk::Image<OutPixelType, Dimension>;

	// Reader is an ITK image series reader
	using ReaderType = itk::ImageSeriesReader< InputImageType >;
	ReaderType::Pointer reader;
	// Default Constructor
	dicomSeries();
	// Constructor given a filepath
	dicomSeries(char*);
	// Prints the series
	// void printSeries();
	// Performs watershed segmentation
	int watershed();
	// Returns this object's reader
	//ReaderType::Pointer getReader();
  	
protected:
private:
	char* dirName;
	// Pointer to a reader, initialized in constructor
	
	// Pointer to a NamesGenerator, initialized in constructor
  	InputNamesGeneratorType::Pointer nameGenerator;
  	// 
  	FileNamesContainer fileNames;
  	ImageIOType::Pointer dicomIO;
};

#endif