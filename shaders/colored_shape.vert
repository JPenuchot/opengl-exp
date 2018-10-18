#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;

out vec3 fragment_color;

// Values that stay constant for the whole mesh.
uniform mat4 proj_view_mod;
uniform float time;

void main()
{
  gl_Position = proj_view_mod * vec4(vertexPosition_modelspace, 1.f);
  fragment_color = vertexColor;
}
