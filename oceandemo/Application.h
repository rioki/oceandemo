
#ifndef _OD_APPLICATION_H_
#define _OD_APPLICATION_H_

#include <SDL.h>

#include "Mesh.h"
#include "Shader.h"

namespace od
{
    class Application
    {
    public:

        Application();

        ~Application();

        void run();

    private:
        bool          running;
        SDL_Window*   window;
        SDL_GLContext glcontext;

        void draw();
        void handle_events();

        Mesh   triangle;
        Shader shader;

        Application(const Application&) = delete;
        const Application& operator = (const Application&) = delete;
    };
}

#endif
