#include "GLHelperFunctions.h"

#include <GL/glew.h>

//-----------------------------------------------------------------------------

void GLHelperFunctions::SetClearColor(
  const float r, const float g, const float b
)
{
  glClearColor(r, g, b, 1.0);
}

//-----------------------------------------------------------------------------

void GLHelperFunctions::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-----------------------------------------------------------------------------

void GLHelperFunctions::Flush() {
  glFlush();
}

//-----------------------------------------------------------------------------
