
#ifndef _OD_OCEAN_H_
#define _OD_OCEAN_H_

#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

namespace od
{    
    class Ocean : public Entity
    {
    public:
        Ocean();

        ~Ocean();

        void draw(Camera& camera) const override;

        void update(float t, float dt) override;

    private:
        Shader  shader;
        Mesh    plane;
        Texture noise;

        Ocean(const Ocean&) = delete;
        const Ocean& operator = (const Ocean&) = delete;
    };
}

#endif
