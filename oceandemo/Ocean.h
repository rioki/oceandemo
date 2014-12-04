
#ifndef _OD_OCEAN_H_
#define _OD_OCEAN_H_

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

namespace od
{    
    class Ocean
    {
    public:
        Ocean();

        ~Ocean();

        void draw(Camera& camera);

    private:
        Shader shader;
        Mesh   plane;

        Ocean(const Ocean&) = delete;
        const Ocean& operator = (const Ocean&) = delete;
    };
}

#endif
