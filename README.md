# Height Map Visualizer

This is a simple tool for height maps visualization. The application takes a file name, which is the height map image, a generates a mesh colored in gray scale. The user can fly through the scene to see the generated terrain.

This project was developed in OpenGL with the following libs: freeGLUT, GLEW, std_image and glm.

## Installation

In order to install the deps and build this project, you need to have the git tool installed in your machine.

To install and build this application, execute this steps:
  - Run the "Install.bat" script, it will install all the deps used by this project. 
  - Run the "Build.bat" script, it will generate a project with CMake.

## How to use de application

To use the application you just need to call the command: 

HeightMapVisualizer.exe \<imageFileName\>

For example:

HeightMapVisualizer.exe C:/Temp/iceland_heightmap.png
  
The application will generate a scene from the input height map, and you can use the following commands:
  - Keys W, A, S, D: move the camera position;
  - Mouse move: move the camera direction;
  - Key Q: switch on/off the wireframe mode;
  - Key ESC: Close the application
 
Enjoy! :)
