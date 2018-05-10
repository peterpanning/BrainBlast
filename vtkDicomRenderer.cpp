// VTK libraries used to render a 3D volume
#include "vtkDicomRenderer.h"

// **CONSTRUCTORS**

vtkDicomRenderer::vtkDicomRenderer(){
	// vtk can actually render dicoms on its own if it wants
	reader->SetDirectoryName("../finalProject/DICOMs");
	reader->Update();
	imageData->ShallowCopy(reader->GetOutput());
	vtkDicomRenderer::initializeRenderer();
}

vtkDicomRenderer::vtkDicomRenderer(char* dirName){
	reader->SetDirectoryName(dirName);
	reader->Update();
	imageData->ShallowCopy(reader->GetOutput());
	vtkDicomRenderer::initializeRenderer();
}

vtkDicomRenderer::vtkDicomRenderer(dicomSeries::ReaderType::Pointer reader) {
	// This constructor converts the dicomSeries itk-based dicom reader to a vtk volume
	const static unsigned int Dimension = 3;
	using VtkPixelType = signed short;
	using VtkImage = itk::Image<VtkPixelType, Dimension>;
	using CastingType = itk::CastImageFilter<dicomSeries::DicomImage, VtkImage>;
	using ConnectorType = itk::ImageToVTKImageFilter<VtkImage>;
	// TODO: Should be in dicomSeries class? 
	using IntensityFilter = itk::RescaleIntensityImageFilter< dicomSeries::DicomImage, dicomSeries::DicomImage >;

	CastingType::Pointer caster = CastingType::New();
  	ConnectorType::Pointer connector = ConnectorType::New();
	IntensityFilter::Pointer rescaleFilter = IntensityFilter::New();

	// Rescale the DICOM image that we read in 
	// One advantage of having the rescaling filter in this class is that 
	// it allows the constructor to take in the reader rather than the 
	// altered output from the reader, which might be harder to define
	// in type
	rescaleFilter->SetInput(reader->GetOutput());
	rescaleFilter->SetOutputMinimum(0);
  	rescaleFilter->SetOutputMaximum(255);

  	// Cast new image intensity values to be the correct data type (unsigned short)
	caster->SetInput( rescaleFilter->GetOutput() ); 
	// Pass this to the ImageToVTKImageFilter connector
	connector->SetInput(caster->GetOutput()); 
	connector->Update(); 

	// vtkImageData object takes in the itk::ImageToVTKImageFilter connector's output

	imageData->DeepCopy(connector->GetOutput());

	vtkDicomRenderer::initializeRenderer();
}

// **END CONSTRUCTORS**

void vtkDicomRenderer::initializeRenderer() {
	renderer->SetBackground(0.1, 0.2, 0.3);

	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(500, 500);

	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(2000.0, 1.0);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	scalarOpacity->AddPoint(-800.0, 0.0);
	scalarOpacity->AddPoint(-750.0, 1.0);
	scalarOpacity->AddPoint(-350.0, 1.0);
	scalarOpacity->AddPoint(-300.0, 0.0);
	scalarOpacity->AddPoint(-200.0, 0.0);
	scalarOpacity->AddPoint(-100.0, 1.0);
	scalarOpacity->AddPoint(1000.0, 0.0);
	scalarOpacity->AddPoint(2750.0, 0.0);
	scalarOpacity->AddPoint(2976.0, 1.0);
	scalarOpacity->AddPoint(3000.0, 0.0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(-750.0, 0.08, 0.05, 0.03);
	color->AddRGBPoint(-350.0, 0.39, 0.25, 0.16);
	color->AddRGBPoint(-200.0, 0.80, 0.80, 0.80);
	color->AddRGBPoint(2750.0, 0.70, 0.70, 0.70);
	color->AddRGBPoint(3000.0, 0.35, 0.35, 0.35);
	volumeProperty->SetColor(color);

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();
	return;
}

void vtkDicomRenderer::render(){
  // This starts the event loop and as a side effect causes an initial render.
  renderWindow->Render();
  renderWindowInteractor->Start();
}