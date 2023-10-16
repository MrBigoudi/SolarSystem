#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "entity.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
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
    MeshPointer sphere = Mesh::unitSphere();
    MaterialPointer material(new Material());
    
    // setup the model matrices for the planets
    glm::mat4 sunModel   = glm::scale(glm::mat4(1.0f), glm::vec3(kSizeSun));
    glm::mat4 earthModel = glm::scale(glm::translate(sunModel, glm::vec3(kRadOrbitEarth,0.,0.)), glm::vec3(kSizeEarth));
    glm::mat4 moonModel = glm::scale(glm::translate(earthModel, glm::vec3(kRadOrbitMoon,0.,0.)), glm::vec3(kSizeMoon));

    // create the planets
    EntityPointer sun(new Entity(sphere, material, shader, sunModel));
    EntityPointer earth(new Entity(sphere, material, shader, earthModel));
    EntityPointer moon(new Entity(sphere, material, shader, moonModel));
    
    // create the scene
    Scene scene(camera);
    scene.addElement(sun);
    scene.addElement(earth);
    scene.addElement(moon);

    game->run(scene);
    game->quit();

    exit(EXIT_SUCCESS);
}