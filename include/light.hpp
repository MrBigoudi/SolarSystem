#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include "errorHandler.hpp"
#include "shaders.hpp"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <memory>

#include "entity.hpp"

class Light;
using LightPointer = std::shared_ptr<Light>;

enum LightType{
    PointLight,
    DirectionalLight,
};

/**
 * A class representing a light
*/
class Light{

    private:
        /**
         * The light's position
        */
        glm::vec3 _Position = glm::vec3(1.0f);

        /**
         * The light's color
        */
        glm::vec3 _Color = glm::vec3(1.0f);

        /**
         * The light's type
        */
        LightType _Type = PointLight;

        /**
         * The entity containing the light
        */
        EntityPointer _Entity = nullptr;


    public:
        /**
         * A basic constructor
         * @param type The type of light
         * @param pos The light's position
         * @param col The light's color
         * @param entity The entity containing the light
        */
        Light(LightType type, const glm::vec3& pos, const glm::vec3& col, const EntityPointer& entity){
            _Type = type;
            _Position = pos;
            _Color = col;
            _Entity = entity;
        }


        /**
         * Send the light to the gpu
         * @param shader The shader to use
         * @param name The name of the light
        */
        void sendGPU(const ShadersPointer& shader, const std::string& name){
            if(!_Entity){
                fprintf(stderr, "The entity must be initialized to setup the light!\n");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
            shader->setVec3f(name + ".position", _Position);
            shader->setVec3f(name + ".color", _Color);
            shader->setMat4f(name + ".model", _Entity->getModel());
        }

        /**
         * Get the type of the light
         * @return The type
        */
        LightType getType() const {
            return _Type;
        }
};

#endif