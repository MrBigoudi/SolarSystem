#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <functional>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <memory>

#include "mesh.hpp"
#include "material.hpp"
#include "shaders.hpp"
#include "stb_image.h"

class Entity;
using EntityPointer = std::shared_ptr<Entity>;
using UpdateFct = std::function<glm::mat4(GLfloat dt, const glm::mat4& model)>;

/**
 * A class representing an entity in the scene
*/
class Entity {

    private:
        /**
         * The entity's mesh
        */
        MeshPointer _Mesh = nullptr;

        /**
         * The entity's material
        */
        MaterialPointer _Material = nullptr;

        /**
         * The entity's shader
        */
        ShadersPointer _Shader = nullptr;

        /**
         * The entity's model matrix
        */
        glm::mat4 _Model = glm::mat4(1.0f);

        /**
         * The entity's updating function
        */
        UpdateFct _UpdateFct = [=](GLfloat dt, const glm::mat4& model){return model;};

        /**
         * The texture Id
        */
        GLuint _TexId = 0;


    public:
        /**
         * A basic constructor
         * @param mesh The entity's mesh
         * @param material The entity's material
         * @param shader The entity's shader
         * @param model The entity's model matrix
        */
        Entity(const MeshPointer& mesh, const MaterialPointer& material, const ShadersPointer& shader, const glm::mat4& model){
            _Mesh = mesh;
            _Material = material;
            _Shader = shader;
            _Model = model;
        }

        /**
         * Initiate the entity
        */
        void init() const {
            _Mesh->initGpuGeometry();
        }

        /**
         * Get the mesh
         * @return A pointer to the mesh
        */
        MeshPointer getMesh() const {
            return _Mesh;
        }

        /**
         * Get the material
         * @return A pointer to the material
        */
        MaterialPointer getMaterial() const {
            return _Material;
        }

        /**
         * Get the model matrix of the entity
         * @return A copy of the model matrix
        */
        const glm::mat4 getModel() const {
            return _Model;
        }

        /**
         * Set the update function
         * @param update The function to call on update
        */
        void setUpdateFct(UpdateFct update){
            _UpdateFct = update;
        }

        /**
         * Update the entity
         * @param dt The delta time
        */
        void update(GLfloat dt){
            //_Shader->setMat4f("modelMat", _UpdateFct(dt, _Model));
            _Model = _UpdateFct(dt, _Model);
        }

        /**
         * Render the entity
         * @cond The shader must have a "modelMat" uniform 4x4 matrix
        */
        void render() const {
            // set the model matrix in the gpu
            _Shader->use();
            _Shader->setMat4f("modelMat", _Model);
            _Material->setShaderValues(_Shader);
            _Mesh->render();
        }

        /**
         * Accessor to the shader
         * @return A pointer to the shader
        */
        const ShadersPointer getShader() const {
            return _Shader;
        }

        /**
         * Load a texture
         * @param fileName The texture file
        */
        void loadTexture(const std::string& fileName){
            // Loading the image in CPU memory using stb_image
            int width, height, numComponents;
            unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &numComponents, 0);
            glGenTextures(1, &_TexId); // generate an OpenGL texture container
            glBindTexture(GL_TEXTURE_2D, _TexId); // activate the texture
            // Setup the texture filtering option and repeat mode; check www.opengl.org for details.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // Fill the GPU texture with the data stored in the CPU image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // Free useless CPU memory
            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture
        }
};

#endif