
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <SDL.h>

#include "Vector4.h"

namespace od
{
    class Texture
    {
    public:

        Texture(unsigned int width, unsigned int height);

        Texture(const std::string& file);

        ~Texture();

        Vector4 get_pixel(unsigned int i, unsigned int j) const;

        void set_pixel(unsigned int i, unsigned int j, Vector4 value);

        void bind(unsigned int channel) const;

        void unbind(unsigned int channel) const;

        void upload() const;

        void release() const;

    private:        
        SDL_Surface* surface;
        mutable unsigned int glid;
    };
}

#endif
