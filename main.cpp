#include <cstdlib>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "game.hpp"

int main(int argc, char** argv){

    Game game(800,600,"SolarSystem");
    game.run();
    game.quit();

    exit(EXIT_SUCCESS);
}