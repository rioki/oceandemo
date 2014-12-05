#version 330 core

uniform mat4 aProjection;
uniform mat4 aView;

in vec3 aVertex;

void main()
{
	gl_Position = aProjection * aView * vec4(aVertex, 1.0);
}