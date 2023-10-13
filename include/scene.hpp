#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "errorHandler.hpp"

using Vertices = std::vector<GLfloat>;
using Colors = std::vector<GLfloat>;
using Uvs = std::vector<GLfloat>;
using Normals = std::vector<GLfloat>;

using Indices = std::vector<GLuint>;
using IndicesData = GLuint*;
using VboData = GLfloat*;

enum VboType{
    VERTICES = 3,
    COLORS = 4,
    UVS = 2,
    NORMALS = 3
};

/**
 * A class that handle the scene
*/
class Scene{
    private:
        /**
         * The number of elements per vertices inside the vbo
        */
        static const GLuint _NB_ELEMENT_PER_VERTICES;

        /**
         * The vertex array object
        */
        GLuint _VAO = 0;

        /**
         * The vertex buffer object
        */
        GLuint _VBO = 0;

        /**
         * The element buffer object
        */
        GLuint _EBO = 0;

        /**
         * The number of vertices
        */
        GLuint _NbVertices = 0;

        /**
         * The vertex positions
        */
        Vertices _Vertices = {};

        /**
         * The vertex colors
        */
        Colors _Colors = {};

        /**
         * The vertex uvs
        */
        Uvs _Uvs = {};

        /**
         * The vertex normals
        */
        Normals _Normals = {};

        /**
         * The number of indices
        */
        GLuint _NbIndices = 0;

        /**
         * The real indices
        */
        IndicesData _IndicesData;

        /**
         * The real vbo
        */
        VboData _VboData;


    private:
        /**
         * Create the vbo
         * @return The vbo as a floating point vector
        */
        void createVBO() {
            const GLuint size = _NbVertices*_NB_ELEMENT_PER_VERTICES;
            _VboData = new GLfloat[_NbVertices * _NB_ELEMENT_PER_VERTICES];

            for(int i=0; i<_NbVertices; i++){
                const GLuint idx   = i*_NB_ELEMENT_PER_VERTICES;
                const GLuint vIdx  = i*VboType::VERTICES;
                const GLuint cIdx  = i*VboType::COLORS;
                const GLuint uvIdx = i*VboType::UVS;
                const GLuint nIdx  = i*VboType::NORMALS;

                // set the vertices
                _VboData[idx]    = _Vertices[vIdx];
                _VboData[idx+1]  = _Vertices[vIdx+1];
                _VboData[idx+2]  = _Vertices[vIdx+2];
                // set the colors
                _VboData[idx+3]  = _Colors[cIdx];
                _VboData[idx+4]  = _Colors[cIdx+1];
                _VboData[idx+5]  = _Colors[cIdx+2];
                _VboData[idx+6]  = _Colors[cIdx+3];
                // set the uvs
                _VboData[idx+7]  = _Uvs[uvIdx];
                _VboData[idx+8]  = _Uvs[uvIdx+1];
                // set the normals
                _VboData[idx+9]  = _Normals[nIdx];
                _VboData[idx+10] = _Normals[nIdx+1];
                _VboData[idx+11] = _Normals[nIdx+2];
            }
        }

        /**
         * Bind the vbo and put the vertices data in it
        */
        void sendVBO() {
            if(_Vertices.empty()){
                fprintf(stderr, "Can't create GPU buffers without vertices!\n");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
            // create the vbo
            createVBO();

            for(int i=0; i<_NbVertices; i++){
                const GLuint idx = i*_NB_ELEMENT_PER_VERTICES;
                std::cout << 
                    _VboData[idx]    << ", " <<
                    _VboData[idx+1]  << ", " <<
                    _VboData[idx+2]  << ", " <<
                    _VboData[idx+3]  << ", " <<
                    _VboData[idx+4]  << ", " <<
                    _VboData[idx+5]  << ", " <<
                    _VboData[idx+6]  << ", " <<
                    _VboData[idx+7]  << ", " <<
                    _VboData[idx+8]  << ", " <<
                    _VboData[idx+9]  << ", " <<
                    _VboData[idx+10] << ", " <<
                    _VboData[idx+11] << std::endl;
            }

            // bind the vbo
            glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_VboData), _VboData, GL_DYNAMIC_READ);
        }

        /**
         * Bind the ebo and put the indices data in it
        */
        void sendEBO() const {
            if(_NbIndices==0){
                fprintf(stderr, "Can't create GPU buffers without indices!\n");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_IndicesData), _IndicesData, GL_DYNAMIC_READ);
        }

        /**
         * Bind the vao and put the necessary data in it
        */
        void sendVAO() const {
            GLsizei size = _NB_ELEMENT_PER_VERTICES * sizeof(float);
            GLvoid* pointer = (void*)0;
            GLuint id = 0;
            // position attributes
            glVertexAttribPointer(id, VboType::VERTICES, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(id);
            // color attributes
            pointer = reinterpret_cast<GLvoid*>(VboType::VERTICES * sizeof(float));
            id++;
            glVertexAttribPointer(id, VboType::COLORS, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(id);
            // uv attributes
            pointer = reinterpret_cast<GLvoid*>((VboType::VERTICES + VboType::COLORS) * sizeof(float));
            id++;
            glVertexAttribPointer(id, VboType::UVS, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(id);
            // normals attributes
            pointer = reinterpret_cast<GLvoid*>((VboType::VERTICES + VboType::COLORS + VboType::UVS) * sizeof(float));
            id++;
            glVertexAttribPointer(id, VboType::NORMALS, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(id);
        }

    private:
        /**
         * An empty constructor
        */
        Scene(){
            glGenVertexArrays(1, &_VAO);
            glGenBuffers(1, &_VBO);
            glGenBuffers(1, &_EBO);
        }


    public:
        /**
         * A constructor to initialize and bind everything
         * @param vertices The vertices (as x, y, z values)
         * @param indices The triangle indices
        */
        Scene(Vertices vertices, Indices indices) : Scene(vertices, indices, {}, {}, {}) {
        }

        /**
         * A constructor to initialize and bind everything
         * @param vertices The vertices (as x, y, z values)
         * @param indices The triangle indices
         * @param colors The vertices' colors (as r, g, b, a values)
         * @param uvs The vertices' uvs (as u, v values)
         * @param normals The vertices' normals (as nx, ny, nz values)
        */
        Scene(Vertices vertices, Indices indices, Colors colors, Uvs uvs, Normals normals) : Scene() {
            // fill if empty lists
            if(vertices.empty()){
                fprintf(stderr, "Vertices can't be empty!\n");
                ErrorHandler::handle(ErrorCodes::OUT_OF_RANGE);
            }
            if(indices.empty()){
                fprintf(stderr, "Indices can't be empty!\n");
                ErrorHandler::handle(ErrorCodes::OUT_OF_RANGE);
            }
            _NbVertices = vertices.size() / VboType::VERTICES;
            if(normals.empty()) normals = Normals(_NbVertices*VboType::NORMALS, 0.0f);
            if(colors.empty()) colors = Colors(_NbVertices*VboType::COLORS, 0.0f);
            if(uvs.empty()) uvs     = Uvs(_NbVertices*VboType::UVS, 0.0f);

            // check sizes
            if(colors.size() != _NbVertices*VboType::COLORS){
                fprintf(stderr, "The number of colors should be equal to the number of vertices! Given %d, expected: %d!\n", (int)colors.size(), _NbVertices*VboType::COLORS);
                ErrorHandler::handle(ErrorCodes::OUT_OF_RANGE);
            }
            if(normals.size() != _NbVertices*VboType::NORMALS){
                fprintf(stderr, "The number of normals should be equal to the number of vertices! Given %d, expected: %d!\n", (int)normals.size(), _NbVertices*VboType::NORMALS);
                ErrorHandler::handle(ErrorCodes::OUT_OF_RANGE);
            }
            if(uvs.size() != _NbVertices*VboType::UVS){
                fprintf(stderr, "The number of uvs should be equal to the number of vertices! Given %d, expected: %d!\n", (int)uvs.size(), _NbVertices*VboType::UVS);
                ErrorHandler::handle(ErrorCodes::OUT_OF_RANGE);
            }

            _Vertices = vertices;
            _NbIndices = indices.size();
            _IndicesData = new GLuint(_NbIndices);
            for(int i=0; i<_NbIndices; i++){
                _IndicesData[i] = indices.data()[i];
            }
            _Colors = colors;
            _Uvs = uvs;
            _Normals = normals;
        }

        /**
         * A basic destructor
        */
        ~Scene(){
            glDeleteVertexArrays(1, &_VAO);
            glDeleteBuffers(1, &_VBO);
            glDeleteBuffers(1, &_EBO);
            delete _VboData;
            delete _IndicesData;
        }

        /**
         * Initiate the GPU geometry
        */
        void initGpuGeometry() {
            glBindVertexArray(_VAO);
            sendVBO();
            sendEBO();
            sendVAO();
        }

        /**
         * Draw the vertices
        */
        void drawElements() const {
            glBindVertexArray(_VAO);
            glDrawElements(GL_TRIANGLES, _NbIndices, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }


};

#endif