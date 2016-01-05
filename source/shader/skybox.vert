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
    vec4 positionWithoutTranslation;
    mat4 pMatrixWoT = pMatrix, mMatrixWoT = mMatrix;
    pMatrixWoT[3] = vec4(0.,0.,0.,1.);
    mMatrixWoT[3] = vec4(0.,0.,0.,1.);
    positionWithoutTranslation = pMatrixWoT * mMatrixWoT * vertexPosition;
    gl_Position = positionWithoutTranslation;

    vec3 temptexcoords = vec3(vertexPosition);

    //Die Koordinatenachsen bei OpenGL Cubemaps stimmen nicht mit den typischen Cubemaps (Renderman, DirectX, ...) überein
    //siehe hierzu GLSpec 4.5 Core, Seite 240

    texCoords = vec3(vertexPosition.x, -vertexPosition.yz);
}
