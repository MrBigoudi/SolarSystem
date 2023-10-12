#include "game.hpp"
#include "GLFW/glfw3.h"

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

        // process inputs
        processInput();

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
 * Process the inputs
*/
void Game::processInput(){
    // quit with q
    if(isPress(GLFW_KEY_Q)){
        quitCommand();
        return;
    }

    // set the wireframe mode on and off with w
    if(isPress(GLFW_KEY_W)){
        wireframeSwitchCommand();
    }
}