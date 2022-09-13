#ifndef _VISUALIZER_APP_H
#define _VISUALIZER_APP_H

#include "Camera.h"
#include "RenderCommand.h"

class VisualizerApp {
  public:
    VisualizerApp() = delete;

    static void Exec(const char* fileName);

  private:

    static void InitializationFunc();
    static void RenderFunc();
    static void HandleMouseMotion(int x, int y);
    static void HandleKeyPress(unsigned char key);

    static void Cleanup();
    
    static const char* heightMapFileName;
    static RenderCommand command;
    static unsigned shaderID;
    static Camera camera;
    static bool useWireframeMode;
};

#endif 
