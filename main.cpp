// FLTK libraries for a Hello World window
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

// Our custom ITK functions and classes

#include "dicomSeries.h"

// Our custom VTK functions and classes

#include "vtkExample.h"


// Use of argc and argv here are from the FLTK Basics example http://www.fltk.org/doc-1.3/basics.html#basics_writing

int main(int argc, char** argv)
{
  // The target directory is the second argument entered at the command line
  char* dirName = argv[1];
  // Make a new dicomSeries from it
  dicomSeries dcm(dirName);
  // Write it to a new .nrrd file
  dcm.printSeries();
  dcm.to3D();

  vtkExample v;
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

  if (argc < 2)
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " [DicomDirectory]";
    std::cerr << "\nIf DicomDirectory is not specified, current directory is used\n";
    }

  return 0;
}