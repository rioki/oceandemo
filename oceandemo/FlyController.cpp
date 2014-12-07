
#include "FlyController.h"

#include <cmath>
#include <SDL.h>

#include <sstream>
#include <windows.h>

namespace od 
{
    FlyController::FlyController(Entity* c) 
    : controlled(c), 
      move_forward(false), move_back(false), move_left(false), move_right(false), 
      move_up(false), move_down(false), yaw(0.0), pitch(0.0)
    {
        transform = controlled->get_transform();
    }

    void FlyController::update(float t, float dt)
    {
        float   speed = 10.0f;
        Vector3 dv(0, 0, 0);

        if (move_forward)
        {
            dv += Vector3(1, 0, 0);
        }
        if (move_back)
        {
            dv += Vector3(-1, 0, 0);
        }
        if (move_left)
        {
            dv += Vector3(0, 1, 0);
        }
        if (move_right)
        {
            dv += Vector3(0, -1, 0);
        }
        if (move_down)
        {
            dv += Vector3(0, 0, 1);
        }
        if (move_up)
        {
            dv += Vector3(0, 0, -1);
        }

        translate(dv);
        
        controlled->set_transform(transform);
    }    

    void FlyController::handle_event(const SDL_Event& e)
    {
        switch (e.type)
        {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_w) 
                {
                    move_forward = true;
                }
                if (e.key.keysym.sym == SDLK_s) 
                {
                    move_back = true;
                }
                if (e.key.keysym.sym == SDLK_a) 
                {
                    move_left = true;
                }
                if (e.key.keysym.sym == SDLK_d) 
                {
                    move_right = true;
                }
                if (e.key.keysym.sym == SDLK_LCTRL) 
                {
                    move_down = true;
                }
                if (e.key.keysym.sym == SDLK_SPACE) 
                {
                    move_up = true;
                }
            break;
            case SDL_KEYUP:
                if (e.key.keysym.sym == SDLK_w) 
                {
                    move_forward = false;
                }
                if (e.key.keysym.sym == SDLK_s) 
                {
                    move_back = false;
                }
                if (e.key.keysym.sym == SDLK_a) 
                {
                    move_left = false;
                }
                if (e.key.keysym.sym == SDLK_d) 
                {
                    move_right = false;
                }
                if (e.key.keysym.sym == SDLK_LCTRL) 
                {
                    move_down = false;
                }
                if (e.key.keysym.sym == SDLK_SPACE) 
                {
                    move_up = false;
                }
            break;
            case SDL_MOUSEMOTION:
            {
                // Only apply when lower than 5. It can happen that when the window is created or maximized
                // that the window recive HUGE mouse movements. These should be discarded.
                if (e.motion.xrel < 5 || e.motion.yrel < 5) 
                {
                    pitch -= static_cast<float>(e.motion.xrel);
                    yaw   -= static_cast<float>(e.motion.yrel);

                    Vector3 p(transform(3, 0), transform(3, 1), transform(3, 2));

                    Matrix44 m(1);
                    m = ::od::rotate(m, Vector3(0, 0, 1), pitch);
                    m = ::od::rotate(m, Vector3(0, 1, 0), yaw);

                    m(3,0) = p(0);
                    m(3,1) = p(1);
                    m(3,2) = p(2);

                    transform = m;
                }               
            }
            break;
        }
    }
}
