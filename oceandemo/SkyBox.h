
#ifndef _OD_SKY_BOX_H_
#define _OD_SKY_BOX_H_

#include "Entity.h"

#include "Shader.h"
#include "Mesh.h"
#include "Cubemap.h"

namespace od
{
    class SkyBox : public Entity
    {
    public:
        SkyBox();

        virtual void draw(Camera& camera) const;
    
    private:
        Shader  shader;
        Mesh    mesh;
        Cubemap cubemap;
    };
}

#endif
