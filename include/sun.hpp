#ifndef __SUN_HPP__
#define __SUN_HPP__

#include "entity.hpp"
#include "light.hpp"
#include "planet.hpp"
#include <memory>
#include "scene.hpp"

class Sun;
using SunPointer = std::shared_ptr<Sun>;

/**
 * A class representing a sun
*/
class Sun : public Planet{

    private:
        /**
         * The light source of the sun
        */
        LightPointer _Light = nullptr;

    public:
        /**
         * A basic constructor
         * @param material The entity's material
         * @param shader The entity's shader
         * @param lightPos The light's position
         * @param lightCol The light's color
        */
        Sun(const MaterialPointer& material, const ShadersPointer& shader, const glm::vec3& lightPos, const glm::vec3& lightCol)
            : Planet(material, shader){
            _Light = LightPointer(new Light(LightType::PointLight, lightPos, lightCol, EntityPointer(this)));
        }

        /**
         * Add the entity to the given scene
         * @param scene The scene where to add the entity
        */
        void addToScene(const ScenePointer& scene) override {
            Entity::addToScene(scene);
            scene->addLight(_Light);
        }
};

#endif