
#include "Application.h"

#include <GL/glew.h>
#include <stdexcept>
#include <ctime>

#include "FlyController.h"
#include "Ocean.h"
#include "SkyBox.h"

namespace od
{
    Application::Application()
    : running(false), window(nullptr), glcontext(nullptr),
      scene(nullptr), camera(nullptr)
    {
        int r = SDL_Init(SDL_INIT_VIDEO);
        if (r != 0) 
        {
            throw std::runtime_error(SDL_GetError());
        }
            
        window = SDL_CreateWindow("Ocean Demmo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_OPENGL);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
        
        // TODO set to 3.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        glcontext = SDL_GL_CreateContext(window);
        if (glcontext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }  
        
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error((const char*)glewGetErrorString(err));
        }        

        SDL_ShowCursor(0);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        // everything that uses OpenGL need to be initialized after glew, thus pointers.

        scene = new Scene;
        camera = new Camera;
        // CHECK ME
        camera->translate(rgm::vec3(0, 0, -3));
        scene->add_enttiy(camera);

        FlyController* ctrl = new FlyController(camera);
        scene->add_enttiy(ctrl);

        scene->add_enttiy(new SkyBox);
        scene->add_enttiy(new Ocean);        
    }

    Application::~Application() 
    {
        delete scene;

        if (glcontext != nullptr)
        {
            SDL_GL_DeleteContext(glcontext);
            glcontext = nullptr;
        }
        
        if (window != nullptr)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        SDL_Quit();
    }

    void Application::run() 
    {
        std::clock_t last_tick = std::clock();
        running = true;
        while (running)
        {   
            std::clock_t now = std::clock();
            float t  = static_cast<float>(now) / static_cast<float>(CLOCKS_PER_SEC);
            float dt = static_cast<float>(now - last_tick) / static_cast<float>(CLOCKS_PER_SEC);
            last_tick = now;

            handle_events();
            scene->update(t, dt);
            draw();
        }
    }
    
    void Application::draw()
    {
        glViewport(0, 0, 1600, 900);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->draw(*camera);
            
        SDL_GL_SwapWindow(window); 
    }

    void Application::handle_events()
    {        
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
             switch (event.type)
             {
                case SDL_QUIT:
                    running = false;
                    break; 

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) 
                    {
                        running = false;
                    }
                // fallthough
                case SDL_KEYUP:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                    // TODO Abstract SDL_Event out
                    scene->handle_event(event);
                    break;
             }
        }
    }
}

int main(int argc, char* argv[])
{
    try
    {
        od::Application app;
        app.run();
        return 0;
    }
    catch (const std::exception& ex)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ex.what(), nullptr);
        return -1;
    }
}
