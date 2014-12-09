#version 330 core

uniform mat4 aProjection;
uniform mat4 aView;

in vec3 aVertex;

out vec3 vTexCoord;

void main()
{
    mat4 invProjection = inverse(aProjection);
    mat3 invView       = inverse(mat3(aView));    

    vTexCoord   = (invView * (invProjection * vec4(aVertex, 1.0)).xyz).xzy;
    gl_Position = vec4(aVertex, 1.0);
}
