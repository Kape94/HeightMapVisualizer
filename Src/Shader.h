#ifndef _SHADER_H
#define _SHADER_H

#include "glm/mat4x4.hpp"

class Shader {
  public:
    void CreateProgram(
      const char* vertexShaderCode,
      const char* fragmentShaderCode
    );

    void DeleteProgram();

    void Use() const;

    void SetUniform(
      const char* uniformName,
      const glm::mat4x4& value
    ) const;

  private:
    unsigned CreateAndCompileShader(const char* code, const unsigned type);

    void CreateProgramWithShaders(
      const unsigned vertexShaderID,
      const unsigned fragmentShaderID
    );

    unsigned programID = 0;
};

#endif 
