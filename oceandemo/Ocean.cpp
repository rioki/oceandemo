
#include "Ocean.h"

#include <ctime>
#include <tchar.h>
#include <windows.h>

#include "fs.h"

namespace od
{    
    Ocean::Ocean()
    : //noise(1024, 1024)
      noise("../Assets/Ocean/Noise.png")
    {
        shader.set_vertex_code(fs::readfile("../Assets/Ocean/Ocean.vert.glsl"));
        shader.set_fragment_code(fs::readfile("../Assets/Ocean/Ocean.frag.glsl"));
        shader.compile();

        float start = -100.0f;
        float step  = 1.0;

        for (unsigned int i = 0; i < 200; i++)
        {
            for (unsigned int j = 0; j < 200; j++)
            {
                float x = start + i * static_cast<float>(step);
                float y = start + j * static_cast<float>(step);

                unsigned int v = plane.add_vertex(Vector3(x, y, 0.0), Vector3(0.0, 0.0, 1.0), Vector2(0.0f, 0.0f));

                if ((i != 0) && (j != 0))
                {
                    unsigned int a = v - 200;
                    unsigned int b = v - 201;
                    unsigned int c = v - 1;
                    unsigned int d = v;
                    
                    plane.add_face(a, b, c);
                    plane.add_face(a, c, d);
                }
            }
        }

        /*for (unsigned int i = 0; i < 1024; i++)
        {
            for (unsigned int j = 0; j < 1024; j++)
            {
                float x = static_cast<float>(i) / 255.0f;
                float y = static_cast<float>(j) / 255.0f;

                float v = snoise2(x, y) / 2.0 + 0.5;
                noise.set_pixel(i, j, Vector4(v, v, v, 1.0));
            }
        }*/
    }

    Ocean::~Ocean() {}

    void Ocean::draw(Camera& camera) const
    {
        shader.bind();
        
        camera.setup(shader);

        noise.bind(0);
        shader.set_uniform("uNoise", (int)0);
        shader.set_uniform("uTime", static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC));

        plane.draw(shader);
    }

    void Ocean::update(float t, float dt)
    {
        
    }
}
