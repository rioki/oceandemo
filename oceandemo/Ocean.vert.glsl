#version 330 core

in vec3 aVertex;

void main()
{
    gl_Position = vec4(aVertex, 1.0);
}