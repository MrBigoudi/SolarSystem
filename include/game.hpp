#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>

#include "errorHandler.hpp"
#include "shaders.hpp"

class Game;

using GameWindow = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;
using GamePointer = std::shared_ptr<Game>;

/**
 * The main class of the program
*/
class Game{

    private:
        /**
         * The main window
        */
        GameWindow _Window = GameWindow(nullptr, glfwDestroyWindow);

        /**
         * Tell if the wireframe mode is on
        */
        GLuint _IsWireframeOn = GLFW_FALSE;

        /**
         * The static instance of the game class
        */
        static GamePointer _Instance;

    private:
        /**
         * An empty constructor
        */
        Game(){}

        /**
         * Init opengl, the window and the basic hints
         * @param width The window's width
         * @param height The window's height
         * @param title The window's title
         * @param major The opengl's major version (default 3)
         * @param minor The opengl's minor version (default 3)
         * @param profile The opengl's profile (default core)
        */
        void initGame(int width, int heigth, const std::string& title, 
            int major = 3, int minor = 3, int profile = GLFW_OPENGL_CORE_PROFILE){
            ErrorHandler::handle(initGLFW());
            ErrorHandler::handle(setHint(GLFW_CONTEXT_VERSION_MAJOR, major));
            ErrorHandler::handle(setHint(GLFW_CONTEXT_VERSION_MINOR, minor));
            ErrorHandler::handle(setHint(GLFW_OPENGL_PROFILE, profile));
            ErrorHandler::handle(createWindow(width, heigth, title));
            ErrorHandler::handle(initGLAD());
        }

    public:
        /**
         * A basic destructor
        */
        ~Game(){
            if(_Window) _Window.reset();
        }

        /**
         * Get the unique instance of the game class
         * @return The instance
        */
        static GamePointer getInstance(){
            if(!_Instance) _Instance = GamePointer(new Game());
            return _Instance;
        }

        /**
         * Init opengl, the window and the basic hints
         * @param width The window's width
         * @param height The window's height
         * @param title The window's title
         * @param major The opengl's major version (default 3)
         * @param minor The opengl's minor version (default 3)
         * @param profile The opengl's profile (default core)
         * @return The game instance
        */
        static GamePointer init(int width, int height, const std::string& title, 
            int major = 3, int minor = 3, int profile = GLFW_OPENGL_CORE_PROFILE){
            GamePointer gamePtr = getInstance();
            gamePtr->initGame(width, height, title, major, minor, profile);
            return gamePtr;
        }


        /**
         * Initiate GLFW
         * @return The error code
         * @see ErrorCodes
        */
        ErrorCodes initGLFW() const {
            if(!glfwInit()){
                fprintf(stderr, "Failed to initialize GLFW!\n");
                return ErrorCodes::GLFW_ERROR;
            }
            return ErrorCodes::NO_ERROR;
        }

        /**
         * Initiate GLAD
         * @return The error code
         * @see ErrorCodes
        */
        ErrorCodes initGLAD() const {
            if(!gladLoadGL(glfwGetProcAddress)) {
                fprintf(stderr, "Failed to initialize GLAD!\n");
                return ErrorCodes::GLAD_ERROR;
            }
            return ErrorCodes::NO_ERROR;
        }

        /**
         * Set a hint
         * @param hint The hint to set
         * @param value The new value for the hint
         * @return The error code
         * @see ErrorCodes
        */
        ErrorCodes setHint(int hint, int value) const {
            glfwWindowHint(hint, value);

            int errorCode;
            const char* errorDescription;

            while ((errorCode = glfwGetError(&errorDescription)) != GLFW_NO_ERROR) {
                fprintf(stderr, "GLFW Error %d: %s\n", errorCode, errorDescription);
                return ErrorCodes::GLFW_ERROR;
            }

            return ErrorCodes::NO_ERROR;
        }

        /**
         * Create the window and make it as the current context
         * @param width The window's width
         * @param height The window's height
         * @param title The window's title
         * @return The error code
         * @see ErrorCodes
        */
        ErrorCodes createWindow(int width, int height, const std::string& title){
            _Window = GameWindow(glfwCreateWindow(width, height, title.c_str(), NULL, NULL), glfwDestroyWindow);
            if(!_Window){
                fprintf(stderr, "Failed to create GLFW window!\n");
                return ErrorCodes::GLFW_ERROR;
            }
            glfwMakeContextCurrent(_Window.get());
            return ErrorCodes::NO_ERROR;
        }

        /**
         * The main loop
         * @param shader The shader to use
        */
        void run(const Shaders& shader);

        /**
         * Quit the game
        */
        void quit() {
            glfwTerminate();
            if(_Window) _Window.reset();
        }

        /**
         * Set the clear color
         * @param r The red component
         * @param g The green component
         * @param b The blue component
         * @param a The alpha component
        */
        void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) const {
            glClearColor(r,g,b,a);
        }

        /**
         * Set the wireframe mode
        */
        void setWireframeMode() const {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        /**
         * Unset the wireframe mode
        */
        void unsetWireframeMode() const {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        /**
         * Process the inpu
         * @param window The game's window
         * @param key The keyboard key that was pressed or released
         * @param scancode The system specific scancode of the key
         * @param action The action (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
         * @param mods Bit field describing which modifier keys were held down
        */
        static void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
        // INPUT PROCESS - CALLBACKS
        /**
         * The command to quit
        */
        void quitCommand() const {
            glfwSetWindowShouldClose(_Window.get(), GLFW_TRUE);
        }

        /**
         * The command to turn on and off the wireframe
        */
        void wireframeSwitchCommand(){
            if(!_IsWireframeOn){
                setWireframeMode();
                _IsWireframeOn = GLFW_TRUE;
            } else {
                unsetWireframeMode();
                _IsWireframeOn = GLFW_FALSE;
            }
        }
};

#endif