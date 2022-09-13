#ifndef _SHADER_FUNCTIONS_H
#define _SHADER_FUNCTIONS_H

#include "glm/mat4x4.hpp"

namespace ShaderFunctions {
  unsigned CreateShader(
    const char* vertexShaderCode,
    const char* fragmentShaderCode
  );

  void DeleteShader(const unsigned shaderID);

  void UseShader(const unsigned shaderID);

  void SetUniform(
    const unsigned shaderID, 
    const char* uniformName, 
    const glm::mat4x4& value
  );
}

#endif 
