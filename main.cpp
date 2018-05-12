// FLTK libraries for a Hello World window
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

// Our custom ITK functions and classes

#include "dicomSeries.h"
#include "smoothing.h"

// Our custom VTK functions and classes

#include "vtkDicomRenderer.h"

int main(int argc, char** argv)
{
  if (argc < 2)
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " [DicomDirectory]";
    return 0;
    }

  // The target directory is the second argument entered at the command line
  char* dirName = argv[1];

  // Construct a new dicomSeries object from that directory
  dicomSeries* d = new dicomSeries(dirName);

  // TODO: Reader should not be public

  dicomSeries::ReaderType::Pointer reader = d->reader;

  // Declare smoothing and send files to be smoothed
  smoothing* smooth = new smoothing();
  smooth->applySmoothing(reader);

  //auto connector = itkVtkBridge(reader);

  vtkDicomRenderer v(reader);
  //vtkDicomRenderer v(dirName);
  v.render();

  // From the FLTK Hello World Window example
  Fl_Window *window = new Fl_Window(340,180);
  Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
  box->box(FL_UP_BOX);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labelsize(36);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv); 

  return 0;
}