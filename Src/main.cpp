#include "ErrorHandling.h"
#include "VisualizerApp.h"

int main(int argc, char** argv) {
  
  if (argc != 2) {
    ErrorHandling::ExitWithErrorMessage(
      "Incorrect number of arguments. \nUsage: HeightMapVisualizer.exe <imageFileName>"
    );
  }

  const char* fileName = argv[1];
  VisualizerApp::Exec(fileName);
  
  return 0;
}
