#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "glm/vec3.hpp"

class BoundingBox {
  public:
    BoundingBox();

    void Reset();
    void Merge(const glm::vec3& point);

    const glm::vec3& MinPoint() const;
    const glm::vec3& MaxPoint() const;

  private:
    glm::vec3 minPoint;
    glm::vec3 maxPoint;
};

#endif 
