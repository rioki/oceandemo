#version 330 core

uniform sampler2D uGround;
uniform float uTime;

in vec2 vTexCoord;

out vec4 oFragColor;

void main()
{
    oFragColor =  texture(uGround, vTexCoord);    
}