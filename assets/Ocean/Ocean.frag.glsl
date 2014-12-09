#version 330 core

uniform sampler2D uNoise;
uniform float uTime;

in vec2 vTexCoord;

out vec4 oFragColor;

void main()
{
    //vec4 color = texture(uNoise, vTexCoord + uTime) / 4.0 + 
    //             texture(uNoise, (vTexCoord + uTime) / 32) / 4.0 + 
    //             texture(uNoise, (vTexCoord + uTime) / 64) / 4.0 + 
    //             texture(uNoise, (vTexCoord + uTime) / 128) / 4.0;

    vec4 color = texture(uNoise, (vTexCoord + vec2(uTime, 0)) / 64) / 4.0 + 
                 texture(uNoise, (vTexCoord + vec2(-uTime, uTime)) / 64) / 4.0 +
                 texture(uNoise, (vTexCoord + vec2(uTime, 0)) / 32) / 4.0 + 
                 texture(uNoise, (vTexCoord + vec2(-uTime, uTime)) / 32) / 4.0;

    oFragColor = color;
}