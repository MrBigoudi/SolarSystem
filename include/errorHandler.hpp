#ifndef __ERROR_HANDLER_HPP__
#define __ERROR_HANDLER_HPP__

#include <cstdlib>
#include <iostream>

#include <glad/gl.h>
#include <stdarg.h>

/**
 * @enum The different error codes
*/
enum ErrorCodes{
    NO_ERROR, 
    GLAD_ERROR,
    GLFW_ERROR,
    GL_ERROR,
    NOT_INITALIZED,
    READ_FILE_ERROR,
    COMPILE_ERROR,
    LINK_ERROR,
    OUT_OF_RANGE,
    BAD_VALUE,
};

/**
 * The class to handle errors
*/
class ErrorHandler{
    private:
        /**
         * Private constructor to make the class purely virtual
        */
        ErrorHandler(){};

    public:
        /**
         * Handle the error
         * @param error The error to handle
        */
        static void handle(ErrorCodes error){
            switch(error){
                case NO_ERROR:
                    break;
                default:
                    std::cerr << "Exiting the program!" << std::endl;
                    exit(EXIT_FAILURE);
                    break;
            }
        }

        /**
         * Handle an OpenGL error
         * @param format The error message
        */
        static void handleGL(const char* format, ...){
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                va_list args;
                va_start(args, format);
                vfprintf(stderr, format, args);
                va_end(args);
                handle(GL_ERROR);
            }
        }

};

#endif