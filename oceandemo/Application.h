
#ifndef _OD_APPLICATION_H_
#define _OD_APPLICATION_H_

#include <SDL.h>

#include "Mesh.h"
#include "Shader.h"

#include "Camera.h"
#include "Scene.h"

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

        Scene* scene;
        Camera* camera;

        void draw();
        void handle_events();

        void handle_key_press(SDL_Keysym key);
        void handle_key_release(SDL_Keysym key);

        Application(const Application&) = delete;
        const Application& operator = (const Application&) = delete;
    };
}

#endif
