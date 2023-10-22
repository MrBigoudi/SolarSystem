#ifndef __PLANET_HPP__
#define __PLANET_HPP__

#include "entity.hpp"
#include "errorHandler.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "mesh.hpp"
#include <memory>

class Planet;
using PlanetPointer = std::shared_ptr<Planet>;

/**
 * A class to represent planets
*/
class Planet : public Entity{

    private:
        /**
         * The planet's position
        */
        glm::vec3 _Position = glm::vec3(0.0f);

        /**
         * The common mesh for all planets
        */
        static MeshPointer _SphereMesh;

        /**
         * The planet it orbits around
        */
        PlanetPointer _OrbitCenter = nullptr;

        /**
         * The orbit speed
        */
        GLfloat _OrbitSpeed = 0.0f;

        /**
         * The orbit radius
        */
        GLfloat _OrbitRadius = 0.0f;

        /**
         * The orbit axis
        */
        glm::vec3 _OrbitAxis = glm::vec3(0.f,1.f,0.f);

        /**
         * The rotation speed
        */
        GLfloat _RotationSpeed = 0.0f;

        /**
         * The rotation axis
        */
        glm::vec3 _RotationAxis = glm::vec3(0.f,1.f,0.f);

        /**
         * The planet size
        */
        GLfloat _Size = 1.0f;

        /**
         * Test if the object has been initialized
        */
        GLboolean _IsInitialized = false;

    private:
        /**
         * Get the static sphere mesh
        */
        static MeshPointer getSphereMesh() {
            if (_SphereMesh == nullptr) {
                _SphereMesh = MeshPointer(new Mesh(Mesh::unitSphere()), &Planet::null_deleter);
            }
            return _SphereMesh;
        }

        /**
         * A custom deleter for the static shared pointer
        */
        static void null_deleter(Mesh*){
            // don't do anything
        }

    public:
        /**
         * A basic constructor
         * @param material The entity's material
         * @param shader The entity's shader
        */
        Planet(const MaterialPointer& material, const ShadersPointer& shader)
            : Entity(material, shader){
            _Mesh = MeshPointer(new Mesh(getSphereMesh()));
            //_Mesh = MeshPointer(new Mesh(Mesh::unitSphere()));
        }

        /**
         * Init a planet without an orbit
         * @param size The planet's size
         * @param rotationSpeed The rotation's speed
         * @param rotationAxis The rotation angle axis
         * @param position The planet's position
        */
        void init(GLfloat size, GLfloat rotationSpeed, glm::vec3 rotationAxis, glm::vec3 position = glm::vec3(0.0f)){
            _Size = size;
            _RotationSpeed = rotationSpeed;
            _RotationAxis = rotationAxis;
            _Position = position;
            _Model = glm::scale(glm::translate(_Model, position), glm::vec3(size));
            _IsInitialized = true;
        }

        /**
         * Init the planets
         * @param size The planet's size
         * @param rotationSpeed The rotation's speed
         * @param rotationAxis The rotation angle axis
         * @param orbitSpeed The orbit's rotation speed
         * @param orbitAxis The orbit angle axis
         * @param orbitRadius The orbit's radius
         * @param orbitCenter The center of the planet's orbit
        */
        void init(GLfloat size, GLfloat rotationSpeed, glm::vec3 rotationAxis, 
                    GLfloat orbitSpeed, glm::vec3 orbitAxis, GLfloat orbitRadius, 
                    const PlanetPointer& orbitCenter){
            _Size = size;
            _RotationSpeed = rotationSpeed;
            _RotationAxis = rotationAxis;
            _OrbitRadius = orbitRadius;
            _OrbitSpeed = orbitSpeed;
            _OrbitCenter = orbitCenter;
            _OrbitAxis = orbitAxis;
            _Model = glm::scale(glm::translate(_OrbitCenter->_Model, glm::vec3(orbitRadius,0.,0.)), glm::vec3(size));
            updatePosition();
            _IsInitialized = true;
        }

        /**
         * Update the planet
         * @param dt The delta time
         * @cond The planet must have been initialized
         * @see init
        */
        void update(GLfloat dt) override {
            if(!_IsInitialized){
                fprintf(stderr, "The planet must be initialized properly before update! Call its `init` function!\n");
                ErrorHandler::handle(ErrorCodes::NOT_INITALIZED);
            }
            // rotate arround itself
            _Model = glm::rotate(_Model, _RotationSpeed, _RotationAxis);
            // orbit arround parent
            if(_OrbitCenter != nullptr){
                glm::mat4 orbit = glm::rotate(glm::translate(glm::mat4(1.0f), _OrbitCenter->_Position), _OrbitSpeed, _OrbitAxis);
                _Model = orbit*_Model;
            }
            updatePosition();
        }

    private:
        /**
         * Update the position
        */
        void updatePosition(){
            _Position = _Model*glm::vec4(0.0f);
        }

};

#endif