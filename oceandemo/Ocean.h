
#ifndef _OD_OCEAN_H_
#define _OD_OCEAN_H_

#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

namespace od
{    
    class Ocean : public Entity
    {
    public:
        Ocean();

        ~Ocean();

        void draw(Camera& camera) const override;

    private:
        Shader shader;
        Mesh   plane;

        Ocean(const Ocean&) = delete;
        const Ocean& operator = (const Ocean&) = delete;
    };
}

#endif
