#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "entity.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "light.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "shaders.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "camera.hpp"

const static float kSizeSun = 1;
const static float kSizeEarth = 0.5;
const static float kSizeMoon = 0.25;
const static float kRadOrbitEarth = 10;
const static float kRadOrbitMoon = 2;
const static float kEarthRotationAxe = 23.5f;
const static float kEarthRotationSpeed = 0.1f;
const static float kMoonRotationAxe = 0.f;
const static float kMoonRotationSpeed = 0.5f;

glm::mat4 earthRotation(GLfloat dt, const glm::mat4& model){
    GLfloat theta = glm::radians(kEarthRotationAxe);
    glm::vec3 rotationAxis = glm::vec3(cos(theta), sin(theta), 0.0f);
    glm::mat4 rotation = glm::rotate(model, kEarthRotationSpeed, rotationAxis);
    return rotation;
};

glm::mat4 moonRotation(GLfloat dt, const glm::mat4& model){
    GLfloat theta = glm::radians(kMoonRotationAxe);
    glm::vec3 rotationAxis = glm::vec3(cos(theta), sin(theta), 0.0f);
    glm::mat4 rotation = glm::rotate(model, kMoonRotationSpeed, rotationAxis);
    return rotation;
};

int main(int argc, char** argv){

    GLuint windowWidth  = 800;
    GLuint windowHeight = 600;

    GamePointer game = Game::init(windowWidth, windowHeight,"SolarSystem");
    ShadersPointer shader(new Shaders("shaders/vert.glsl", "shaders/frag.glsl"));

    // setup the camera
    CameraPointer camera(new Camera());
    camera->setRatio(((GLfloat)windowWidth)/windowHeight);
    camera->moveTo(glm::vec3(-2.0f, 5.0f, 25.f));
    camera->setTarget(glm::vec3(-2.0f, .0f, 0.f));

    // setup the spheres meshes and materials
    MeshPointer sunMesh = Mesh::unitSphere();
    MeshPointer earthMesh(new Mesh(sunMesh)); // shallow copy
    MeshPointer moonMesh(new Mesh(sunMesh)); // shallow copy
    
    // setup the model matrices for the planets
    glm::mat4 sunModel   = glm::scale(glm::mat4(1.0f), glm::vec3(kSizeSun));
    glm::mat4 earthModel = glm::scale(glm::translate(sunModel, glm::vec3(kRadOrbitEarth,0.,0.)), glm::vec3(kSizeEarth));
    glm::mat4 moonModel = glm::scale(glm::translate(earthModel, glm::vec3(kRadOrbitMoon,0.,0.)), glm::vec3(kSizeMoon));

    // create the suns
    glm::vec4 sunColor = glm::vec4(1.,1.,0.,1.);
    MaterialPointer sunMaterial(new Material());
    sunMesh->setSimpleColor(sunColor);
    sunMaterial->setAmbient(1.0f);
    EntityPointer sun(new Entity(sunMesh, sunMaterial, shader, sunModel));
    //sun->setUpdateFct(rotation);

    // create the planes
    MaterialPointer planetMaterial(new Material());
    
    glm::vec4 earthColor = glm::vec4(0.,1.,0.2,1.);
    earthMesh->setSimpleColor(earthColor);
    EntityPointer earth(new Entity(earthMesh, planetMaterial, shader, earthModel));
    earth->setUpdateFct(earthRotation);

    glm::vec4 moonColor = glm::vec4(1.,1.,1.,1.);
    moonMesh->setSimpleColor(moonColor);
    EntityPointer moon(new Entity(moonMesh, planetMaterial, shader, moonModel));
    moon->setUpdateFct(moonRotation);

    // create the lights
    LightPointer sunLight(new Light(LightType::PointLight, glm::vec3(), glm::vec3(1.0,1.0,1.0), sunModel));
    
    // create the scene
    ScenePointer scene(new Scene(camera));
    scene->addElement(sun);
    scene->addElement(earth);
    scene->addElement(moon);
    scene->addLight(sunLight);

    game->setScene(scene);
    game->run();
    game->quit();

    exit(EXIT_SUCCESS);
}