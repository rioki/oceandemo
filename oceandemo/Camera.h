
#ifndef _OD_CAMERA_H_
#define _OD_CAMERA_H_

#include "Vector3.h"
#include "Shader.h"

namespace od
{
    class Camera 
    {
    public:
        Camera();

        ~Camera();

        void setup(Shader& shader);

    private:
        float fov;
        float zNear;
        float zFar;

        Vector3 position;
        //Vector4 orientation;
    };
}

#endif
