#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include <glm/glm.hpp>
#include <memory>
#include "glad/gl.h"
#include "shaders.hpp"


class Material;
using MaterialPointer = std::shared_ptr<Material>;

/**
 * A class representing a material
*/
class Material{

    private:
        /**
         * The diffuse property
        */
        GLfloat _Diffuse = 1.0f;

        /**
         * The specular property
        */
        GLfloat _Specular = 1.0f;

        /**
         * The shininess
        */
        GLfloat _Shininess = 10.0f;

        /**
         * The ambient local illumination
        */
        glm::vec3 _Ambient = glm::vec3(0.f);


    public:
        /**
         * An empty constructor
        */
        Material(){}

        /**
         * A basic constructor
         * @param ambient The ambient property
         * @param diffuse The diffuse property
         * @param specular The specular property
         * @param shininess The shininess property
        */
        Material(const glm::vec3& ambient, GLfloat diffuse, GLfloat specular, GLfloat shininess){
            _Ambient = ambient;
            _Diffuse = diffuse;
            _Specular = specular;
            _Shininess = shininess;
        }

        /**
         * Set the values for a given shader
         * @param shader The shader to use
         * @cond Shader must have the correct "fAmbient", "fDiffuse", "fSpecular" and "fShininess" variables
        */
        void setShaderValues(const ShadersPointer& shader){
            shader->use();
            shader->setVec3f("fAmbient", _Ambient);
            shader->setFloat("fDiffuse", _Diffuse);
            shader->setFloat("fSpecular", _Specular);
            shader->setFloat("fShininess", _Shininess);
        }
};

#endif