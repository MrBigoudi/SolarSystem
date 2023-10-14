#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <glad/gl.h>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "errorHandler.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Shaders;
using ShadersPointer = std::shared_ptr<Shaders>;

/**
 * @enum The different type of shaders
*/
enum ShaderType{VERT, FRAG, GEOM};

class Shaders{

    private:
        /**
         * The shader's id
        */
        GLuint _Id = -1;

    public:
        /**
         * Basic constructor
         * @param vert The path to the vertex shader
         * @param frag The path to the fragment shader
         * @param geom The path to the geometry shader
        */
        Shaders(const std::string& vert, const std::string& frag, const std::string& geom = "");

        /**
         * Basic destructor
        */
        ~Shaders(){
            glDeleteProgram(_Id);
        }

        /**
         * Accessor to the shader id
         * @return The id
        */
        const GLuint getId() const {
            return _Id;
        }

        /**
         * Activate the shader
        */
        void use() const;

        /**
         * Set a uniform boolean
         * @param name The variable's name
         * @param val The variable's value
        */
        void setBool(const std::string& name, bool val) const {
            checkID("Can't set a uniform value before creating the program!\n");
            glUniform1i(glGetUniformLocation(_Id, name.c_str()), (GLuint)val);
            ErrorHandler::handleGL("Failed to set %s!\n", name.c_str());
        }

        /**
         * Set a uniform int
         * @param name The variable's name
         * @param val The variable's value
        */
        void setInt(const std::string& name, int val) const {
            checkID("Can't set a uniform value before creating the program!\n");
            glUniform1i(glGetUniformLocation(_Id, name.c_str()), (GLuint)val);
            ErrorHandler::handleGL("Failed to set %s!\n", name.c_str());
        }

        /**
         * Set a uniform float
         * @param name The variable's name
         * @param val The variable's value
        */
        void setFloat(const std::string& name, float val) const {
            checkID("Can't set a uniform value before creating the program!\n");
            glUniform1f(glGetUniformLocation(_Id, name.c_str()), (GLuint)val);
            ErrorHandler::handleGL("Failed to set %s!\n", name.c_str());
        }

        /**
         * Set a uniform 4x4 float matrix
         * @param name The variable's name
         * @param val The variable's value
        */
        void setMat4f(const std::string& name, const glm::mat4x4& val) const {
            checkID("Can't set a uniform value before creating the program!\n");
            glUniformMatrix4fv(glGetUniformLocation(_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
            ErrorHandler::handleGL("Failed to set %s!\n", name.c_str());
        }

    private:
        /**
         * Get the content of a shader inside a string
         * @param path The path to the file
         * @return The content of the shader
         * @cond Crash the program if cannot open the file
        */
        const std::string openShaderFile(const std::string& path) const;

        /**
         * Compile a shader
         * @param code The shader code as a string
         * @param type The shader type
         * @return The shader
        */
        GLuint compileShader(const std::string& code, ShaderType type) const;

        /**
         * Link shaders
         * @param vert The vertex shader
         * @param frag The fragment shader
         * @param geom The geometry shader (optional)
        */
        void linkShaders(GLuint vert, GLuint frag, GLuint geom = -1);

        /**
         * Delete the given shader
         * @param shader The vertex shader
        */
        void deleteShader(GLuint shader) const {
            glDeleteShader(shader);
        }

        /**
         * Check if the program has been created
         * @param msg The error message
        */
        void checkID(const std::string& msg) const {
            if(_Id == -1){
                fprintf(stderr, "%s", msg.c_str());
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
        }

};

#endif