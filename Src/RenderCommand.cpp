#include "RenderCommand.h"

#include <GL/glew.h>

//-----------------------------------------------------------------------------

void RenderCommand::Setup(
  const float* vertices, 
  const unsigned nVertices, 
  const unsigned* indices, 
  const unsigned _nIndices
)
{
  DeleteCurrent();

  LoadDataInGPU(vertices, nVertices, indices, _nIndices);
  LinkShaderAttributes();
}

//-----------------------------------------------------------------------------

void RenderCommand::LoadDataInGPU(
  const float* vertices, 
  const unsigned nVertices, 
  const unsigned* indices, 
  const unsigned _nIndices
)
{
  nIndices = _nIndices;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(float), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(unsigned), indices, GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------------

void RenderCommand::LinkShaderAttributes() {
  LinkVertexPositionAttribute();
  LinkVertexColorAttribute();
}

//-----------------------------------------------------------------------------

void RenderCommand::LinkVertexPositionAttribute() {
  constexpr unsigned totalVertexSize = 6 * sizeof(float);
  constexpr unsigned nFloatsPerPosition = 3;
  constexpr unsigned positionInputLocation = 0;
  glVertexAttribPointer(
    positionInputLocation, nFloatsPerPosition, GL_FLOAT,
    GL_FALSE, totalVertexSize, (void*)0
  );
  glEnableVertexAttribArray(positionInputLocation);
}

//-----------------------------------------------------------------------------

void RenderCommand::LinkVertexColorAttribute() {
  constexpr unsigned totalVertexSize = 6 * sizeof(float);
  constexpr unsigned nFloatsPerColor = 3;
  constexpr unsigned colorInputLocation = 1;
  glVertexAttribPointer(
    colorInputLocation, nFloatsPerColor, GL_FLOAT, GL_FALSE,
    totalVertexSize, (void*)(3 * sizeof(float))
  );
  glEnableVertexAttribArray(colorInputLocation);
}

//-----------------------------------------------------------------------------

void RenderCommand::DeleteCurrent() {
  if (VAO != 0) {
    glDeleteVertexArrays(1, &VAO); 
    VAO = 0;
  }
  if (VBO != 0) {
    glDeleteBuffers(1, &VBO); 
    VBO = 0;
  }
  if (EBO != 0) {
    glDeleteBuffers(1, &EBO); 
    EBO = 0;
  }

  nIndices = 0;
}

//-----------------------------------------------------------------------------

void RenderCommand::Execute(
  const Shader& shader, 
  const bool useWireframeMode
) 
{
  const unsigned polygonMode = useWireframeMode ? GL_LINE_STRIP : GL_TRIANGLES;

  glBindVertexArray(VAO);
  shader.Use();
  glDrawElements(polygonMode, nIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

//-----------------------------------------------------------------------------
