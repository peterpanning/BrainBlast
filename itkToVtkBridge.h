#ifndef FINALPROJECT_ITKTOVTKBRIDGE_H 
#define FINALPROJECT_ITKTOVTKBRIDGE_H

#include <itkCastImageFilter.h>
#include <itkImageSeriesReader.h>
#include <itkImageToVTKImageFilter.h>
#include "itkRescaleIntensityImageFilter.h"
#include "dicomSeries.h"

class itkToVtkBridge {
	const static unsigned int Dimension = 3;
	using VtkPixelType = signed short;
	using IntensityFilter = itk::RescaleIntensityImageFilter
		< dicomSeries::DicomImage, dicomSeries::DicomImage >;
	IntensityFilter::Pointer rescaleFilter;
public:
	using VtkImage = itk::Image<VtkPixelType, Dimension>;
	using ConnectorType = itk::ImageToVTKImageFilter<VtkImage>;
	itkToVtkBridge(dicomSeries::DicomImage::Pointer);
	ConnectorType::Pointer connector;
	
private:	
	using CastingType = itk::CastImageFilter
		<dicomSeries::DicomImage, VtkImage>;
	CastingType::Pointer caster;
};

#endif