#version 330
#sginclude "://shader/commonlight.vert.inc"

out vec4 color;

void main()
{
    float factor = 1.0;
    gl_Position = vPos();

    color = lambert();
}
