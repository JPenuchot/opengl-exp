#pragma once

#include <chrono>
#include <array>

#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <common/loadShader.hpp>

template<std::size_t N>
class simple_shape
{
  GLuint programID;

  // This will identify our vertex buffer
  GLuint vertexbuffer;

  //  Model matrix
  glm::mat4 model;

  // An array of 3 vectors which represents 3 vertices
  const std::array<GLfloat, N * 9> g_vertex_buffer;

public:

  simple_shape( const std::array<GLfloat, N * 9> g_vertex_buffer
              , const glm::mat4& model
              )
  : programID       (LoadShaders( "shaders/simple_shape.vert"
                                , "shaders/simple_shape.frag"
                                ))
  , model           (model)
  , g_vertex_buffer (g_vertex_buffer)
  {
    using namespace std;

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
    glDrawArrays(GL_TRIANGLES, 0, g_vertex_buffer.size() / 3);

    glDisableVertexAttribArray(0);
  }
};

template<std::size_t N>
auto make_simple_shape( const std::array<GLfloat, N> g_vertex_buffer
                      , const glm::mat4& model =
                          glm::translate( glm::identity<glm::mat4>()
                                        , glm::vec3{ 0.f, 0.f, -10.f }
                                        )
                      )
{
  static_assert(N % 9 == 0, "Wrong vertex amount.");
  return simple_shape<N / 9>{g_vertex_buffer, model};
}

//  Simple shape examples

using simple_triangle = simple_shape<1>;
using simple_cube     = simple_shape<12>;
