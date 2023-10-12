#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <glad/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @enum The different type of shaders
*/
enum ShaderType{VERT, FRAG, GEOM};

class Shaders{

    private:
        /**
         * The shader's id
        */
        GLuint _Id;

    public:
        /**
         * Basic constructor
         * @param vert The path to the vertex shader
         * @param frag The path to the fragment shader
        */
        Shaders(const std::string& vert, const std::string& frag);

        /**
         * Basic constructor
         * @param vert The path to the vertex shader
         * @param frag The path to the fragment shader
         * @param geokm The path to the geometry shader
        */
        Shaders(const std::string& vert, const std::string& frag, const std::string& geom);

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

    private:
        /**
         * Get the content of a shader inside a string
         * @param path The path to the file
         * @param shader The type of the shader
         * @return The content of the shader
         * @cond Crash the program if cannot open the file
        */
        const std::string openShaderFile(const std::string& path, ShaderType shader) const;

};

#endif