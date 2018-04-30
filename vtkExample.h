#ifndef FINALPROJECT_VTKEXAMPLE_H 
#define FINALPROJECT_VTKEXAMPLE_H

// VTK libraries used to render a 3D cylinder
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkCylinderSource.h>

class vtkExample{
public:
	vtkExample();
	//vtkRenderer(const nrrdFile&);
	void render();
private:
	vtkSmartPointer<vtkCylinderSource> cylinder;
	// The mapper is responsible for pushing the geometry into the graphics library.
  	// It may also do color mapping, if scalars or other attributes are defined.
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper;
	// The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
	vtkSmartPointer<vtkActor> cylinderActor;
	// The renderer generates the image
  	// which is then displayed on the render window.
	vtkSmartPointer<vtkRenderer> renderer;
	// The render window is the actual GUI window
  	// that appears on the computer screen
  	vtkSmartPointer<vtkRenderWindow> renderWindow;
  	// The render window interactor captures mouse events
  	// and will perform appropriate camera or actor manipulation
  	// depending on the nature of the events.
  	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
};

#endif