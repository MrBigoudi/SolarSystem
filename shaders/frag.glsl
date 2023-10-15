#version 330 core

in vec4 fCol;
in vec3 fNorm;
in vec3 fPos;

out vec4 color;

uniform vec3 camPos;
uniform vec3 fAmbient;
uniform float fDiffuse;
uniform float fSpecular;
uniform float fShininess;

/**
 * Get the diffusion part of the model
 * @param lPos The light position
 * @param lColor The light color
 * @return The diffusion component
*/
vec3 getDiffuse(vec3 lPos, vec3 lColor){
    vec3 lDir = normalize(lPos-fPos);
    vec3 nDir = normalize(fNorm);
    vec3 c = vec3(fCol.x*lColor.x, fCol.y*lColor.y, fCol.z*lColor.z);
    return fDiffuse*max(0.0, dot(nDir, lDir))*c;
}

/**
 * Get the specular part of the model
 * @param lPos The light position
 * @param lColor The light color
 * @return The specular component
*/
vec3 getSpecular(vec3 lPos, vec3 lColor){
    vec3 lDir = normalize(lPos-fPos);
    vec3 camDir = normalize(camPos-fPos);
    vec3 nDir = normalize(fNorm);

    vec3 h = normalize(lDir + camDir);
    vec3 c = vec3(fCol.x*lColor.x, fCol.y*lColor.y, fCol.z*lColor.z);

    return fSpecular*pow(max(0., dot(nDir, h)), fShininess)*c;
}

void main(){
    vec3 lPos = vec3(1.2, 1.0, 2.0);
    vec3 lColor = vec3(1.,1.,1.);

    vec3 ambient = fAmbient;
    vec3 diffuse = getDiffuse(lPos, lColor);
    vec3 specular = getSpecular(lPos, lColor);

    // color = fCol;
    color = vec4(ambient + diffuse + specular, 1.0);
}