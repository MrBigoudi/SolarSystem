#version 330 core

in vec4 fCol;
in vec3 fNorm;
in vec3 fPos;

out vec4 color;

uniform vec3 camPos;
uniform float fAmbient;
uniform float fDiffuse;
uniform float fSpecular;
uniform float fShininess;

struct PointLight{
    vec3 position;
    vec3 color;
    mat4 model;
};

struct DirectionalLight{
    vec3 position;
    vec3 color;
    mat4 model;
};

const int MAX_SIZE = 128;

uniform int NB_POINT_LIGHTS;
uniform PointLight pointLights[MAX_SIZE];
uniform int NB_DIRECTIONAL_LIGHTS;
uniform DirectionalLight directionalLights[MAX_SIZE];

/**
 * Get the light's position
 * @param light The point light to get
*/
vec3 getLightPos(PointLight light){
    vec4 tmp = light.model * vec4(light.position, 1.0);
    return vec3(tmp.x, tmp.y, tmp.z);
}

/**
 * Get the light's position
 * @param light The directional light to get
*/
vec3 getLightPos(DirectionalLight light){
    vec4 tmp = light.model * vec4(light.position, 1.0);
    return vec3(tmp.x, tmp.y, tmp.z);
}

/**
 * Get the ambient part of the model for one light
 * @param lColor The light color
 * @return The ambient component
*/
vec3 getAmbient(vec3 lColor){
    vec3 c = vec3(fCol.x*lColor.x, fCol.y*lColor.y, fCol.z*lColor.z);
    return fAmbient * lColor * c;
}


/**
 * Get the diffusion part of the model for one light
 * @param lPos The light position
 * @param lColor The light color
 * @return The diffusion component
*/
vec3 getDiffuse(vec3 lPos, vec3 lColor){
    if(lPos == fPos) return vec3(0.);
    vec3 lDir = normalize(lPos-fPos);
    vec3 nDir = normalize(fNorm);
    vec3 c = vec3(fCol.x*lColor.x, fCol.y*lColor.y, fCol.z*lColor.z);
    return fDiffuse*max(0.0, dot(nDir, lDir))*c;
}

/**
 * Get the specular part of the model for one light
 * @param lPos The light position
 * @param lColor The light color
 * @return The specular component
*/
vec3 getSpecular(vec3 lPos, vec3 lColor){
    if(lPos == fPos) return vec3(0.);
    vec3 lDir = normalize(lPos-fPos);
    vec3 camDir = normalize(camPos-fPos);
    vec3 nDir = normalize(fNorm);

    vec3 h = normalize(lDir + camDir);
    vec3 c = vec3(fCol.x*lColor.x, fCol.y*lColor.y, fCol.z*lColor.z);

    return fSpecular*pow(max(0., dot(nDir, h)), fShininess)*c;
}

/**
 * Get the complete ambient part of the model
*/
vec3 getAmbient(){
    vec3 sum = vec3(0.);
    // point lights
    int endLoop = int(min(NB_POINT_LIGHTS, MAX_SIZE));
    for(int i=0; i<endLoop; i++){
        vec3 lColor = pointLights[i].color;
        sum += getAmbient(lColor);
    }

    // directional lights
    endLoop = int(min(NB_DIRECTIONAL_LIGHTS, MAX_SIZE));
    for(int i=0; i<endLoop; i++){
        vec3 lColor = directionalLights[i].color;
        sum += getAmbient(lColor);
    }
    return sum;
}


/**
 * Get the complete diffuse part of the model
*/
vec3 getDiffuse(){
    vec3 sum = vec3(0.);
    // point lights
    int endLoop = int(min(NB_POINT_LIGHTS, MAX_SIZE));
    for(int i=0; i<endLoop; i++){
        vec3 lPos = getLightPos(pointLights[i]);
        vec3 lColor = pointLights[i].color;
        sum += getDiffuse(lPos, lColor);
    }

    // directional lights
    endLoop = int(min(NB_DIRECTIONAL_LIGHTS, MAX_SIZE));
    for(int i=0; i<endLoop; i++){
        vec3 lPos = getLightPos(directionalLights[i]);
        vec3 lColor = directionalLights[i].color;
        sum += getDiffuse(lPos, lColor);
    }
    return sum;
}

/**
 * Get the complete specular part of the model
*/
vec3 getSpecular(){
    vec3 sum = vec3(0.);
    // point lights
    int endLoop = int(min(NB_POINT_LIGHTS, MAX_SIZE));
    for(int i=0; i<endLoop; i++){
        vec3 lPos = pointLights[i].position;
        vec3 lColor = pointLights[i].color;
        sum += getSpecular(lPos, lColor);
    }

    // directional lights
    endLoop = int(min(NB_DIRECTIONAL_LIGHTS, MAX_SIZE));
    for(int i=0; i<endLoop; i++){
        vec3 lPos = directionalLights[i].position;
        vec3 lColor = directionalLights[i].color;
        sum += getSpecular(lPos, lColor);
    }
    return sum;
}

/**
 * The Phong model
*/
void main(){
    vec3 ambient = getAmbient();
    vec3 diffuse = getDiffuse();
    vec3 specular = getSpecular();

    // color = fCol;
    color = vec4(ambient + diffuse + specular, 1.0);
}