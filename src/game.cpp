#include "game.hpp"
#include "GLFW/glfw3.h"

/**
 * The static instance of the game class
*/
GamePointer Game::_Instance = GamePointer(nullptr);

/**
 * The main loop
 * @param shader The shader to use
*/
void Game::run(const Shaders& shader){
    if(!_Window){
        fprintf(stderr, "Can't run without a GLFW window!\n");
        ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
    } 

    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // set the callbacks
    glfwSetKeyCallback(_Window.get(), inputCallback);

    // 1. generate the buffers
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_READ);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_READ);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    setClearColor(0.2f, 0.3f, 0.3f);
    // 5. infinite loop
    while(!glfwWindowShouldClose(_Window.get())){
        // render
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // handle events
        glfwSwapBuffers(_Window.get());
        glfwPollEvents();
    }

    // 6. unbind the vertices
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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