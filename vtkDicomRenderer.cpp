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

vtkDicomRenderer::vtkDicomRenderer(itkToVtkBridge::ConnectorType::Pointer connector) {

	// This constructor takes in a connection from an itkToVtkBridge and renders it. 

	imageData->DeepCopy(connector->GetOutput());

	vtkDicomRenderer::initializeRenderer();
}


// **END CONSTRUCTORS**

void vtkDicomRenderer::initializeRenderer() {
	renderer->SetBackground(0.1, 0.2, 0.3);

	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(1000, 1000);

	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	//volumeProperty->SetAmbient(0.1);
	//volumeProperty->SetAmbient(1);
	volumeProperty->SetAmbient(0.5);


	volumeProperty->SetDiffuse(0.6);
	volumeProperty->SetSpecular(0.2);
	//volumeProperty->SetSpecularPower(10.0);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(1000.0, 1.0);
	//gradientOpacity->AddPoint(2000.0, 1.0);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	//scalarOpacity->AddPoint(-800.0, 0.0);
	//scalarOpacity->AddPoint(-750.0, 0.0);
	//scalarOpacity->AddPoint(-350.0, 0.0);
	//scalarOpacity->AddPoint(-300.0, 0.0);
	//scalarOpacity->AddPoint(-200.0, 0.0);
	scalarOpacity->AddPoint( 100.0, 1.0);
	scalarOpacity->AddPoint(1000.0, 1.0);
	scalarOpacity->AddPoint(1150.0, 0.0);
	//scalarOpacity->AddPoint(2750.0, 0.0);
	//scalarOpacity->AddPoint(2976.0, 0.0);
	//scalarOpacity->AddPoint(3000.0, 0.0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(-750.0, 0.08, 0.05, 0.03);
	color->AddRGBPoint(-350.0, 0.2, 0.25, 0.16);
	color->AddRGBPoint(0.0, 0.4, 0.4, 0.4);
	color->AddRGBPoint(1050.0, 0.60, 0.60, 0.60);
	color->AddRGBPoint(2000.0, 0.8, 0.8, 0.8);
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