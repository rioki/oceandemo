
#ifndef _OD_MESH_H_
#define _OD_MESH_H_

#include <vector>
#include "Vector3.h"
#include "Vector2.h"

#include "Shader.h"

namespace od
{
    class Mesh
    {
    public:
        
        Mesh();

        ~Mesh();

        unsigned int add_vertex(const Vector3& vertex, const Vector3& normal, const Vector2& texcoord);

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

        std::vector<Vector3> vertexes;
        std::vector<Vector3> normals;
        std::vector<Vector2> texcoords;
        std::vector<Vector3> tangents;
        std::vector<Face>    faces;

        mutable unsigned int vao;
        mutable unsigned int buffers[5];
        
        void compute_tangents();

        Mesh(const Mesh&) = delete;
        const Mesh& operator = (const Mesh&) = delete;
    };
}

#endif
