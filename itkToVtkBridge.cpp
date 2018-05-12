#include "itkToVtkBridge.h"

itkToVtkBridge::itkToVtkBridge(dicomSeries::DicomImage::Pointer image) {
	
	// This bridge takes in any DicomImage pointer, which can be generated 
	// by any variety of correctly designed filters as demonstrated on 
	// pages 52 and 53 of the master's thesis
	// and has a connector which is used to render the series in 3D

	rescaleFilter = IntensityFilter::New();
	caster = CastingType::New();
  	connector = ConnectorType::New();

	// Rescale the DICOM image that we read in 
	// One advantage of having the rescaling filter in this class is that 
	// it allows the constructor to take in the reader rather than the 
	// altered output from the reader, which might be harder to define
	// in type

	rescaleFilter->SetInput(image);
	rescaleFilter->SetOutputMinimum(0);
  	rescaleFilter->SetOutputMaximum(255);

  	// Cast new image intensity values to be the correct data type (unsigned short)
	caster->SetInput( rescaleFilter->GetOutput() ); 
	// Pass this to the ImageToVTKImageFilter connector
	connector->SetInput(caster->GetOutput()); 
	connector->Update(); 
}