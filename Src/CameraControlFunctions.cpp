#include "CameraControlFunctions.h"

#include "glm/gtc/matrix_transform.hpp"

//-----------------------------------------------------------------------------

namespace Impl {
  void ComputeCameraAxis(
    glm::vec3& xAxis, 
    glm::vec3& yAxis, 
    glm::vec3& zAxis, 
    const glm::vec3& cameraDir
  );
}

//-----------------------------------------------------------------------------
// InputHandlingFunctions
//-----------------------------------------------------------------------------

void CameraControlFunctions::HandleKeyPress(
  unsigned char key,
  Camera& camera
)
{
  glm::vec3 xAxis, yAxis, zAxis;
  Impl::ComputeCameraAxis(xAxis, yAxis, zAxis, camera.direction);

  glm::vec3 newPos = camera.position;
  constexpr glm::vec3 sensitivity(5.0f, 5.0f, 5.0f);
  if (key == 'a') {
    newPos = newPos + (xAxis * sensitivity);
  }
  if (key == 'd') {
    newPos = newPos - (xAxis * sensitivity);
  }
  if (key == 'w') {
    newPos = newPos + (zAxis * sensitivity);
  }
  if (key == 's') {
    newPos = newPos - (zAxis * sensitivity);
  }

  camera.position = newPos;
}

//-----------------------------------------------------------------------------

void CameraControlFunctions::HandleMouseMotion(
  const int x, 
  const int y, 
  const unsigned screenWidth,
  const unsigned screenHeight,
  Camera& camera
)
{
  glm::vec3 xAxis, yAxis, zAxis;
  Impl::ComputeCameraAxis(xAxis, yAxis, zAxis, camera.direction);

  const float sensitivity = 0.05;
  glm::mat4x4 rotation = glm::identity<glm::mat4x4>();
  if (x != 0) {
    const int adjustedX = x - (screenWidth / 2);
    rotation = glm::rotate(rotation, glm::radians((float)adjustedX * sensitivity), yAxis);
  }
  if (y != 0) {
    const int adjustedY = y - (screenHeight / 2);
    rotation = glm::rotate(rotation, glm::radians((float)adjustedY * sensitivity), xAxis);
  }

  glm::vec4 newCameraDir = glm::normalize(rotation * glm::vec4(camera.direction, 0.0));
  camera.direction = newCameraDir;
}

//-----------------------------------------------------------------------------
// Impl
//-----------------------------------------------------------------------------

void Impl::ComputeCameraAxis(
  glm::vec3& xAxis,
  glm::vec3& yAxis,
  glm::vec3& zAxis,
  const glm::vec3& cameraDir
)
{
  const glm::vec3 dir = glm::normalize(cameraDir);
  constexpr glm::vec3 temp{ 0.0, 1.0, 0.0 };

  xAxis = glm::normalize(glm::cross(temp, dir));
  const bool xAxisLenghtIsZero = glm::length(xAxis) < 0.0001;
  if (xAxisLenghtIsZero) {
    constexpr glm::vec3 newTemp{ 1.0, 0.0, 0.0 };
    xAxis = glm::normalize(glm::cross(newTemp, dir));
  }

  yAxis = glm::normalize(glm::cross(xAxis, dir));
  zAxis = dir;
}

//-----------------------------------------------------------------------------
