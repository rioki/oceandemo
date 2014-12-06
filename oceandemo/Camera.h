
#ifndef _OD_CAMERA_H_
#define _OD_CAMERA_H_

#include "Entity.h"
#include "Shader.h"
#include "Vector3.h"
#include "Matrix44.h"

namespace od
{
    class Camera : public Entity
    {
    public:
        Camera();

        ~Camera();

        void setup(const Shader& shader) const;        

    private:
        float fov;
        float zNear;
        float zFar;

        mutable Matrix44 projection;
        mutable Matrix44 view;
    };
}

#endif
