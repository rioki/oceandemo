
#include "Camera.h"

namespace od
{
    Camera::Camera()
    : fov(45.0), zNear(0.1f), zFar(1000.0f), position(0, 0, 10) {}

    Camera::~Camera() {}

    void Camera::setup(Shader& shader) 
    {
    
    }

}
