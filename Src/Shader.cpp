#include "Shader.h"

#include <GL/glew.h>

#include "glm/gtc/type_ptr.hpp"

//-----------------------------------------------------------------------------

void Shader::CreateProgram(
  const char* vertexShaderCode, 
  const char* fragmentShaderCode
)
{
  const unsigned vShaderID = CreateAndCompileShader(
    vertexShaderCode, GL_VERTEX_SHADER
  );
  const unsigned fShaderID = CreateAndCompileShader(
    fragmentShaderCode, GL_FRAGMENT_SHADER
  );

  CreateProgramWithShaders(vShaderID, fShaderID);
}

//-----------------------------------------------------------------------------

void Shader::DeleteProgram() {
  glDeleteProgram(programID);
  programID = 0;
}

//-----------------------------------------------------------------------------

void Shader::Use() const {
  glUseProgram(programID);
}

//-----------------------------------------------------------------------------

void Shader::SetUniform(
  const char* uniformName, 
  const glm::mat4x4& value
) const
{
  const int loc = glGetUniformLocation(programID, uniformName);
  glProgramUniformMatrix4fv(programID, loc, 1, GL_FALSE, glm::value_ptr(value));
}

//-----------------------------------------------------------------------------

unsigned Shader::CreateAndCompileShader(const char* code, const unsigned type) {
  unsigned shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &code, nullptr);
  glCompileShader(shaderID);
  return shaderID;
}

//-----------------------------------------------------------------------------

void Shader::CreateProgramWithShaders(
  const unsigned vertexShaderID, 
  const unsigned fragmentShaderID
)
{
  programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

//-----------------------------------------------------------------------------
