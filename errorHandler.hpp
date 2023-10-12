#ifndef __ERROR_HANDLER_HPP__
#define __ERROR_HANDLER_HPP__

#include <cstdlib>
#include <iostream>

/**
 * @enum The different error codes
*/
enum ErrorCodes{
    NO_ERROR, 
    GLAD_ERROR,
    GLFW_ERROR,
    NOT_INITALIZED
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

};

#endif