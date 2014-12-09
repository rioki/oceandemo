
#version 330 core

uniform samplerCube uCubemap;

in vec3 vTexCoord;

out vec4 oFragColor;

void main()
{
    oFragColor = texture(uCubemap, vTexCoord);
}
