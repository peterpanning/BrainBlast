#include "dicomSeries.h"
#include "vtkDicomRenderer.h"
#include "itkToVtkBridge.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
      std::cout << "Usage: " << std::endl;
      std::cout << argv[0] << " [DicomDirectory]";
    return 0;
}

  // The target directory is the second argument entered at the command line
  char* dirName = argv[1];
  // Construct a new dicomSeries object from that directory
  dicomSeries* dicom = new dicomSeries(dirName);
  // Make a converter
  itkToVtkBridge* bridge = new itkToVtkBridge(dicom->RegionGrow());
  // Pass it to the renderer
  vtkDicomRenderer v(bridge->connector);
  // For demonstration purposes, render a version of the series without any changes
  // vtkDicomRenderer y(dirName);
  // y.render();
  // Render it
  v.render();
  return 0;
}
