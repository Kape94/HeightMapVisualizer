#include "BoundingBox.h"

#include <algorithm>
#include <limits>

//-----------------------------------------------------------------------------

BoundingBox::BoundingBox() : 
  minPoint(0.0f, 0.0f, 0.0f), maxPoint(0.0f, 0.0f, 0.0f) 
{
  Reset();
}

//-----------------------------------------------------------------------------

void BoundingBox::Reset() {
  constexpr float minFloat = std::numeric_limits<float>::lowest();
  constexpr float maxFloat = std::numeric_limits<float>::max();

  minPoint = { maxFloat, maxFloat, maxFloat };
  maxPoint = { minFloat, minFloat, minFloat };
}

//-----------------------------------------------------------------------------

void BoundingBox::Merge(const glm::vec3& point) {
  minPoint.x = std::min(minPoint.x, point.x);
  minPoint.y = std::min(minPoint.y, point.y);
  minPoint.z = std::min(minPoint.z, point.z);

  maxPoint.x = std::max(maxPoint.x, point.x);
  maxPoint.y = std::max(maxPoint.y, point.y);
  maxPoint.z = std::max(maxPoint.z, point.z);
}

//-----------------------------------------------------------------------------

const glm::vec3& BoundingBox::MinPoint() const {
  return minPoint;
}

//-----------------------------------------------------------------------------

const glm::vec3& BoundingBox::MaxPoint() const {
  return maxPoint;
}

//-----------------------------------------------------------------------------
