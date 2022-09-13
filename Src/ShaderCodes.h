#ifndef _SHADER_CODES_H
#define _SHADER_CODES_H

namespace ShaderCodes {
  const char* vertexShader = R"(
    #version 330

    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec3 col;

    out vec3 color;

    uniform mat4 viewMatrix;

    void main() {
      gl_Position = viewMatrix * vec4(pos, 1.0);
      color = col;
    }
  )";

  const char* fragmentShader = R"(
    #version 330

    in vec3 color;

    out vec4 fragColor;

    void main() {
      fragColor = vec4(color, 1.0);
    }
  )";
}

#endif 
