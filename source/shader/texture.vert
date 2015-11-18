#version 330
in vec4 vertexPosition;
in vec4 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform mat4 pMatrix;
uniform mat4 mMatrix;
uniform mat3 nMatrix;

out vec2 texCoords;

void main()
{
    gl_Position = pMatrix * mMatrix * vertexPosition;

    texCoords=textureCoords;
}
