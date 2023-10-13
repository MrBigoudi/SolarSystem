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
         * The triangle indices
        */
        Indices _Indices = {};

    private:
        /**
         * Create the vbo
         * @return The vbo as a floating point vector
        */
        std::vector<GLfloat> createVBO() const {
            const GLuint size = _NbVertices*_NB_ELEMENT_PER_VERTICES;
            std::vector<GLfloat> vbo(size);


            for(int i=0; i<_NbVertices; i++){
                const GLuint idx   = i*_NB_ELEMENT_PER_VERTICES;
                const GLuint vIdx  = i*VboType::VERTICES;
                const GLuint cIdx  = i*VboType::COLORS;
                const GLuint uvIdx = i*VboType::UVS;
                const GLuint nIdx  = i*VboType::NORMALS;

                // set the vertices
                vbo[idx] = _Vertices[vIdx];
                vbo[idx+1] = _Vertices[vIdx+1];
                vbo[idx+2] = _Vertices[vIdx+2];
                // set the colors
                vbo[idx+3] = _Colors[cIdx];
                vbo[idx+4] = _Colors[cIdx+1];
                vbo[idx+5] = _Colors[cIdx+2];
                vbo[idx+6] = _Colors[cIdx+3];
                // set the uvs
                vbo[idx+7] = _Uvs[uvIdx];
                vbo[idx+8] = _Uvs[uvIdx+1];
                // set the normals
                vbo[idx+9] = _Normals[nIdx];
                vbo[idx+10] = _Normals[nIdx+1];
                vbo[idx+11] = _Normals[nIdx+2];
            }

            return vbo;
        }

        /**
         * Bind the vbo and put the vertices data in it
        */
        void sendVBO() const {
            if(_Vertices.empty()){
                fprintf(stderr, "Can't create GPU buffers without vertices!\n");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
            std::vector<GLfloat> vbo = createVBO();
            
            glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vbo.data()), vbo.data(), GL_DYNAMIC_READ);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        /**
         * Bind the ebo and put the indices data in it
        */
        void sendEBO() const {
            if(_Indices.empty()){
                fprintf(stderr, "Can't create GPU buffers without indices!\n");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_Indices.data()), _Indices.data(), GL_DYNAMIC_READ);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        /**
         * Bind the vao and put the necessary data in it
        */
        void sendVAO() const {
            GLsizei size = _NB_ELEMENT_PER_VERTICES * sizeof(float);
            GLvoid* pointer = (void*)0;
            // position attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(0);
            // color attributes
            pointer = (void*)(VboType::VERTICES * sizeof(float));
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(1);
            // uv attributes
            pointer = (void*)((VboType::VERTICES + VboType::COLORS) * sizeof(float));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(2);
            // normals attributes
            pointer = (void*)((VboType::VERTICES + VboType::COLORS + VboType::UVS) * sizeof(float));
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, size, pointer);
            glEnableVertexAttribArray(3);
            // unbind
            glBindVertexArray(0);
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
            _Indices = indices;
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
        }

        /**
         * Initiate the GPU geometry
        */
        void initGpuGeometry() const {
            glBindVertexArray(_VAO);
            sendVBO();
            sendEBO();
            sendVAO();
        }

        /**
         * Draw the vertices
        */
        void drawElements() const {
            glDrawElements(GL_TRIANGLES, _Indices.size(), GL_UNSIGNED_INT, 0);
        }


};

#endif