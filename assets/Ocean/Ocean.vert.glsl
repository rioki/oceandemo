#version 330 core

uniform mat4 aProjection;
uniform mat4 aView;

uniform sampler2D uNoise;
uniform float uTime;

in vec3 aVertex;

out vec2 vTexCoord;

void main()
{
    vTexCoord   = aVertex.xy;

    vec4 color = texture(uNoise, (aVertex.xy + vec2(uTime, 0)) / 64) / 4.0 + 
                 texture(uNoise, (aVertex.xy + vec2(-uTime, uTime)) / 64) / 4.0 +
                 texture(uNoise, (aVertex.xy + vec2(uTime, 0)) / 32) / 4.0 + 
                 texture(uNoise, (aVertex.xy + vec2(-uTime, uTime)) / 32) / 4.0;

    gl_Position = aProjection * aView * vec4(aVertex.xy, color.r * 3.0, 1.0);
}