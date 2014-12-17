#version 330 core

// FIXME -> uProjetionMatrix
uniform mat4 aProjection;
uniform mat4 aView;
uniform mat4 uModelMatrix;
uniform mat4 uTextureMatrix;

uniform float uRockMin;
uniform float uRockMax;

uniform sampler2D uGround;

in vec3 aVertex;
in vec2 aTexCoord;

out vec2 vTexCoord;

void main()
{    
    // WHY U NO TRANSLATE?!
    //vec2 tc      = (uTextureMatrix * vec4(aTexCoord, 0.0f, 0.0f)).xy;
    vec2 tc      = (uTextureMatrix * vec4(aTexCoord, 0.0f, 0.0f)).xy + vec2(uTextureMatrix[3][0], uTextureMatrix[3][1]);

    float rockDst = uRockMax - uRockMin;
    float height  = texture(uGround, tc).x * rockDst + uRockMin;

    vTexCoord    = tc;
    gl_Position  = aProjection * aView * uModelMatrix * vec4(aVertex.xy, height, 1.0);
}