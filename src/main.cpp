#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "entity.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "shaders.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "planet.hpp"
#include "sun.hpp"

// sun
const static float kSizeSun = 1;
const static glm::vec3 kSunRotationAxis = glm::vec3(0.f, 1.f, 0.f);
const static float kSunRotationSpeed = 0.01f;

// earth
const static float kSizeEarth = 0.5;
const static float kRadOrbitEarth = 10;
const static glm::vec3 kEarthRotationAxis = glm::vec3(0.f, 23.5f, 0.f);
const static glm::vec3 kEarthOrbitAxis = glm::vec3(0.f, 1.f, 0.f);
const static float kEarthRotationSpeed = 0.05f;
const static float kEarthOrbitSpeed = 0.01f;

// moon
const static float kSizeMoon = 0.25;
const static float kRadOrbitMoon = 2;
const static glm::vec3 kMoonRotationAxis = glm::vec3(0.f, 1.f, 0.f);
const static glm::vec3 kMoonOrbitAxis = glm::vec3(0.f, 1.f, 0.f);
const static float kMoonRotationSpeed = 0.1f;
const static float kMoonOrbitSpeed = 0.04f;

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
    
    // setup the materials
    MaterialPointer sunMaterial(new Material());
    sunMaterial->setAmbient(1.0f);
    MaterialPointer planetMaterial(new Material());

    // create the scene
    ScenePointer scene(new Scene(camera));

    // setup the the sun
    SunPointer sun(new Sun(sunMaterial, shader, glm::vec3(), glm::vec3(1.0,1.0,1.0)));
    sun->getMesh()->setSimpleColor(glm::vec4(1.,1.,0.,1.));
    sun->addToScene(scene);
    sun->init(kSizeSun, kSunRotationSpeed, kSunRotationAxis);

    // setup the earth
    PlanetPointer earth(new Planet(planetMaterial, shader));
    earth->getMesh()->setSimpleColor(glm::vec4(0.,1.,0.2,1.));
    earth->init(kSizeEarth, kEarthRotationSpeed, kEarthRotationAxis, kEarthOrbitSpeed, kEarthOrbitAxis, kRadOrbitEarth, sun);
    earth->addToScene(scene);
    earth->loadTexture("media/earth.jpg");
    
    // setup the moon
    PlanetPointer moon(new Planet(planetMaterial, shader));
    moon->getMesh()->setSimpleColor(glm::vec4(1.,1.,1.,1.));
    moon->init(kSizeMoon, kMoonRotationSpeed, kMoonRotationAxis, kMoonOrbitSpeed, kMoonOrbitAxis, kRadOrbitMoon, earth);
    moon->addToScene(scene);
    moon->loadTexture("media/moon.jpg");

    // main loop
    game->setScene(scene);
    game->run();
    game->quit();

    exit(EXIT_SUCCESS);
}