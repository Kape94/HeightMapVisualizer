#include "TerrainGenerator.h"

#include "ErrorHandling.h"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

//-----------------------------------------------------------------------------

void TerrainGenerator::Load(const char* fileName) {
  LoadImageData(fileName);

  GenerateMeshVerticesAndComputeBoundingBox();
  GenerateMeshIndices();

  FreeImageData();
}

//-----------------------------------------------------------------------------

void TerrainGenerator::LoadImageData(const char* fileName) {
  imageData = stbi_load(
    fileName, &imageWidth, &imageHeight, &nChannels, 0
  );

  if (imageData == nullptr) {
    std::string error = "Couldn't open the file ";
    error += fileName;
    ErrorHandling::ExitWithErrorMessage(error.c_str());
  }
}

//-----------------------------------------------------------------------------

void TerrainGenerator::GenerateMeshVerticesAndComputeBoundingBox() {
  boundingBox.Reset();

  vertices.clear();
  vertices.reserve(6 * imageWidth * imageHeight);

  for (unsigned i = 0; i < imageHeight; ++i) {
    for (unsigned j = 0; j < imageWidth; ++j) {
      unsigned char y = imageData[(j + (i * imageWidth)) * nChannels];

      const float scaledY = (float)y * 0.5;
      const glm::vec3 vertexPoint((float)i, scaledY, (float)j);
      vertices.push_back(vertexPoint.x);
      vertices.push_back(vertexPoint.y);
      vertices.push_back(vertexPoint.z);

      boundingBox.Merge(vertexPoint);

      const float color = 0.2f + 0.8f * ((float)y / 256.0f);
      vertices.push_back(color);
      vertices.push_back(color);
      vertices.push_back(color);
    }
  }
}

//-----------------------------------------------------------------------------

void TerrainGenerator::GenerateMeshIndices() {
  indices.clear();
  indices.reserve(6 * imageWidth * imageHeight);
  for (unsigned i = 0; i < imageHeight - 1; ++i) {
    for (unsigned j = 0; j < imageWidth - 1; ++j) {
      const unsigned widthOffset = i * imageWidth;
      const unsigned nextLineWidthOffset = (i + 1) * imageWidth;

      const unsigned topLeftIndex = widthOffset + j;
      const unsigned bottomLeftIndex = nextLineWidthOffset + j;
      const unsigned topRightIndex = widthOffset + j + 1;
      const unsigned bottomRightIndex = nextLineWidthOffset + j + 1;

      indices.push_back(topLeftIndex);
      indices.push_back(bottomLeftIndex);
      indices.push_back(topRightIndex);

      indices.push_back(topRightIndex);
      indices.push_back(bottomRightIndex);
      indices.push_back(bottomLeftIndex);
    }
  }
}

//-----------------------------------------------------------------------------

void TerrainGenerator::FreeImageData() {
  stbi_image_free(imageData);
}

//-----------------------------------------------------------------------------

const std::vector<float>& TerrainGenerator::GetVertices() const {
  return vertices;
}

//-----------------------------------------------------------------------------

const std::vector<unsigned>& TerrainGenerator::GetIndices() const {
  return indices;
}

//-----------------------------------------------------------------------------

const BoundingBox& TerrainGenerator::GetBoundingBox() const {
  return boundingBox;
}

//-----------------------------------------------------------------------------
