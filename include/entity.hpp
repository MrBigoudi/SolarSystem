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

class Scene;
using ScenePointer = std::shared_ptr<Scene>;

class Entity;
using EntityPointer = std::shared_ptr<Entity>;

enum Filtering{
    LINEAR,
    NEAREST,
};

enum Wrapping{
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
};

/**
 * A class representing an entity in the scene
*/
class Entity {

    protected:
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
         * The texture Id
        */
        GLuint _TexId = 0;

        /**
         * A boolean to tell if the entity has a texture
        */
        GLboolean _HasTex = false;


    public:
        /**
         * A basic constructor
         * @param material The entity's material
         * @param shader The entity's shader
         * @param mesh The entity's mesh
        */
        Entity(const MaterialPointer& material, const ShadersPointer& shader, const MeshPointer& mesh = nullptr){
            _Mesh = mesh;
            _Material = material;
            _Shader = shader;
        }

        /**
         * Initiate the entity
        */
        virtual void init() const {
            _Mesh->initGpuGeometry();
            _Shader->setInt("fAlbedoTex", 0);
        }

        /**
         * Get the mesh
         * @return A pointer to the mesh
        */
        MeshPointer getMesh() const {
            return _Mesh;
        }

        /**
         * Get the model matrix of the entity
         * @return A copy of the model matrix
        */
        const glm::mat4 getModel() const {
            return _Model;
        }

        /**
         * Get the material
         * @return A pointer to the material
        */
        MaterialPointer getMaterial() const {
            return _Material;
        }

        /**
         * Update the entity
         * @param dt The delta time
        */
        virtual void update(GLfloat dt) = 0;

        /**
         * Render the entity
         * @cond The shader must have a "modelMat" uniform 4x4 matrix
        */
        virtual void render() const {
            // set the model matrix in the gpu
            _Shader->use();
            _Shader->setMat4f("modelMat", _Model);
            _Shader->setBool("useTex", _HasTex);
            _Material->setShaderValues(_Shader);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _TexId);
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
         * @param minFilter The minifying filter
         * @param magFilter The magnifying filter
         * @param wrapS The wrapping property of the texture for the S axis
         * @param wrapT The wrapping property of the texture for the T axis
        */
        void loadTexture(const std::string& fileName, Filtering minFilter = LINEAR, Filtering magFilter = LINEAR, Wrapping wrapS = REPEAT, Wrapping wrapT = REPEAT){
            // Loading the image in CPU memory using stb_image
            int width, height, numComponents;
            unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &numComponents, 0);
            glGenTextures(1, &_TexId); // generate an OpenGL texture container
            glBindTexture(GL_TEXTURE_2D, _TexId); // activate the texture
            // Setup the texture filtering option and repeat mode; check www.opengl.org for details.
            setMagFilter(magFilter);
            setMinFilter(minFilter);
            setWrapS(wrapS);
            setWrapT(wrapT);
            // Fill the GPU texture with the data stored in the CPU image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // Free useless CPU memory
            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture
            _HasTex = true;
        }

        /**
         * Add the entity to the given scene
         * @param scene The scene where to add the entity
        */
        virtual void addToScene(const ScenePointer& scene);

    private:
        /**
         * Set the minifyer filter
         * @param filter The filter to use
        */
        void setMinFilter(Filtering filter) const {
            switch (filter) {
                case LINEAR:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    break;
                case NEAREST:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    break;
            }
        }

        /**
         * Set the magnifyer filter
         * @param filter The filter to use
        */
        void setMagFilter(Filtering filter) const {
            switch (filter) {
                case LINEAR:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                case NEAREST:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
            }
        }

        /**
         * Set the texture wrapping for the S axis
         * @param wrap The wrapping to use
        */
        void setWrapS(Wrapping wrap) const {
            switch(wrap){
                case REPEAT:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    break;
                case MIRRORED_REPEAT:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                    break;
                case CLAMP_TO_EDGE:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    break;
                case CLAMP_TO_BORDER:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                    break;
            }
        }

        /**
         * Set the texture wrapping for the T axis
         * @param wrap The wrapping to use
        */
        void setWrapT(Wrapping wrap) const {
            switch(wrap){
                case REPEAT:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    break;
                case MIRRORED_REPEAT:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
                    break;
                case CLAMP_TO_EDGE:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    break;
                case CLAMP_TO_BORDER:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                    break;
            }
        }
};

#endif