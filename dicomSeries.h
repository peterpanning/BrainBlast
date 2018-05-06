#ifndef FINALPROJECT_DICOMSERIES_H 
#define FINALPROJECT_DICOMSERIES_H

// TODO: Is storing these header files here best practice?

#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"

class dicomSeries{
public:
	dicomSeries();
	dicomSeries(char*);
	int to3D();
	void printSeries();
	int watershed()
protected:
private:
	// All DICOM series use 16-bit colors
	using PixelType = signed short;
	char* dirName;
	using NamesGeneratorType = itk::GDCMSeriesFileNames;
  	NamesGeneratorType::Pointer nameGenerator;
  	using SeriesIdContainer = std::vector< std::string >;
  	// Should have an attribute which it can use to store and return the
  	// actual series for processing and passing to vtk
};

#endif