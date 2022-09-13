#ifndef _TERRAIN_GENERATOR_H
#define _TERRAIN_GENERATOR_H

#include <vector>

#include "BoundingBox.h"

class TerrainGenerator {
  public:
    
    void Load(const char* fileName);

    const std::vector<float>& GetVertices() const;
    const std::vector<unsigned>& GetIndices() const;
    const BoundingBox& GetBoundingBox() const;

  private:

    void LoadImageData(const char* fileName);
    void FreeImageData();
    void GenerateMeshVerticesAndComputeBoundingBox();
    void GenerateMeshIndices();

    unsigned char* imageData = nullptr;
    int imageWidth = 0;
    int imageHeight = 0;
    int nChannels = 0;

    std::vector<float> vertices;
    std::vector<unsigned> indices;
    BoundingBox boundingBox;
};

#endif 
