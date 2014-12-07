
#ifndef _OD_CUBEMAP_H_
#define _OD_CUBEMAP_H_

#include <SDL.h>
#include <string>

namespace od
{
    enum CubeMapOrientation
    {
        XPOS = 0, 
        XNEG = 1, 
        YPOS = 2, 
        YNEG = 3, 
        ZPOS = 4, 
        ZNEG = 5
    };

    class Cubemap
    {
    public:
        Cubemap();

        ~Cubemap();

        void load(CubeMapOrientation o, const std::string& file);

        void bind(unsigned int channel) const;

        void unbind(unsigned int channel) const;

        void upload() const;

        void relase() const;

    private:
        SDL_Surface* textures[6];
        mutable unsigned int glid;
    };

}

#endif
