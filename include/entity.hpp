#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <memory>

#include "mesh.hpp"
#include "material.hpp"
#include "shaders.hpp"

class Entity;
using EntityPointer = std::shared_ptr<Entity>;

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

};

#endif