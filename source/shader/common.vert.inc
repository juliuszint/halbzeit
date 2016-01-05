
uniform mat4 pMatrix;
uniform mat4 mMatrix;
uniform mat3 nMatrix;

in vec4 vertexPosition;
in vec4 vertexNormal;
in vec4 vertexColor;

vec4 vPos() {return(pMatrix * mMatrix * vertexPosition);}
