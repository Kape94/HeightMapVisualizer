#include "VisualizerApp.h"

#include "CameraControlFunctions.h"
#include "Context.h"
#include "GLHelperFunctions.h"
#include "RenderCommand.h"
#include "ShaderCodes.h"
#include "ShaderFunctions.h"
#include "TerrainGenerator.h"

//-----------------------------------------------------------------------------

constexpr unsigned WIDTH = 1280;
constexpr unsigned HEIGHT = 960;

const char* VisualizerApp::heightMapFileName = nullptr;
unsigned VisualizerApp::shaderID = 0;
RenderCommand VisualizerApp::command;
Camera VisualizerApp::camera;
bool VisualizerApp::useWireframeMode = false;

//-----------------------------------------------------------------------------

void VisualizerApp::Exec(const char* fileName) {
  heightMapFileName = fileName;

  Context::Create(WIDTH, HEIGHT, InitializationFunc, RenderFunc);
  Context::SetMouseMotionFunc(HandleMouseMotion);
  Context::SetKeyboardFunc(HandleKeyPress);
  Context::Run();

  Cleanup();
}

//-----------------------------------------------------------------------------

void VisualizerApp::Cleanup() {
  command.DeleteCurrent();
  ShaderFunctions::DeleteShader(shaderID);
}

//-----------------------------------------------------------------------------

void VisualizerApp::InitializationFunc() {
  shaderID = ShaderFunctions::CreateShader(
    ShaderCodes::vertexShader, ShaderCodes::fragmentShader
  );

  TerrainGenerator generator;
  generator.Load(heightMapFileName);

  const BoundingBox terrainBoundingBox = generator.GetBoundingBox();
  camera.LookAt(terrainBoundingBox.MaxPoint(), terrainBoundingBox.MinPoint());
  
  const std::vector<float>& terrainVertices = generator.GetVertices();
  const std::vector<unsigned>& terrainIndices = generator.GetIndices();
  command.Setup(
    terrainVertices.data(), terrainVertices.size(),
    terrainIndices.data(), terrainIndices.size()
  );

  GLHelperFunctions::SetClearColor(0.0, 0.0, 0.0);
}

//-----------------------------------------------------------------------------

void VisualizerApp::RenderFunc() {
  GLHelperFunctions::Clear();

  const glm::mat4x4 viewMatrix = camera.CreateViewMatrix(WIDTH, HEIGHT);
  ShaderFunctions::SetUniform(shaderID, "viewMatrix", viewMatrix);

  command.Execute(shaderID, useWireframeMode);
  
  GLHelperFunctions::Flush();
}

//-----------------------------------------------------------------------------

void VisualizerApp::HandleMouseMotion(int x, int y) {
  CameraControlFunctions::HandleMouseMotion(x, y, WIDTH, HEIGHT, camera);
}

//-----------------------------------------------------------------------------

void VisualizerApp::HandleKeyPress(unsigned char key) {
  constexpr unsigned char keyESC = 27;
  if (key == keyESC) {
    Context::Exit();
  }
  if (key == 'q') {
    useWireframeMode = !useWireframeMode;
  }

  CameraControlFunctions::HandleKeyPress(key, camera);
}

//-----------------------------------------------------------------------------
