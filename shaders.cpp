#include "shaders.hpp"
#include <cstdlib>

Shaders::Shaders(const std::string& vert, const std::string& frag){
    
}

Shaders::Shaders(const std::string& vert, const std::string& frag, const std::string& geom){

}

void Shaders::use() const {

}


const std::string Shaders::openShaderFile(const std::string& path, ShaderType shader) const{
    std::string shaderCode;
    std::ifstream shaderFile;

    try {
        // open files
        shaderFile.open(path);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();	
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode   = shaderStream.str();	
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        exit(EXIT_FAILURE);
    }
    return shaderCode;
}
