#pragma once

#include <array>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <common/loadShader.hpp>

class triangle
{
  GLuint programID;

  // This will identify our vertex buffer
  GLuint vertexbuffer;

  //  Model matrix
  glm::mat4 model_mat = glm::translate(glm::mat4{}, glm::vec3{1.f, 0.f, 0.f});

public:

  triangle()
  : programID(LoadShaders("shaders/vert.glsl" , "shaders/frag.glsl"))
  {
    using namespace std;

    // An array of 3 vectors which represents 3 vertices
    constexpr array<GLfloat, 3 * 8> g_vertex_buffer =
        // front
      { -1.f, -1.f,  1.f
      ,  1.f, -1.f,  1.f
      ,  1.f,  1.f,  1.f
      , -1.f,  1.f,  1.f
        // back
      , -1.f, -1.f, -1.f
      ,  1.f, -1.f, -1.f
      ,  1.f,  1.f, -1.f
      , -1.f,  1.f, -1.f
      };

    array<GLushort, 4 * 6 * 3> cube_elements =
      { 0, 1, 2, /**/ 2, 3, 0 // front
      , 1, 5, 6, /**/ 6, 2, 1 // right
      , 7, 6, 5, /**/ 5, 4, 7 // back
      , 4, 0, 3, /**/ 3, 7, 4 // left
      , 4, 5, 1, /**/ 1, 0, 4 // bottom
      , 3, 2, 6, /**/ 6, 7, 3 // top
      };

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Give our vertices to OpenGL.
    glBufferData( GL_ARRAY_BUFFER
                , g_vertex_buffer.size() * sizeof(GLfloat)
                , g_vertex_buffer.data()
                , GL_STATIC_DRAW
                );
  }

  void draw()
  {
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer ( 0         // attribute 0. No particular reason
                                      // for 0, but must match the layout
                                      // in the shader.
                          , 3         // size
                          , GL_FLOAT  // type
                          , GL_FALSE  // normalized?
                          , 0         // stride
                          , (void*)0  // array buffer offset
                          );

    // Use our shader
    glUseProgram(programID);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0;
                                      // 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
  }
};
