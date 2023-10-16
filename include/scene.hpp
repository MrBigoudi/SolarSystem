#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "entity.hpp"
#include "camera.hpp"
#include "errorHandler.hpp"
#include "shaders.hpp"
#include "light.hpp"

using Entities = std::vector<EntityPointer>;
using PointLights = std::vector<LightPointer>;
using DirectonalLights = std::vector<LightPointer>;

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
         * The point lights in the scene
        */
        PointLights _PointLights = {};

        /**
         * The number of point lights
        */
        GLuint _NbPointLights = 0;

        /**
         * The directional lights in the scene
        */
        DirectonalLights _DirectionalLights = {};

        /**
         * The number of directional lights
        */
        GLuint _NbDirectionalLights = 0;

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
            if(!entity){
                fprintf(stderr, "Can't add an empty entity to the scene!");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED, ErrorLevel::WARNING);
                return;
            }
            _Entities.push_back(entity);
        }

        /**
         * Add a point light to the scene
         * @param light The light to add
        */
        void addPointLight(const LightPointer& light){
            if(light->getType() != LightType::PointLight){
                fprintf(stderr, "Must assign a point light to the scene's point lights!");
                ErrorHandler::handle(ErrorCodes::WRONG_TYPE, ErrorLevel::WARNING);
                return;
            }
            _PointLights.push_back(light);
            _NbPointLights++;
        }

        /**
         * Add a directional light to the scene
         * @param light The light to add
        */
        void addDirectionalLight(const LightPointer& light){
            if(light->getType() != LightType::DirectionalLight){
                fprintf(stderr, "Must assign a directional light to the scene's directional lights!");
                ErrorHandler::handle(ErrorCodes::WRONG_TYPE, ErrorLevel::WARNING);
                return;
            }
            _DirectionalLights.push_back(light);
            _NbDirectionalLights++;
        }

        /**
         * Add a light to the scene
         * @param light The light to add
        */
        void addLight(const LightPointer& light){
            if(!light){
                fprintf(stderr, "Can't add an empty light to the scene!");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED, ErrorLevel::WARNING);
                return;
            }

            switch(light->getType()){
                case LightType::PointLight:
                    addPointLight(light);
                    return;
                case LightType::DirectionalLight:
                    addDirectionalLight(light);
                    return;
            }
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
         * @cond Shaders must have the correct light uniform variables
        */
        void render() const {
            // get the coordinate matrices
            const glm::mat4 model = glm::mat4(1.0f);
            const glm::mat4 view  = _Camera->getViewMatrix();
            const glm::mat4 proj  = _Camera->getProjectionMatrix(ProjectionType::PERSP);

            // render the enetities
            for(auto entity : _Entities){
                ShadersPointer shader = entity->getShader();
                shader->use();

                // set the matrices
                shader->setMat4f("viewMat", view);
                shader->setMat4f("projMat", proj);
                shader->setVec3f("camPos", _Camera->getPosition());

                // set the point lights
                shader->setInt("NB_POINT_LIGHTS", _NbPointLights);
                for(GLuint i=0; i<_NbPointLights; i++){
                    std::string name = "pointLights[" + std::to_string(i) + "]";
                    _PointLights[i]->sendGPU(shader, name);
                }

                // set the directional lights
                shader->setInt("NB_DIRECTIONAL_LIGHTS", _NbDirectionalLights);
                for(GLuint i=0; i<_NbDirectionalLights; i++){
                    std::string name = "directionalLights[" + std::to_string(i) + "]";
                    _DirectionalLights[i]->sendGPU(shader, name);
                }

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