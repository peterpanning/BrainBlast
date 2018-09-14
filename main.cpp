// FLTK libraries for a Hello World window
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

// Our custom ITK functions and classes
#include "dicomSeries.h"

// Our custom VTK functions and classes
#include "vtkDicomRenderer.h"
#include "itkToVtkBridge.h"

int main(int argc, char** argv)
{
  if (argc != 2)
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " [DicomDirectory]";
    return 0;
    }

  // The target directory is the second argument entered at the command line
  char* dirName = argv[1];
  // Construct a new dicomSeries object from that directory
  dicomSeries* d = new dicomSeries(dirName);
  // Make a converter
  itkToVtkBridge* bridge = new itkToVtkBridge(d->RegionGrow());
  // Pass it to the renderer
  vtkDicomRenderer v(bridge->connector);
  // For fun, render a version of the series without any changes
  vtkDicomRenderer y(dirName);
  y.render();
  // Render it
  v.render();
  return 0;
}