#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vCol;

out vec4 fCol;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){
    mat4 MVP = projMat * viewMat * modelMat;
    gl_Position = MVP * vec4(vPos, 1.0);
    fCol = vCol;
}