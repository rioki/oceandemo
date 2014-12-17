
#include "Texture.h"

#include <stdexcept>
#include <GL/glew.h>
#include <SDL_image.h>

namespace od
{
    Texture::Texture()
    : surface(nullptr), glid(0) {}

    Texture::Texture(unsigned int width, unsigned int height, ColorMode cm)
    : Texture()
    {
        Uint32 rmask, gmask, bmask, amask;

        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            if (cm == RGBA)
            {
                amask = 0x000000ff;
            }
            else
            {
                amask = 0x00000000;
            }
        #else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            if (cm == RGBA)
            {
                amask = 0xff000000;
            }
            else
            {
                amask = 0x00000000;
            }
        #endif
        unsigned int bpp = cm == RGBA ? 32 : 24;


        surface = SDL_CreateRGBSurface(0, width, height, bpp, rmask, gmask, bmask, amask);
        if (surface == NULL) 
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    Texture::Texture(const std::string& file)
    : Texture()
    {
        surface = IMG_Load(file.c_str());
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
    }

    Texture::Texture(const Texture& other)
    : surface(other.surface), glid(0)
    {   
        if (surface)
        {
            surface->refcount++;
        }        
    }

    Texture::~Texture()
    {
        release();
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    const Texture& Texture::operator = (const Texture& other)
    {
        if (this != &other)
        {
            release();
            if (surface != nullptr)
            {
                SDL_FreeSurface(surface);
                surface = nullptr;
            }

            surface = other.surface;
            if (surface)
            {
                surface->refcount++;
            }
        }
        return *this;
    }

    ColorMode Texture::get_color_mode() const
    {
        return static_cast<ColorMode>(surface->format->BytesPerPixel);
    }

    Uint32 getpixel(SDL_Surface *surface, int x, int y)
    {
        int bpp = surface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

        switch(bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
        }
    }

    rgm::vec4 Texture::get_pixel(unsigned int i, unsigned int j) const
    {
        if (i < surface->w && i >= 0 &&
             j < surface->h && j >= 0)
        {
            Uint32 p = getpixel(surface, i, j);
            Uint8 r, g, b, a;
            SDL_GetRGBA(p, surface->format, &r, &g, &b, &a);
            return rgm::vec4(static_cast<float>(r)/255.0,
                             static_cast<float>(g)/255.0,
                             static_cast<float>(b)/255.0,
                             static_cast<float>(a)/255.0);
        }
        else
        {
            throw std::invalid_argument("index out of bounds");
        }
    }

    void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
    {
        int bpp = surface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to set */
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

        switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
        }
    }

    void Texture::set_pixel(unsigned int i, unsigned int j, rgm::vec4 value)
    {
        if (surface->refcount > 1)
        {
            // TODO duplicate surface
        }

        if (i < surface->w && i >= 0 &&
            j < surface->h && j >= 0)
        {
            Uint8 r = static_cast<Uint8>(value[0] * 256.0f);
            Uint8 g = static_cast<Uint8>(value[1] * 256.0f);
            Uint8 b = static_cast<Uint8>(value[2] * 256.0f);
            Uint8 a = static_cast<Uint8>(value[3] * 256.0f);
            Uint32 p = SDL_MapRGBA(surface->format, r, g, b, a);
            putpixel(surface, i, j, p);
        }
        else
        {
            throw std::invalid_argument("index out of bounds");
        }
    }

    void Texture::bind(unsigned int channel) const
    {
        if (surface == nullptr)
        {
            unbind(channel);
            return;
        }

        if (glid == 0)
        {
            upload();
        }

        glActiveTexture(GL_TEXTURE0 + channel);
        glBindTexture(GL_TEXTURE_2D, glid);
    }

    void Texture::unbind(unsigned int channel) const
    {
        glActiveTexture(GL_TEXTURE0 + channel);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::upload() const
    {
        glGenTextures(1, &glid);                    
        glBindTexture(GL_TEXTURE_2D, glid);
        
        // TODO mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        int mode = 0;
        switch (surface->format->BytesPerPixel)
        {
            case 3:
                mode = GL_RGB;    
                break;
            case 4:
                mode = GL_RGBA;
                break;
            default:
                throw std::logic_error("Unknown pixel format.");
        }
    
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);      
    }

    void Texture::release() const
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
        }
    }
}
