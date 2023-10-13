#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "game.hpp"
#include "scene.hpp"

int main(int argc, char** argv){

    Vertices vertices({
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    });
    Indices indices({
        0, 1, 3,
        1, 2, 3
    });

    GamePointer game = Game::init(800,600,"SolarSystem");
    Shaders shader("shaders/vert.glsl", "shaders/frag.glsl");
    Scene scene(vertices, indices);

    game->run(shader, scene);
    game->quit();

    exit(EXIT_SUCCESS);
}