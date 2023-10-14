#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "camera.hpp"

int main(int argc, char** argv){

    Vertices vertices({
        0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f
    });
    Colors colors({
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    });
    Indices indices({
        0, 1, 2,
        1, 3, 2
    });

    GamePointer game = Game::init(800,600,"SolarSystem");
    ShadersPointer shader(new Shaders("shaders/vert.glsl", "shaders/frag.glsl"));
    CameraPointer camera(new Camera());

    MeshPointer mesh(new Mesh(vertices, indices, colors));
    Scene scene(camera, shader);
    scene.addMesh(mesh);
    //camera.print(std::cout);

    game->run(scene);
    game->quit();

    exit(EXIT_SUCCESS);
}