#ifndef FINALPROJECT_DICOMESERIES_H
#define FINALPROJECT_DICOMESERIES_H

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

class gradientDiffusion{
public:
	gradientDiffusion();
	gradientDiffusion(char* dirName);
	void applyFilter();
private: 
	
};

#endif