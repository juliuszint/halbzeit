#sginclude "://shader/commonlightmatdefs.inc"

float phongKd(vec3 light, vec3 normal)
{
    return(max(dot(light, normal), 0.0));
}

float phongKs(vec3 view, vec3 reflect, Material m)
{
    return(pow(max(dot(view, reflect), 0.0), material.shininess));
}

float phongKa()
{
    return(1.0);
}

vec4 phongKdKaColor(vec3 light, vec3 view, vec3 normal, Material m, Light l)
{
    vec4 d=phongKd(normal, light)*l.diffuse*m.diffuse;
    vec4 a=phongKa()*l.ambient*m.ambient;
    return(d+a);
}

vec4 phong(vec3 light, vec3 view, vec3 normal, Material m, Light l)
{
    vec4 s=phongKs(view, -reflect(light,normal), m)*l.specular*m.specular;
    return(phongKdKaColor(light, view, normal, m, l)+s);
}
