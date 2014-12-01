
#include "Application.h"

#include <GL/glew.h>
#include <stdexcept>

namespace od
{
    const char* vertex = "#version 330 core\n"
                         "in vec3 aVertex;\n"
                         "void main()\n"
                         "{\n"
                         "  gl_Position = vec4(aVertex, 1.0);\n"
                         "}\n";

    const char* fragment = "#version 330 core\n"
                           "out vec4 oFragColor;\n"
                           "void main()\n"
                           "{\n"
                           "  oFragColor = vec4(0.7, 0.5, 1.0, 1.0);\n"
                           "}\n";

    Application::Application()
    : running(false), window(nullptr), glcontext(nullptr)
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
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        glcontext = SDL_GL_CreateContext(window);
        if (glcontext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }  
        
        
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error((const char*)glewGetErrorString(err));
        }

        // TEST

        triangle.add_vertex(Vector3(-1.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
        triangle.add_vertex(Vector3( 1.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
        triangle.add_vertex(Vector3( 0.0f,  1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f));
        triangle.add_face(0, 1, 2);

        shader.set_vertex_code(vertex);
        shader.set_fragment_code(fragment);
        shader.compile();
        
    }

    Application::~Application() 
    {
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

        shader.bind();
        triangle.draw(shader);
            
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
