
#include "Camera.h"

#include "Shader.h"

namespace od
{
    Camera::Camera()
    : fov(45.0f), aspect(16.0f / 9.0f), near(0.1f), far(1000.0f) {}

    Camera::~Camera() {}

    void Camera::set_fov(float value)
    {
        fov = value;
    }

    float Camera::get_fov() const
    {
        return fov;
    }

    void Camera::set_aspect(float value)
    {
        aspect = value;
    }

    float Camera::get_aspect() const
    {
        return aspect;
    }
        
    void Camera::set_near(float value)
    {
        near = value;
    }

    float Camera::get_near() const
    {
        return near;
    }

    void Camera::set_far(float value)
    {
        far = value;
    }

    float Camera::get_far() const
    {
        return far;
    }

    rgm::mat4 Camera::get_projection() const
    {
        return rgm::perspective(fov, aspect, near, far);
    }

    rgm::mat4 Camera::get_view() const
    {
        rgm::vec3 forward  = rgm::vec3(transform * rgm::vec4(1, 0, 0, 0));
        rgm::vec3 up       = rgm::vec3(transform * rgm::vec4(0, 0, 1, 0));
        rgm::vec3 position = rgm::vec3(transform[3]); 
        rgm::vec3 target   = position + forward;
        return rgm::lookat(position, target, up);
    }

    void Camera::setup(const Shader& shader) const
    {
        shader.set_uniform("aProjection", get_projection());
        shader.set_uniform("aView",       get_view());
    }

}
