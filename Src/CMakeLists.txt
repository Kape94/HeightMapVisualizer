cmake_minimum_required(VERSION 3.22)
project(HeightMapVisualizer)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB SRC_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE GLUT::GLUT)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)


