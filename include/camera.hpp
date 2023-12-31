#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glad/gl.h>
#include <memory>
#include <ostream>

class Camera;
using CameraPointer = std::shared_ptr<Camera>;

enum ProjectionType{ORTHO, PERSP};
enum CameraMovement{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

/**
 * A class representing the camera
*/
class Camera{
    private:
        /**
         * The center of the camera
        */
        glm::vec3 _Center = glm::vec3(0, 0, 3.0);

        /**
         * The look at
        */
        glm::vec3 _At = glm::vec3(0, 0, 0);

        /**
         * The up vector
        */
        glm::vec3 _Up = glm::vec3(0, 1, 0);

        /**
         * The camera's field of view, in degrees
        */
        GLfloat _Fov = 45.f;

        /**
         * The ratio between the width and the height of the image
        */
        GLfloat _Ratio = 1.f;

        /**
         * The distance before which geometry is excluded from the rasterization process
        */
        GLfloat _Near = 0.1f;

        /**
         * The distance after which the geometry is excluded from the rasterization process
        */
        GLfloat _Far = 100.f;

        /**
         * The camera's speed
        */
        GLfloat _Speed = 10.f;


    public:
        /**
         * Instantiate a default camera
        */
        Camera(){};


        /**
         * Instantiate a camera
         * @param center The camera's center
         * @param at The camera's looking point
         * @param up The camera's up vector
         * @param fov The camera's field of view
         * @param ratio The camera's aspect ratio
         * @param near The near plane
         * @param far The far plane
        */
        Camera(glm::vec3 center, glm::vec3 at, glm::vec3 up, GLfloat fov, GLfloat ratio, GLfloat near, GLfloat far){
            _Center = center;
            _At = at;
            _Up = up;
            _Fov = fov;
            _Ratio = ratio;
            _Near = near;
            _Far = far;
        }

        /**
         * Get the position of the camera
         * @return The position
        */
        const glm::vec3 getPosition() const {
            return _Center;
        }

        /**
         * Move the camera to a given position
         * @param newPos The new camera position
        */
        void moveTo(const glm::vec3& newPos){
            _Center = newPos;
        }

        /**
         * Set the camera's targer
         * @param target The new camera's target
        */
        void setTarget(const glm::vec3& target){
            _At = target;
        }

        /**
         * Set the camera's aspect ratio
         * @param newRatio The new ratio of the camera
        */
        void setRatio(GLfloat newRatio){
            if(newRatio <= 0){
                fprintf(stderr, "Aspect ratio must be positive!\n");
                return;
            }
            _Ratio = newRatio;
        }

        /**
         * Compute the view matrix
         * @return The view matrix
        */
        glm::mat4 getViewMatrix() const {
            return glm::lookAt(_Center, _At, _Up);
        }

        /**
         * Compute the projection matrix
         * @param type The type of projection
         * @return The projection matrix
        */
        glm::mat4 getProjectionMatrix(ProjectionType type) const {
            glm::mat4 res;

            switch(type){
                case ORTHO:{
                    float halfHeight = _Near * glm::tan(glm::radians(_Fov) / 2.0f);
                    float halfWidth = halfHeight * _Ratio;
                    GLfloat up = _Center.y-halfHeight;
                    GLfloat down = _Center.y+halfHeight;
                    GLfloat left = _Center.x-halfWidth;
                    GLfloat right = _Center.x+halfWidth;
                    res = glm::ortho(left, right, down, up, _Near, _Far);
                    break;
                }
                case PERSP:{
                    res = glm::perspective(glm::radians(_Fov), _Ratio, _Near, _Far);
                    break;
                }
            }

            return res;
        }

        /**
         * Display the camera
         * @param stream Where to display it
        */
        void print(std::ostream& stream){
            stream << "Center: " << _Center.x << ", " << _Center.y << ", " << _Center.z << "\n"
                    << "At: " << _At.x << ", " << _At.y << ", " << _At.z << "\n"
                    << "Up: " << _Up.x << ", " << _Up.y << ", " << _Up.z << "\n"
                    << "Fov: " << _Fov << "\n"
                    << "Ratio: " << _Ratio << "\n"
                    << "Near: " << _Near << "\n"
                    << "Far: " << _Far << std::endl;
        }

        /**
         * Set the fov
         * @param newFov The new fov
        */
        void setFov(GLfloat newFov){
            if (newFov <= 1.0f)
                _Fov = 1.0f;
            if (newFov >= 45.0f)
                _Fov = 45.0f; 
            _Fov = newFov;
        }

        /**
         * Get the fov
         * @return The fov as a constant
        */
        const GLfloat getFov() const {
            return _Fov;
        }

        /**
         * Move the camera
         * @param direction The movement direction
         * @param dt The 
        */
        void move(CameraMovement direction, GLfloat dt){
            float velocity = _Speed * dt;

            glm::vec3 front = glm::normalize(_At - _Center);
            glm::vec3 right = glm::normalize(glm::cross(front, _Up));

            switch(direction){
                case UP:
                    _Center += _Up * velocity;
                    _At += _Up * velocity;
                    break;
                case DOWN:
                    _Center -= _Up * velocity;
                    _At -= _Up * velocity;
                    break;
                case RIGHT:
                    _Center += right * velocity;
                    _At += right * velocity;
                    break;
                case LEFT:
                    _Center -= right * velocity;
                    _At -= right * velocity;
                    break;
            }
        }
};

#endif