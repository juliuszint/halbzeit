#sgdefine COMMONLIGHTMATDEFS_INC //Define setzen um Mehrfache inkludierung auszuschliessen

#define MAX_LIGHTS 8 //maximum number of lights in a scene

struct Light{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 position;      //position of the light source
  vec3 spotDirection; //direction of the spot light
  float spotCutoff; //cutoff angle of the spot light
  bool hasShadow; //does the light produce shadow?
  float isActive;
};

struct Material{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 emission;
  float shininess;
};

uniform Light lights[MAX_LIGHTS];
uniform Material material;

