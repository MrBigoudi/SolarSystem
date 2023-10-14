#include "game.hpp"
#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "scene.hpp"
#include <GL/glext.h>

/**
 * The static instance of the game class
*/
GamePointer Game::_Instance = GamePointer(nullptr);

/**
 * The main loop
 * @param scene The scene to render
*/
void Game::run(const Scene& scene) const {
    if(!_Window){
        fprintf(stderr, "Can't run without a GLFW window!\n");
        ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
    } 

    // set the callbacks
    glfwSetKeyCallback(_Window.get(), inputCallback);

    // init the buffers
    scene.initMeshes();

    // set the clear color
    setClearColor(0.2f, 0.3f, 0.3f);

    while(!glfwWindowShouldClose(_Window.get())){
        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CameraPointer camera = scene.getCamera();
        ShadersPointer shader = scene.getShader();

        shader->use();

        // create the matrices
        const glm::mat4 model = glm::mat4(1.0f);
        const glm::mat4 view  = camera->getViewMatrix();
        const glm::mat4 proj  = camera->getProjectionMatrix(ProjectionType::PERSP);
        shader->setMat4f("modelMat", model);
        shader->setMat4f("viewMat", view);
        shader->setMat4f("projMat", proj);

        // std::cout << "Model:\n"
        //     << model[0][0] << ", " << model[0][1] << ", " << model[0][2] << "\n"
        //     << model[1][0] << ", " << model[1][1] << ", " << model[1][2] << "\n"
        //     << model[2][0] << ", " << model[2][1] << ", " << model[2][2] << std::endl;

        // std::cout << "View:\n"
        //     << view[0][0] << ", " << view[0][1] << ", " << view[0][2] << "\n"
        //     << view[1][0] << ", " << view[1][1] << ", " << view[1][2] << "\n"
        //     << view[2][0] << ", " << view[2][1] << ", " << view[2][2] << std::endl;

        // std::cout << "Projection:\n"
        //     << proj[0][0] << ", " << proj[0][1] << ", " << proj[0][2] << "\n"
        //     << proj[1][0] << ", " << proj[1][1] << ", " << proj[1][2] << "\n"
        //     << proj[2][0] << ", " << proj[2][1] << ", " << proj[2][2] << std::endl;

        scene.render();

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