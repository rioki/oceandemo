
#include "Cubemap.h"

#include <cstring>
#include <cassert>
#include <SDL_image.h>
#include <GL/glew.h>

namespace od
{
    Cubemap::Cubemap()
    : glid(0)
    {
        std::memset(textures, 0, 6*sizeof(SDL_Surface*));
    }

    Cubemap::~Cubemap() 
    {
        relase();

        for (unsigned int i = 0; i < 6; i++)
        {
            if (textures[i] != nullptr)
            {
                SDL_FreeSurface(textures[i]);
                textures[i] = nullptr;
            }
        }        
    }
    
    void Cubemap::load(CubeMapOrientation o, const std::string& file)
    {
        // TODO add reload code
        assert(glid == 0);
        
        textures[o] = IMG_Load(file.c_str());
        if (textures[o] == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
    }

    void Cubemap::bind(unsigned int channel) const
    {
        if (glid == 0)
        {
            upload();
        }

        glActiveTexture(GL_TEXTURE0 + channel);
        glBindTexture(GL_TEXTURE_CUBE_MAP, glid);
    }

    void Cubemap::unbind(unsigned int channel) const
    {
        glActiveTexture(GL_TEXTURE0 + channel);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void Cubemap::upload() const
    {
        glGenTextures(1, &glid);
        glBindTexture(GL_TEXTURE_CUBE_MAP, glid);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, textures[XPOS]->w, textures[XPOS]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[XPOS]->pixels); 
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, textures[XNEG]->w, textures[XNEG]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[XNEG]->pixels); 
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, textures[YPOS]->w, textures[YPOS]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[YPOS]->pixels); 
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, textures[YNEG]->w, textures[YNEG]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[YNEG]->pixels); 
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, textures[ZPOS]->w, textures[ZPOS]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[ZPOS]->pixels); 
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, textures[ZNEG]->w, textures[ZNEG]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[ZNEG]->pixels); 
    }

    void Cubemap::relase() const
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
        }
    }
}
