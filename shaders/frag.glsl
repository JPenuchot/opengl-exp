#version 330 core

out vec3 color;

uniform float time;

void main()
{
  float time_reduced = time * .0001f;
  color = vec3( sin(time_reduced) * 1.f
              , sin(time_reduced + 3.14) * 1.f
              , sin(time_reduced * .5 + 1.07) * 1.f
              );
}
