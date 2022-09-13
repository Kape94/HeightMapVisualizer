#include "Context.h"

// glew must be included before freeglut!
#include <GL/glew.h>

#include <GL/freeglut.h>

//-----------------------------------------------------------------------------

namespace Impl {
  unsigned SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;

  void InitGlut();
  void InitContext();
  void CreateGlutWindow(const unsigned width, const unsigned height);
  void InitGlew();

  void SetupOpenGL(const unsigned width, const unsigned height);

  Context::Callback renderFunction;
  void GlutRenderFunction();

  void (*motionFunction)(int, int);
  void GlutMouseMotionFunction(int x, int y);

  void (*keyboardFunction)(unsigned char);
  void GlutKeyboardFunction(unsigned char key, int x, int y);
}

//-----------------------------------------------------------------------------
// Context
//-----------------------------------------------------------------------------

void Context::Create(
  const unsigned width, 
  const unsigned height, 
  Callback init, 
  Callback render
) 
{
  Impl::SCREEN_WIDTH = width;
  Impl::SCREEN_HEIGHT = height;

  Impl::InitGlut();
  Impl::InitContext();
  Impl::CreateGlutWindow(width, height);
  Impl::InitGlew();

  Impl::SetupOpenGL(width, height);

  init();

  Impl::renderFunction = render;
  glutDisplayFunc(Impl::GlutRenderFunction);
}

//-----------------------------------------------------------------------------

void Context::SetMouseMotionFunc(void (*motionFunc)(int, int)) {
  Impl::motionFunction = motionFunc;
  glutPassiveMotionFunc(Impl::GlutMouseMotionFunction);
}

//-----------------------------------------------------------------------------

void Context::SetKeyboardFunc(void(*keyboardFunc)(unsigned char)) {
  Impl::keyboardFunction = keyboardFunc;
  glutKeyboardFunc(Impl::GlutKeyboardFunction);
}

//-----------------------------------------------------------------------------

void Context::Run() {
  glutMainLoop();
  glutSwapBuffers();
}

//-----------------------------------------------------------------------------

void Context::Exit()
{
  glutLeaveMainLoop();
}

//-----------------------------------------------------------------------------
// Impl
//-----------------------------------------------------------------------------

void Impl::InitGlut() {
  int argcDummy = 0;
  char** argvDummy = nullptr;
  glutInit(&argcDummy, argvDummy);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}

//-----------------------------------------------------------------------------

void Impl::InitContext() {
  glutInitContextVersion(3, 3);
  glutInitContextFlags(GLUT_CORE_PROFILE);
  glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
}

//-----------------------------------------------------------------------------

void Impl::CreateGlutWindow(const unsigned width, const unsigned height) {
  glutInitWindowSize(width, height);
  glutCreateWindow("Visualizer");
  glutFullScreen();
  glutWarpPointer(width / 2, height / 2);
}

//-----------------------------------------------------------------------------

void Impl::InitGlew() {
  glewExperimental = GL_TRUE;
  glewInit();
}

//-----------------------------------------------------------------------------

void Impl::SetupOpenGL(const unsigned width, const unsigned height) {
  glViewport(0, 0, width, height);

  glEnable(GL_DEPTH_TEST);
}

//-----------------------------------------------------------------------------

void Impl::GlutRenderFunction() {
  renderFunction();
  glutSwapBuffers();
}

//-----------------------------------------------------------------------------

void Impl::GlutMouseMotionFunction(int x, int y) {
  motionFunction(x, y);
  glutPostRedisplay();
  glutWarpPointer(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

//-----------------------------------------------------------------------------

void Impl::GlutKeyboardFunction(unsigned char key, int x, int y) {
  keyboardFunction(key);
  glutPostRedisplay();
}

//-----------------------------------------------------------------------------
