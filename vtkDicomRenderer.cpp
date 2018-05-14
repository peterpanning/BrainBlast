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

	std::cout << "Copying image data...\n";

	imageData->DeepCopy(connector->GetOutput());

	std::cout << "Generating surfact...\n";

	surface->SetInputData(imageData);
	surface->ComputeNormalsOn();
	surface->SetValue(0,180);

	std::cout << "Initializing Renderer...\n";

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

	// Good shading makes an object look more 3D
	volumeProperty->ShadeOn();

	// Setting interpolation to linear allows for "high-quality rendering" 
	//https://www.vtk.org/Wiki/VTK/Examples/Cxx/Medical/MedicalDemo4
	volumeProperty->SetInterpolationTypeToLinear();

	// Ambient property is inversely related to shading impact
	// It's the amount of ambient light in the scene
	volumeProperty->SetAmbient(0.5);

	// Diffuse and specular are directly related to shading impact
	// Higher diffuse highlights seems to highlight finer details
	volumeProperty->SetDiffuse(.4);
	// Higher specular seemed to emphasize shadows and 
	// divisions between regions.  
	volumeProperty->SetSpecular(.6);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(90, .5);
	gradientOpacity->AddPoint(100.0, 1);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	// Grey matter has intensities between 25 and 45
	scalarOpacity->AddPoint(0, 0.0);
	scalarOpacity->AddPoint(25, .75);
	scalarOpacity->AddPoint(45, .75);

	// Most flesh has intensities between 500 and 1000 according to 
	// https://www.paraview.org/Wiki/VTK/Examples/Cxx/Medical/MedicalDemo4
	scalarOpacity->AddPoint(500.0, 0);
	scalarOpacity->AddPoint(1500.0, 0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(0.0, 0.8, 0.2, 0.2);
	color->AddRGBPoint(500.0, .8, .2, .2);
	volumeProperty->SetColor(color);

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();
	return;
}

void vtkDicomRenderer::render(){
  // This starts the event loop and as a side effect causes an initial render.
  std::cout << "Rendering!\n";
  renderWindow->Render();
  renderWindowInteractor->Start();
}