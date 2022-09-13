#ifndef _RENDER_COMMAND_H
#define _RENDER_COMMAND_H

#include "Shader.h"

class RenderCommand {
  public:
    void Setup(
      const float* vertices,
      const unsigned nVertices,
      const unsigned* indices,
      const unsigned nIndices
    );

    void DeleteCurrent();

    void Execute(
      const Shader& shader,
      const bool useWireframeMode
    );

  private:

    void LoadDataInGPU(
      const float* vertices,
      const unsigned nVertices,
      const unsigned* indices,
      const unsigned _nIndices
    );

    void LinkShaderAttributes();
    void LinkVertexPositionAttribute();
    void LinkVertexColorAttribute();

    unsigned VAO = 0;
    unsigned VBO = 0;
    unsigned EBO = 0;
    unsigned nIndices = 0;
};

#endif 
