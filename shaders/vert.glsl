#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vCol;
layout(location = 2) in vec2 vUv;
layout(location = 3) in vec3 vNorm;

out vec4 fCol;
out vec3 fNorm;
out vec3 fPos;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){
    mat4 MVP = projMat * viewMat * modelMat;
    gl_Position = MVP * vec4(vPos, 1.0);
    //fCol = vec4((vNorm + 1.0) / 2.0, 1.0);
    fCol = vCol;
    fNorm = vNorm;
    fPos = vec3(modelMat*vec4(vPos, 1.0));
}