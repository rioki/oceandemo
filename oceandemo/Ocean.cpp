
#include "Ocean.h"

#include <cassert>
#include <ctime>
#include <tchar.h>
#include <GL/glew.h>

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
        //float 

        /*for (unsigned int i = 0; i < 200; i++)
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
        }*/

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
        if (grid.get_vertex_count() == 0)
        {
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            const_cast<Ocean*>(this)->create_grid(viewport[2], viewport[3]);
        }

        const_cast<Ocean*>(this)->compute_projector(camera.get_projection(), camera.get_view());

        shader.bind();
        
        camera.setup(shader);

        noise.bind(0);
        shader.set_uniform("uNoise", (int)0);
        shader.set_uniform("uTime", static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC));

        grid.draw(shader);
    }

    void Ocean::update(float t, float dt)
    {
        
    }

    void Ocean::create_grid(unsigned int x, unsigned int y)
    {
        assert(grid.get_vertex_count() == 0);

        unsigned int xi = x / 4;
        unsigned int yj = y / 4;
        float stepx = 1.0f / static_cast<float>(xi);
        float stepy = 1.0f / static_cast<float>(yj);

        for (unsigned int i = 0; i < xi; i++)
        {
            for (unsigned int j = 0; j < yj; j++)
            {
                float x = (-0.5 + i * static_cast<float>(stepx)) * 100.0f;
                float y = (-0.5 + j * static_cast<float>(stepy)) * 100.0f;

                unsigned int v = grid.add_vertex(rgm::vec3(x, y, 0.0), rgm::vec3(0.0, 0.0, 1.0), rgm::vec2(x, y));

                if ((i != 0) && (j != 0))
                {
                    unsigned int a = v - yj;
                    unsigned int b = v - yj - 1;
                    unsigned int c = v - 1;
                    unsigned int d = v;
                    
                    grid.add_face(a, b, c);
                    grid.add_face(a, c, d);
                }
            }
        }
        
    }

    void Ocean::compute_projector(const rgm::mat4& camera_projection, const rgm::mat4& camera_view)
    {
        
    }
}
