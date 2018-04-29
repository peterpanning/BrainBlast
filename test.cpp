// VTK libraries for building the example program 
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>

// FLTK libraries for a Hello World window
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

// ITK libraries for a simple hello world program. Unclear why they can be referenced with quotes rather than brackets. 
#include "itkImage.h"

// Use of argc and argv here are from the FLTK Basics example http://www.fltk.org/doc-1.3/basics.html#basics_writing

int main(int argc, char **argv)
{
  // From the ITK Hello World example
  typedef itk::Image<unsigned short, 3> ImageType;
  ImageType::Pointer image = ImageType::New();  

  // From the FLTK Hello World Window example

  Fl_Window *window = new Fl_Window(340,180);
  Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
  box->box(FL_UP_BOX);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labelsize(36);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);

  // From the VTK Hello World example

  // This creates a polygonal cylinder model with eight circumferential facets
  // (i.e, in practice an octagonal prism).
  vtkSmartPointer<vtkCylinderSource> cylinder =
    vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetResolution(8);

  // The mapper is responsible for pushing the geometry into the graphics library.
  // It may also do color mapping, if scalars or other attributes are defined.
  vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

  // The actor is a grouping mechanism: besides the geometry (mapper), it
  // also has a property, transformation matrix, and/or texture map.
  // Here we set its color and rotate it around the X and Y axes.
  vtkSmartPointer<vtkActor> cylinderActor =
    vtkSmartPointer<vtkActor>::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  cylinderActor->RotateX(30.0);
  cylinderActor->RotateY(-45.0);

  // The renderer generates the image
  // which is then displayed on the render window.
  // It can be thought of as a scene to which the actor is added
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(cylinderActor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  // Zoom in a little by accessing the camera and invoking its "Zoom" method.
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);

  // The render window is the actual GUI window
  // that appears on the computer screen
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(200, 200);
  renderWindow->AddRenderer(renderer);

  // The render window interactor captures mouse events
  // and will perform appropriate camera or actor manipulation
  // depending on the nature of the events.
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // This starts the event loop and as a side effect causes an initial render.
  renderWindowInteractor->Start();

  // From the FLTK Hello World Window tutorial
  return Fl::run();

}