
#include "Terrain.h"

#include <ctime>
#include <algorithm>

#include "fs.h"
#include "snoise.h"

#include "Camera.h"

using rgm::vec2;
using rgm::vec3;
using rgm::vec4;
using rgm::mat3;
using rgm::mat4;

namespace od
{
    Terrain::Point::Point()
    : rock(0.0), dirt(0.0), vegetation(0.0), watter(0.0), watter_flow(0) {}

    Terrain::Terrain(unsigned int width, unsigned int height)
    : size(width, height), rock_min(0.0), rock_max(0.0)
    {
        if (width % 512 != 0 || height % 512 != 0)
        {
            throw std::invalid_argument("Width and height must be powers of 512.");
        }

        points = std::vector<Point>(width * height);

        ground_shader.set_vertex_code(fs::readfile("../Assets/Terrain/Ground.vert.glsl"));
        ground_shader.set_fragment_code(fs::readfile("../Assets/Terrain/Ground.frag.glsl"));
        ground_shader.compile();

        ground_texture = Texture(width, height, RGB /*, FLOAT*/);
        
        watter_shader.set_vertex_code(fs::readfile("../Assets/Terrain/Watter.vert.glsl"));
        watter_shader.set_fragment_code(fs::readfile("../Assets/Terrain/Watter.frag.glsl"));
        watter_shader.compile();

        watter_texture = Texture(width, height, RGBA /*, FLOAT*/);
        
        create_plane512();
    }

    void Terrain::generate()
    {
        float hight1 = 50.0f;
        float scale1 = 512.0f;

        float hight2 = 10.0f;
        float scale2 = 128.0f;

        float hight3 = 2.0f;
        float scale3 = 32.0f;

        for (unsigned int x = 0; x < size[0]; x++)
        {
            for (unsigned int y = 0; y < size[1]; y++)
            {
                assert(x * size[0] + y < points.size());
                
                float rock = snoise2(x / scale1, y / scale1) * hight1 + 
                             snoise2(x / scale2, y / scale2) * hight2 + 
                             snoise2(x / scale3, y / scale3) * hight3;
                
                points[x * size[0] + y].rock = rock;
            }
        }

        sync_textures();
    }

    void Terrain::draw(Camera& camera) const 
    {
        ground_shader.bind();
        
        camera.setup(ground_shader);

        // position?
        unsigned int xcnt  = size[0] / 512;
        unsigned int ycnt  = size[1] / 512;
        vec2         hs    = vec2(size) / 2.0f;
        mat4         model;
        
        ground_texture.bind(0);
        ground_shader.set_uniform("uGround", 0);
        ground_shader.set_uniform("uRockMin", rock_min);
        ground_shader.set_uniform("uRockMax", rock_max);
        
        for (unsigned int x = 0; x < xcnt; x++)
        {
            for (unsigned int y = 0; y < ycnt; y++)
            {
                // is this not xcnt to short?
                vec2 pos = -hs + vec2(x * 512.0f, y * 512.0f);

                model = mat4(1);
                model = rgm::translate(model, vec3(pos));

                ground_shader.set_uniform("uModelMatrix", model);
                
                float tx = (float)x / (float)xcnt;
                float ty = (float)y / (float)ycnt;

                mat4 tm(1);
                tm = rgm::translate(tm, vec3((float)x / (float)xcnt, (float)y / (float)ycnt, 0.0));
                tm = rgm::scale(tm, vec3(1.0/(float)xcnt, 1.0/(float)ycnt, 1.0));
                
                ground_shader.set_uniform("uTextureMatrix", tm);


                plane512.draw(ground_shader);
            }
        }
    }

    void Terrain::update(float t, float dt) 
    {
    
    }

    void Terrain::create_plane512()
    {
        // resolution 1m = 1 node
        // note, this may actually be 513 since there is one overlap
        assert(plane512.get_vertex_count() == 0);

        for (unsigned int i = 0; i < 513; i++)
        {
            for (unsigned int j = 0; j < 512; j++)
            {
                float x = (j % 2 == 0) ? static_cast<float>(i) : static_cast<float>(i) + 0.5f;
                float y = static_cast<float>(j);

                unsigned int v = plane512.add_vertex(rgm::vec3(x, y, 0.0), rgm::vec3(0.0, 0.0, 1.0), rgm::vec2(x/512.0f, y/512.0f));

                if ((i != 0) && (j != 0))
                {
                    unsigned int a = v - 512;
                    unsigned int b = v - 513;
                    unsigned int c = v - 1;
                    unsigned int d = v;
                    
                    plane512.add_face(a, b, c);
                    plane512.add_face(a, c, d);
                }
            }
        }
    }

    void Terrain::sync_textures()
    {
        rock_min = 0;
        rock_max = 0;

        for (unsigned int x = 0; x < size[0]; x++)
        {
            for (unsigned int y = 0; y < size[1]; y++)
            {
                Point& point = points[x * size[0] + y];

                rock_min = std::min(rock_min, point.rock);
                rock_max = std::max(rock_max, point.rock);
            }
        }

        float rock_dst = rock_max - rock_min;

        for (unsigned int x = 0; x < size[0]; x++)
        {
            for (unsigned int y = 0; y < size[1]; y++)
            {
                assert(x * size[0] + y < points.size());
                Point& point = points[x * size[0] + y];

                float rock = (point.rock - rock_min) / rock_dst;

                ground_texture.set_pixel(x, y, vec4(rock, 0.0, 0.0, 0.0));
            }
        }
    }
}
