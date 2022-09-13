#ifndef _CAMERA_H
#define _CAMERA_H

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

class Camera {
  public:

    void LookAt(const glm::vec3& eye, const glm::vec3& target);
    glm::mat4x4 CreateViewMatrix(
      const unsigned screenWidth, 
      const unsigned screenHeight
    );

    glm::vec3 position;
    glm::vec3 direction;
};

#endif 
