
#ifndef _OD_SHADER_H_
#define _OD_SHADER_H_

#include <string>

#include "Matrix44.h"

namespace od
{
    class Shader
    {
    public:

        Shader();

        ~Shader();

        void set_vertex_code(const std::string& value);

        const std::string& get_vertex_code() const;

        void set_fragment_code(const std::string& value);

        const std::string& get_fragment_code() const;

        void compile();

        void bind();

        void unbind();
        
        void release();
        
        int get_attribute_location(const std::string& name) const;

        void set_uniform(const std::string& name, const Matrix44& value);

    private:
        std::string vertex_code;
        std::string fragment_code;
        unsigned int program_id;

        Shader(const Shader&) = delete;
        const Shader& operator = (const Shader&) = delete;
    };
}

#endif
