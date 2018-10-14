#pragma once

#include <chrono>
#include <array>

#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <common/loadShader.hpp>

class triangle
{
  GLuint programID;

  // This will identify our vertex buffer
  GLuint vertexbuffer;

  //  Model matrix
  glm::mat4 model;

public:

  triangle( glm::mat4 model = glm::translate( glm::identity<glm::mat4>()
                                            , glm::vec3{ 0.f, 0.f, -10.f }
                                            )
          )
  : programID (LoadShaders("shaders/vert.glsl" , "shaders/frag.glsl"))
  , model     (model)
  {
    using namespace std;

    // An array of 3 vectors which represents 3 vertices
    constexpr array<GLfloat, 9> g_vertex_buffer = { -1.0f, -1.0f, 0.0f
                                                  ,  1.0f, -1.0f, 0.0f
                                                  ,  0.0f,  1.0f, 0.0f
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

  void draw(const glm::mat4& proj_view)
  {
    model = glm::rotate(model, 0.03f, glm::vec3{0.f, 1.f, 0.f});

    auto pvm = proj_view * model;

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

    //  Binding matrix to a uniform value
    GLuint MatrixID = glGetUniformLocation(programID, "proj_view_mod");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &pvm[0][0]);

    //  Binding time to a uniform value
    GLuint TimeID = glGetUniformLocation(programID, "time");
    glUniform1f(TimeID, float(clock()));

    // Use our shader
    glUseProgram(programID);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0;
                                      // 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
  }
};
