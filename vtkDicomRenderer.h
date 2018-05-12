#ifndef FINALPROJECT_VTKDICOMRENDERER_H 
#define FINALPROJECT_VTKDICOMRENDERER_H

// VTK libraries used to render a 3D Volume of a DICOM series
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include "dicomSeries.h"
#include "itkToVtkBridge.h"

// From the itkVtkBridge class



class vtkDicomRenderer{
public:
	vtkDicomRenderer();
	vtkDicomRenderer(char*);
	vtkDicomRenderer(itkToVtkBridge::ConnectorType::Pointer);
	void initializeRenderer();
	void render();
private:
  	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
  	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
  	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
  	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
  	vtkSmartPointer<vtkPiecewiseFunction> gradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  	vtkSmartPointer<vtkPiecewiseFunction> scalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  	vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
  	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
};

#endif