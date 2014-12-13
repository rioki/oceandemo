
#ifndef _OD_MESH_H_
#define _OD_MESH_H_

#include <vector>
#include <rgm/rgm.h>

#include "Shader.h"

namespace od
{
    class Mesh
    {
    public:
        
        Mesh();

        ~Mesh();

        unsigned int get_vertex_count() const;

        unsigned int get_face_count() const;

        unsigned int add_vertex(const rgm::vec3& vertex, const rgm::vec3& normal, const rgm::vec2& texcoord);

        void add_face(unsigned int a, unsigned int b, unsigned int c);

        void upload() const;

        void release() const;

        void draw(const Shader& shader) const;

    private:
        struct Face
        {
            unsigned int a;
            unsigned int b;
            unsigned int c;
        };

        std::vector<rgm::vec3> vertexes;
        std::vector<rgm::vec3> normals;
        std::vector<rgm::vec2> texcoords;
        std::vector<rgm::vec3> tangents;
        std::vector<Face>    faces;

        mutable unsigned int vao;
        mutable unsigned int buffers[5];
        
        void compute_tangents();

        Mesh(const Mesh&) = delete;
        const Mesh& operator = (const Mesh&) = delete;
    };
}

#endif
