#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "mesh.hpp"
#include "camera.hpp"
#include "shaders.hpp"

using Meshes = std::vector<MeshPointer>;

/**
 * A class that handle the scene
*/
class Scene{
    private:
        /**
         * The objects in the scene
        */
        Meshes _Meshes = {};

        /**
         * The scene's camera
        */
        CameraPointer _Camera = nullptr;

        /**
         * The scene's shader
        */
        ShadersPointer _Shader = nullptr;

    public:
        /**
         * A basic constructor
         * @param cam The scene's camera
         * @param shader The scene's shader
        */
        Scene(CameraPointer& cam, ShadersPointer& shader){
            _Camera = cam;
            _Shader = shader;
        }

        /**
         * Add a mesh to the scene
         * @param mesh The mesh to add
        */
        void addMesh(const MeshPointer& mesh){
            _Meshes.push_back(mesh);
        }

        /**
         * Initiate all the meshes
        */
        void initMeshes() const {
            for(auto mesh : _Meshes){
                mesh->initGpuGeometry();
            }
        }

        /**
         * Render all the meshes
        */
        void render() const {
            for(auto mesh : _Meshes){
                mesh->render();
            }
        }

        /**
         * Get the camera
         * @return The camera as a const
        */
        const CameraPointer getCamera() const {
            return _Camera;
        }

        /**
         * Get the shader
         * @return The shader as a const
        */
        const ShadersPointer getShader() const {
            return _Shader;
        }
};

#endif