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

int main(int argc, char** argv){

    // Vertices vertices({
    //     0.0f,  0.0f, 0.0f,
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     1.0f,  1.0f, 0.0f
    // });
    // Colors colors({
    //     1.0f, 0.0f, 0.0f, 1.0f,
    //     0.0f, 1.0f, 0.0f, 1.0f,
    //     0.0f, 0.0f, 1.0f, 1.0f,
    //     0.0f, 0.0f, 0.0f, 1.0f,
    // });
    // Indices indices({
    //     0, 1, 2,
    //     1, 3, 2
    // });

    GLuint windowWidth  = 800;
    GLuint windowHeight = 600;

    GamePointer game = Game::init(windowWidth, windowHeight,"SolarSystem");
    ShadersPointer shader(new Shaders("shaders/vert.glsl", "shaders/frag.glsl"));
    CameraPointer camera(new Camera());
    camera->setRatio(((GLfloat)windowWidth)/windowHeight);

    Scene scene(camera);

    // MeshPointer mesh(new Mesh(vertices, indices, colors));
    MeshPointer sphere = Mesh::unitSphere();
    MaterialPointer material(new Material());
    EntityPointer entity(new Entity(sphere, material, shader));
    // scene.addMesh(mesh);
    // sphere->print(std::cout);
    scene.addElement(entity);

    game->run(scene);
    game->quit();

    exit(EXIT_SUCCESS);
}