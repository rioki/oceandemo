
#ifndef _OD_APPLICATION_H_
#define _OD_APPLICATION_H_

#include <SDL.h>

#include "Mesh.h"
#include "Shader.h"

#include "Camera.h"
#include "Ocean.h"

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

        Camera* camera;
        Ocean*  ocean;

        Application(const Application&) = delete;
        const Application& operator = (const Application&) = delete;
    };
}

#endif
