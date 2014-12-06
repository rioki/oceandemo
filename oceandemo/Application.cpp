
#include "Application.h"

#include <GL/glew.h>
#include <stdexcept>

#include "Ocean.h"

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

        // everything that uses OpenGL need to be initialized after glew, thus pointers.

        scene = new Scene;
        camera = new Camera;
        // CHECK ME
        camera->translate(Vector3(0, 0, -3));
        scene->add_enttiy(camera);

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
        running = true;
        while (running)
        {
            handle_events();
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
                    handle_key_press(event.key.keysym);
                    break;
                case SDL_KEYUP:
                    handle_key_release(event.key.keysym);
                    break;
             }
        }
    }

    void Application::handle_key_press(SDL_Keysym key)
    {
        
    }

    void Application::handle_key_release(SDL_Keysym key)
    {
    
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
