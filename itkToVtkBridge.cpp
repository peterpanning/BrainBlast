#include "itkToVtkBridge.h"

itkToVtkBridge::itkToVtkBridge(dicomSeries::DicomImage::Pointer image) {
	
	// This bridge takes in a DicomImage pointer, which can be generated 
	// by any variety of filters, and has a connector whose output is used
	// to render the input image in 3D

	rescaleFilter = IntensityFilter::New();
	caster = CastingType::New();
  	connector = ConnectorType::New();

  	// Rescale image intensity values

	rescaleFilter->SetInput(image);
	rescaleFilter->SetOutputMinimum(0);
  	rescaleFilter->SetOutputMaximum(255);

  	// Cast image intensity values to unsigned short
	caster->SetInput( rescaleFilter->GetOutput() ); 

	// Pass rescaled & casted image to ImageToVTKImageFilter connector
	connector->SetInput(caster->GetOutput()); 
	connector->Update(); 
}