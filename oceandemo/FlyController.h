
#ifndef _OD_FYL_CONTROLLER_H_
#define _OD_FYL_CONTROLLER_H_

#include "Entity.h"

namespace od 
{
    class FlyController : public Entity 
    {
    public:
        FlyController(Entity* controlled);

        void update(float t, float dt) override;

        void handle_event(const SDL_Event& e) override;
        
    private:
        Entity* controlled;        

        bool move_forward;
        bool move_back;
        bool move_left;
        bool move_right;
        bool move_up;
        bool move_down;

        float yaw;
        float pitch;
    };
}

#endif
