#ifndef _CAMERA_CONTROL_FUNCTIONS_H
#define _CAMERA_CONTROL_FUNCTIONS_H

#include "Camera.h"

namespace CameraControlFunctions {
  
  void HandleKeyPress(
    unsigned char key,
    Camera& camera
  );

  void HandleMouseMotion(
    const int x,
    const int y,
    const unsigned screenWidth,
    const unsigned screenHeight,
    Camera& camera
  );

}

#endif 
