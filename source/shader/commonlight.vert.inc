#sgdefine COMMONLIGHT_VERT_INC //Define setzen um Mehrfache inkludierung auszuschliessen

#sginclude "://shader/common.vert.inc"
#sginclude "://shader/commonlightmatdefs.inc"
#sginclude "://shader/commonlightmodels.inc"

vec3 eyePosition() {return(mMatrix * vertexPosition).xyz;}
vec3 eyeLightPos() {return(lights[0].position.xyz);}
vec3 eyeNormalVec() {return(normalize(nMatrix * vertexNormal.xyz));}
vec3 eyeLightVec() {return(normalize(eyeLightPos().xyz - eyePosition().xyz));}
vec3 eyeViewVec() {return(-normalize(eyePosition().xyz));}
vec3 eyeReflectVec() {return(-reflect(eyeLightVec(), eyeNormalVec()));}

vec4 phong()
{
    return(phong(eyeLightVec(), eyeViewVec(), eyeNormalVec(), material, lights[0]));
}

vec4 lambert()
{
    return(phongKdKaColor(eyeLightVec(), eyeViewVec(), eyeNormalVec(), material, lights[0]));
}
