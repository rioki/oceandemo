
#include "Camera.h"

#include <GL/glew.h>

namespace od
{
    Camera::Camera()
    : fov(45.0), zNear(0.1f), zFar(1000.0f) {}

    Camera::~Camera() {}

    void Camera::setup(const Shader& shader) const
    {
        // TODO compute projection and view only after changes
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        
        float aspect = static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]);

        projection = perspective(fov, aspect, zNear, zFar);

        Vector3 forward  = Vector3(transform * Vector4(1, 0, 0, 0));
        Vector3 up       = Vector3(transform * Vector4(0, 0, 1, 0));
        Vector3 position = Vector3(transform(3, 0), transform(3, 1), transform(3, 2)); 
        Vector3 target   = position + forward;
        view             = lookat(position, target, up);

        shader.set_uniform("aProjection", projection);
        shader.set_uniform("aView",       view);
    }

}
