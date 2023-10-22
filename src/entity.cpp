#include "scene.hpp"
#include "entity.hpp"

/**
 * Add the entity to the given scene
 * @param scene The scene where to add the entity
*/
void Entity::addToScene(const ScenePointer& scene){
    scene->addElement(EntityPointer(this));
}