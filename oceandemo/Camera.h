
#ifndef _OD_CAMERA_H_
#define _OD_CAMERA_H_

#include <rgm/rgm.h>

#include "Entity.h"

namespace od
{
    class Shader;

    class Camera : public Entity
    {
    public:
        Camera();

        ~Camera();

        void set_fov(float value);

        float get_fov() const;

        void set_aspect(float value);

        float get_aspect() const;
        
        void set_near(float value);       

        float get_near() const;

        void set_far(float value);       

        float get_far() const;

        rgm::mat4 get_projection() const;

        rgm::mat4 get_view() const;

        void setup(const Shader& shader) const;        

    private:
        float fov;
        float aspect;
        float near;
        float far;
    };
}

#endif
