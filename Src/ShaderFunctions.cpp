#include "ShaderFunctions.h"

#include <GL/glew.h>

#include "glm/gtc/type_ptr.hpp"

//-----------------------------------------------------------------------------

namespace Impl {
  unsigned CreateAndCompileShader(const char* code, const unsigned type);
  
  unsigned CreateProgram(
    const unsigned vertexShaderID, 
    const unsigned fragmentShaderID
  );
}

//-----------------------------------------------------------------------------
// ShaderFunctions
//-----------------------------------------------------------------------------

unsigned ShaderFunctions::CreateShader(
  const char* vertexShaderCode, 
  const char* fragmentShaderCode
)
{
  const unsigned vShaderID = Impl::CreateAndCompileShader(
    vertexShaderCode, GL_VERTEX_SHADER
  );
  const unsigned fShaderID = Impl::CreateAndCompileShader(
    fragmentShaderCode, GL_FRAGMENT_SHADER
  );
  
  return Impl::CreateProgram(vShaderID, fShaderID);
}

//-----------------------------------------------------------------------------

void ShaderFunctions::DeleteShader(const unsigned shaderID) {
  glDeleteProgram(shaderID);
}

//-----------------------------------------------------------------------------

void ShaderFunctions::UseShader(const unsigned shaderID) {
  glUseProgram(shaderID);
}

//-----------------------------------------------------------------------------

void ShaderFunctions::SetUniform(
  const unsigned shaderID, 
  const char* uniformName, 
  const glm::mat4x4& value
)
{
  const int loc = glGetUniformLocation(shaderID, uniformName);
  glProgramUniformMatrix4fv(shaderID, loc, 1, GL_FALSE, glm::value_ptr(value));
}

//-----------------------------------------------------------------------------
// Impl 
//-----------------------------------------------------------------------------

unsigned Impl::CreateAndCompileShader(const char* code, const unsigned type) {
  unsigned shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &code, nullptr);
  glCompileShader(shaderID);
  return shaderID;
}

//-----------------------------------------------------------------------------

unsigned Impl::CreateProgram(
  const unsigned vertexShaderID,
  const unsigned fragmentShaderID
)
{
  const unsigned programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return programID;
}

//-----------------------------------------------------------------------------
