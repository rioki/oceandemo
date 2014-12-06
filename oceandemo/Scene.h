
#ifndef _OD_SCENE_H_
#define _OD_SCENE_H_

#include <list>

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

        void draw(Camera& camera);

    private:
        std::list<Entity*> entities;

        Scene(const Scene&) = delete;
        const Scene& operator = (const Scene&) = delete;
    };
}

#endif
