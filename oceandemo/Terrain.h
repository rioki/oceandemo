
#ifndef _OD_TERRAIN_H_
#define _OD_TERRAIN_H_

#include "Entity.h"

#include <vector>
#include <rgm/rgm.h>

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

namespace od
{
    class Terrain : public Entity
    {
    public:

        Terrain(unsigned int width = 2048, unsigned int height = 2048);

        void generate();

        void draw(Camera& camera) const override;

        void update(float t, float dt) override;

    private:
        rgm::ivec2 size;

        struct Point
        {
            Point();

            float     rock;
            float     dirt;
            float     vegetation;
            float     watter;
            rgm::vec3 watter_flow;
        };

        std::vector<Point> points;

        Mesh      plane512;        
        Shader    ground_shader;        
        Texture   ground_texture;
        float     rock_min;
        float     rock_max;
        Shader    watter_shader;
        Texture   watter_texture;

        void create_plane512();
        void sync_textures();

    };
}

#endif
