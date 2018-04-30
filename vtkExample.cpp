#include "vtkExample.h"

vtkExample::vtkExample() {
  // This creates a polygonal cylinder model with eight circumferential facets
  // (i.e, in practice an octagonal prism).
  cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetResolution(8);

  cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

  // Here we set the actor's color and rotate it around the X and Y axes.
  cylinderActor = vtkSmartPointer<vtkActor>::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  cylinderActor->RotateX(30.0);
  cylinderActor->RotateY(-45.0);

  // The renderer can be thought of as a scene to which the actor is added
  renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(cylinderActor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  // Zoom in a little by accessing the camera and invoking its "Zoom" method.
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  // The actual window that appears on the computer screen
  renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(200, 200);
  renderWindow->AddRenderer(renderer);

  // The render window interactor captures mouse events
  // and will perform appropriate camera or actor manipulation
  // depending on the nature of the events.
  renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
}

void vtkExample::render(){
  // This starts the event loop and as a side effect causes an initial render.
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Start();
}

  