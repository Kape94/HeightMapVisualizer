#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

//-----------------------------------------------------------------------------

namespace Impl {
  glm::mat4x4 CreatePerspectiveMatrix(
    const unsigned screenWidth, 
    const unsigned screenHeight
  );

  glm::mat4x4 CreateLookAtMatrix(
    const glm::vec3& position, 
    const glm::vec3& direction
  );
}

//-----------------------------------------------------------------------------

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target) {
  position = eye;
  direction = glm::normalize(target - eye);
}

//-----------------------------------------------------------------------------

glm::mat4x4 Camera::CreateViewMatrix(
  const unsigned screenWidth, 
  const unsigned screenHeight
)
{
  const glm::mat4x4 projection = Impl::CreatePerspectiveMatrix(
    screenWidth, screenHeight
  );
  const glm::mat4x4 view = Impl::CreateLookAtMatrix(position, direction);

  return projection * view;
}

//-----------------------------------------------------------------------------

glm::mat4x4 Impl::CreatePerspectiveMatrix(
  const unsigned screenWidth,
  const unsigned screenHeight
)
{
  constexpr float fieldOfView = glm::radians(60.0f);
  const float aspect = static_cast<float>(screenWidth / screenHeight);
  const float near = 0.1f;
  const float far = 10000.0f;

  return glm::perspective(fieldOfView, aspect, near, far);
}

//-----------------------------------------------------------------------------

glm::mat4x4 Impl::CreateLookAtMatrix(
  const glm::vec3& position,
  const glm::vec3& direction
)
{
  constexpr glm::vec3 directionStep(10.0, 10.0, 10.0);
  const glm::vec3 targetPoint = position + (direction * directionStep);
  constexpr glm::vec3 up(0.0f, 1.0f, 0.0f);

  return glm::lookAt(position, targetPoint, up);
}

//-----------------------------------------------------------------------------
