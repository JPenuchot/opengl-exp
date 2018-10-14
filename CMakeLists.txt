cmake_minimum_required(VERSION 2.8.9)
project(prog)
find_package(PkgConfig REQUIRED)

# Adding compiler optimizations

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Prefer vendor OpenGL over legacy version
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenCV REQUIRED)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

# Adding includes

include_directories(
  "include/"
  ${OPENGL_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
)

# Linking libraries

link_libraries(
  ${OpenCV_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${GLEW_LIBRARIES}
)

# Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
