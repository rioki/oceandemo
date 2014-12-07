
#ifndef _OD_SCENE_H_
#define _OD_SCENE_H_

#include <list>
#include <SDL.h>

namespace od
{
    class Entity;
    class Camera;

    class Scene
    {
    public:
        Scene();

        virtual ~Scene();

        void add_enttiy(Entity* entity);

        void remove_entity(Entity* entity);

        virtual void draw(Camera& camera);

        virtual void update(float t, float dt);

        virtual void handle_event(const SDL_Event& e);

    private:
        std::list<Entity*> entities;

        Scene(const Scene&) = delete;
        const Scene& operator = (const Scene&) = delete;
    };
}

#endif
