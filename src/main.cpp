#include <iostream>
#include <vector>
#include <array>

// Include GLEW. Always include it before gl.h and glfw3.h,
// since it's a bit magic.
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Shader loading
#include <common/loadShader.hpp>

#include <render/entities/triangle.hpp>

int main()
{
  using namespace glm;
  using namespace std;

  /*
   * GLFW INIT
   */

  if(!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << endl;
    return -1;
  }

  glewExperimental = true; // Needed for core profile

  // 4x antialiasing
  glfwWindowHint(GLFW_SAMPLES, 4);

  // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context

  // (In the accompanying source code, this variable is global for simplicity)
  GLFWwindow* window;
  window = glfwCreateWindow(3200, 1800, "Tuto ça tourne mal", NULL, NULL);

  if(!window)
  {
    cerr << "Failed to open GLFW window. If you have an Intel GPU,"
        " " "they are not 3.3 compatible. Try the 2.1 version of the tutorials."
         << endl;

    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  /*
   * GLEW INIT
   */

  if(glewInit() != GLEW_OK)
  {
    cout << "Failed to initialize GLEW" << endl;
    return -1;
  }

  //  Creating then binding our vertex array
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  //  Declaring our triangle
  triangle tr;

  //  Moves objects from world to view coordinates
  auto view_mat = glm::lookAt ( glm::vec3{  0.f,  0.f,  5.f } //  Eye
                              , glm::vec3{  0.f,  0.f, -1.f } //  Center
                              , glm::vec3{  0.f,  1.f,  0.f } //  Up
                              );

  //  Projection matrix, yo
  auto proj_mat = glm::perspective
    ( glm::radians(90.f)  // The vertical Field of View, in radians.
    , 16.f / 9.f          // Aspect Ratio. Depends on the size of your window.
    , 0.1f                // Near clipping plane. Keep as big as possible,
                          // or you'll get precision issues.
    , 100.0f              // Far clipping plane. Keep as little as possible.
    );

  do
  {
    //  Clearing buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Making dat proj + view matrix
    auto proj_view_mat = proj_mat * view_mat;

    //  Drawing our triangle
    tr.draw(proj_view_mat);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // Check if the ESC key was pressed or the window was closed
  while (  glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0
        );
}
