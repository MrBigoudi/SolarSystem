#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "entity.hpp"
#include "camera.hpp"
#include "shaders.hpp"

using Entities = std::vector<EntityPointer>;

/**
 * A class that handle the scene
*/
class Scene{
    private:
        /**
         * The objects in the scene
        */
        Entities _Entities = {};

        /**
         * The scene's camera
        */
        CameraPointer _Camera = nullptr;

    public:
        /**
         * A basic constructor
         * @param cam The scene's camera
        */
        Scene(CameraPointer& cam){
            _Camera = cam;
        }

        /**
         * Add an entity to the scene
         * @param entity The entity to add
        */
        void addElement(const EntityPointer& entity){
            _Entities.push_back(entity);
        }

        /**
         * Initiate all the entities
        */
        void initMeshes() const {
            for(auto entity : _Entities){
                entity->init();
            }
        }

        /**
         * Render all the meshes
         * @cond All the entities must have shaders with "viewMat", "projMat" and "camPos" uniform variables
        */
        void render() const {
            const glm::mat4 model = glm::mat4(1.0f);
            const glm::mat4 view  = _Camera->getViewMatrix();
            const glm::mat4 proj  = _Camera->getProjectionMatrix(ProjectionType::PERSP);
            for(auto entity : _Entities){
                ShadersPointer shader = entity->getShader();
                shader->use();
                shader->setMat4f("viewMat", view);
                shader->setMat4f("projMat", proj);
                shader->setVec3f("camPos", _Camera->getPosition());
                entity->render();
            }
        }

        /**
         * Get the camera
         * @return The camera as a const
        */
        const CameraPointer getCamera() const {
            return _Camera;
        }
};

#endif