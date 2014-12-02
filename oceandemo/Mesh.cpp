
#include "Mesh.h"

#include <cassert>
#include <GL/glew.h>

namespace od
{
    enum BufferId
    {
        VERTEX_BUFFER   = 0,
        NORMAL_BUFFER   = 1,
        TEXCOORD_BUFFER = 2,
        TANGENT_BUFFER  = 3,
        INDEX_BUFFER    = 4
    };

    Mesh::Mesh() 
    : vao(0)
    {
        std::memset(&buffers, 0, 5 * sizeof(unsigned int));
    }

    Mesh::~Mesh() 
    {
        release();
    }

    unsigned int Mesh::add_vertex(const Vector3& vertex, const Vector3& normal, const Vector2& texcoord)
    {
        vertexes.push_back(vertex);
        normals.push_back(normal);
        texcoords.push_back(texcoord);

        return vertexes.size() - 1;
    }

    void Mesh::add_face(unsigned int a, unsigned int b, unsigned int c)
    {
        if ((a >= vertexes.size()) || (b >= vertexes.size()) || (c >= vertexes.size()))
        {
            throw std::invalid_argument("Mesh::add_face: index out of bounds");
        }
        
        Face face = {a, b, c};
        faces.push_back(face); 
    }

    void Mesh::upload()
    {
        assert(vertexes.size() == normals.size() && vertexes.size() == texcoords.size());

        if (tangents.size() != vertexes.size())
        {
            compute_tangents();
        }

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(5, buffers);
        
        size_t vcount = vertexes.size();
        size_t fcount = faces.size();

        glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);    
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &vertexes[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);    
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &normals[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);    
        glBufferData(GL_ARRAY_BUFFER, vcount * 2 * sizeof(float), &texcoords[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[TANGENT_BUFFER]);    
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &tangents[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);    
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, fcount * 3 * sizeof(unsigned int), &faces[0], GL_STATIC_DRAW);  
                
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void Mesh::release()
    {
        if (buffers[0] != 0)
        {
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(5, buffers);
            std::memset(&buffers, 0, 5 * sizeof(unsigned int));
        }
    }

    void Mesh::draw(Shader& shader) const    
    {
        if (buffers[0] == 0)
        {
            const_cast<Mesh*>(this)->upload(); 
        }

        // NOTE: we may not need the glBindBuffer here
        glBindVertexArray(vao);

        int vertex_location   = shader.get_attribute_location("aVertex");
        int normal_location   = shader.get_attribute_location("aNormal");
        int texcoord_location = shader.get_attribute_location("aTexCoord");
        int tangent_location  = shader.get_attribute_location("aTangent");
        
        if (vertex_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
            glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(vertex_location);
        }
        
        if (normal_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);
            glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(normal_location);
        }
        
        if (texcoord_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);
            glVertexAttribPointer(texcoord_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(texcoord_location);
        }
        
        if (tangent_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[TANGENT_BUFFER]);
            glVertexAttribPointer(tangent_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(tangent_location);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);        
        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  

        if (vertex_location != -1)
        {
            glDisableVertexAttribArray(vertex_location);
        }

        if (normal_location != -1)
        {
            glDisableVertexAttribArray(normal_location);
        }

        if (texcoord_location != -1)
        {
            glDisableVertexAttribArray(texcoord_location);
        }
        
        if (texcoord_location != -1)
        {
            glDisableVertexAttribArray(tangent_location);
        }

        glBindVertexArray(0);
    }

    void Mesh::compute_tangents()
    {
        std::vector<Vector3> tan1(vertexes.size(), Vector3(0, 0, 0));
        std::vector<Vector3> tan2(vertexes.size(), Vector3(0, 0, 0));
        
        for (Face face : faces)
        {
            Vector3 v1 = Vector3(vertexes[face.a]);
            Vector3 v2 = Vector3(vertexes[face.b]);
            Vector3 v3 = Vector3(vertexes[face.c]);
            
            Vector2 w1 = texcoords[face.a];
            Vector2 w2 = texcoords[face.b];
            Vector2 w3 = texcoords[face.c];
            
            float x1 = v2.x - v1.x;
            float x2 = v3.x - v1.x;
            float y1 = v2.y - v1.y;
            float y2 = v3.y - v1.y;
            float z1 = v2.z - v1.z;
            float z2 = v3.z - v1.z;
            
            float s1 = w2.x - w1.x;
            float s2 = w3.x - w1.x;
            float t1 = w2.y - w1.y;
            float t2 = w3.y - w1.y;
            
            float r = 1.0F / (s1 * t2 - s2 * t1);
            Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
            Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);
            
            tan1[face.a] = tan1[face.a] + sdir;
            tan1[face.b] = tan1[face.b] + sdir;
            tan1[face.c] = tan1[face.c] + sdir;
            
            tan2[face.a] = tan2[face.a] + tdir;
            tan2[face.b] = tan2[face.b] + tdir;
            tan2[face.c] = tan2[face.c] + tdir;
        }
        
        tangents.resize(vertexes.size());
        for (unsigned int i = 0; i < vertexes.size(); i++)
        {
            Vector3& n = normals[i];
            Vector3& t1 = tan1[i];
            Vector3& t2 = tan2[i];
            
            if (dot(cross(n, t1), t2) < 0.0f) 
            {
                tangents[i] = -normalize(t1 - n * dot(n, t1));
            }
            else
            {
                tangents[i] = normalize(t1 - n * dot(n, t1));
            }            
        }
    }
}
