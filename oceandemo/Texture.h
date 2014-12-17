
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <SDL.h>
#include <rgm/rgm.h>

namespace od
{
    enum ColorMode
    {
        RGB       = 3,
        RGBA      = 4
    };

    class Texture
    {
    public:

        Texture();

        Texture(unsigned int width, unsigned int height, ColorMode cm = RGBA);

        Texture(const std::string& file);

        Texture(const Texture& other);

        ~Texture();

        const Texture& operator = (const Texture& other);

        ColorMode get_color_mode() const;

        rgm::vec4 get_pixel(unsigned int i, unsigned int j) const;

        void set_pixel(unsigned int i, unsigned int j, rgm::vec4 value);

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
