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
*/
void Game::run(){
    if(!_Window){
        fprintf(stderr, "Can't run without a GLFW window!\n");
        ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
    } 

    if(!_Scene){
        fprintf(stderr, "Can't run without a scene!\n");
        ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
    } 

    // set the callbacks
    glfwSetKeyCallback(_Window.get(), inputCallback);
    glfwSetScrollCallback(_Window.get(), scrollCallback);

    // init the buffers
    _Scene->initMeshes();

    while(!glfwWindowShouldClose(_Window.get())){
        // update
        update();
        _Scene->update((float)glfwGetTime());

        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _Scene->render();

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

    // move the camera using the arrows and f, b
    if(key == GLFW_KEY_LEFT){
        if(action == GLFW_PRESS)
            getInstance().get()->_KeyLeftPressed = true;
        if(action == GLFW_RELEASE)
            getInstance().get()->_KeyLeftPressed = false;
    }
    if(key == GLFW_KEY_RIGHT){
        if(action == GLFW_PRESS)
            getInstance().get()->_KeyRightPressed = true;
        if(action == GLFW_RELEASE)
            getInstance().get()->_KeyRightPressed = false;
    }
    if(key == GLFW_KEY_UP){
        if(action == GLFW_PRESS)
            getInstance().get()->_KeyUpPressed = true;
        if(action == GLFW_RELEASE)
            getInstance().get()->_KeyUpPressed = false;
    }
    if(key == GLFW_KEY_DOWN){
        if(action == GLFW_PRESS)
            getInstance().get()->_KeyDownPressed = true;
        if(action == GLFW_RELEASE)
            getInstance().get()->_KeyDownPressed = false;
    }
}