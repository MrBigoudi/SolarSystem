#include "game.hpp"
#include "GLFW/glfw3.h"
#include "scene.hpp"
#include <GL/glext.h>

/**
 * The static instance of the game class
*/
GamePointer Game::_Instance = GamePointer(nullptr);

/**
 * The main loop
 * @param shader The shader to use
 * @param scene The scene to use
*/
void Game::run(const Shaders& shader, Scene& scene){
    if(!_Window){
        fprintf(stderr, "Can't run without a GLFW window!\n");
        ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
    } 

    // set the callbacks
    glfwSetKeyCallback(_Window.get(), inputCallback);

    // init the buffers
    scene.initGpuGeometry();

    // set the clear color
    setClearColor(0.2f, 0.3f, 0.3f);

    while(!glfwWindowShouldClose(_Window.get())){
        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        scene.drawElements();

        // handle events
        glfwSwapBuffers(_Window.get());
        glfwPollEvents();
    }
}

/**
 * Process the inpu
 * @param window The game's window
 * @param key The keyboard key that was pressed or released
 * @param scancode The system specific scancode of the key
 * @param action The action (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
 * @param mods Bit field describing which modifier keys were held down
*/
void Game::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // quit with q
    if(key == GLFW_KEY_Q && action == GLFW_PRESS){
        getInstance().get()->quitCommand();
        return;
    }

    // set the wireframe mode on and off with w
    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        getInstance().get()->wireframeSwitchCommand();
    }
}