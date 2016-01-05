#version 330
in vec4 vertexPosition;
in vec4 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform mat4 pMatrix;
uniform mat4 mMatrix;
uniform mat3 nMatrix;

out vec3 texCoords;

void main()
{
    gl_Position = pMatrix * mMatrix * vertexPosition;
    vec3 temptexcoords = vec3(vertexPosition);

    //Die Koordinatenachsen bei OpenGL Cubemaps stimmen nicht mit den typischen Cubemaps (Renderman, DirectX, ...) überein
    //siehe hierzu GLSpec 4.5 Core, Seite 240

    texCoords = vec3(vertexPosition.x, -vertexPosition.yz);
}
