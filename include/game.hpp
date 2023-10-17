#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>

#include "errorHandler.hpp"
#include "scene.hpp"

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

        /**
         * The game's scene
        */
        ScenePointer _Scene = nullptr;

        /**
         * The delta time
        */
        GLfloat _Dt = 0.0f;

        /**
         * The last time frame
        */
        GLfloat _LastTimeFrame = 0.0f;

        /**
         * Boolean to check the press keys
        */
        bool _KeyLeftPressed = false;
        bool _KeyRightPressed = false;
        bool _KeyUpPressed = false;
        bool _KeyDownPressed = false;

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
        void initGame(int width, int height, const std::string& title, 
            GLuint major = 3, GLuint minor = 3, GLuint profile = GLFW_OPENGL_CORE_PROFILE, GLuint resizable = GLFW_FALSE){
            ErrorHandler::handle(initGLFW());
            ErrorHandler::handle(setHint(GLFW_CONTEXT_VERSION_MAJOR, major));
            ErrorHandler::handle(setHint(GLFW_CONTEXT_VERSION_MINOR, minor));
            ErrorHandler::handle(setHint(GLFW_OPENGL_PROFILE, profile));
            ErrorHandler::handle(setHint(GLFW_RESIZABLE, resizable));
            ErrorHandler::handle(createWindow(width, height, title));
            ErrorHandler::handle(initGLAD());
            glEnable(GL_DEPTH_TEST);
            ErrorHandler::handleGL("Failed to enable GL_DEPTH_TEST!");
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
         * @param resizable If the window is resizable (default false)
         * @return The game instance
        */
        static GamePointer init(int width, int height, const std::string& title, 
            GLuint major = 3, GLuint minor = 3, GLuint profile = GLFW_OPENGL_CORE_PROFILE, GLuint resizable = GLFW_FALSE){
            GamePointer gamePtr = getInstance();
            gamePtr->initGame(width, height, title, major, minor, profile, resizable);
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
        ErrorCodes setHint(GLuint hint, GLuint value) const {
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
         * Set the scene
         * @param scene The scene to set
        */
        void setScene(const ScenePointer& scene){
            if(scene) _Scene = scene;
        }

        /**
         * The main loop
        */
        void run();

        /**
         * Update the delta time
        */
        void update(){
            GLfloat curTime = glfwGetTime();
            _Dt = curTime - _LastTimeFrame;
            _LastTimeFrame = curTime;
            // update the camera
            updateCamera();
        }

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
         * Process the inputs
         * @param window The game's window
         * @param key The keyboard key that was pressed or released
         * @param scancode The system specific scancode of the key
         * @param action The action (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
         * @param mods Bit field describing which modifier keys were held down
        */
        static void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        /**
         * Process the scrolls
         * @param window The game's window
         * @param xoffset The x offset
         * @param yoffset The y offset
        */
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
            GLfloat fov = getInstance()->_Scene->getCamera()->getFov() - (GLfloat)yoffset;
            if (fov < 1.0f)
                fov = 1.0f;
            if (fov > 45.0f)
                fov = 45.0f; 
            getInstance()->_Scene->getCamera()->setFov(fov);
        }

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

        /**
         * Update the camera
        */
        void updateCamera() const {
            if (_KeyLeftPressed) {
                _Scene->getCamera()->move(CameraMovement::LEFT, _Dt);
            }
            if (_KeyRightPressed) {
                _Scene->getCamera()->move(CameraMovement::RIGHT, _Dt);
            }
            if (_KeyUpPressed) {
                _Scene->getCamera()->move(CameraMovement::UP, _Dt);
            }
            if (_KeyDownPressed) {
                _Scene->getCamera()->move(CameraMovement::DOWN, _Dt);
            }
        }
};

#endif