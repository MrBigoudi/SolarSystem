#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "game.hpp"

int main(int argc, char** argv){

    Game game(800,600,"SolarSystem");
    Shaders shader("shaders/vert.glsl", "shaders/frag.glsl");

    game.run(shader);
    game.quit();

    exit(EXIT_SUCCESS);
}