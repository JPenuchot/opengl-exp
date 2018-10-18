#version 330 core

in vec3 fragment_color;

out vec3 color;

uniform float time;

void main()
{
  color = fragment_color;
}
