
#ifndef _OD_ENTITY_H_
#define _OD_ENTITY_H_

#include <SDL.h>

#include <rgm/rgm.h>

namespace od
{
    class Camera;
    
    class Entity
    {
    public:

        Entity();

        virtual ~Entity();

        rgm::mat4 get_transform() const;

        void set_transform(rgm::mat4 value);

        void translate(const rgm::vec3& v);

        void rotate(const rgm::vec3& axis, float angle);

        virtual void draw(Camera& camera) const;

        virtual void update(float t, float dt);

        virtual void handle_event(const SDL_Event& e);

    protected:
        rgm::mat4 transform;

    private:
    

        Entity(const Entity&) = delete;
        const Entity& operator = (const Entity&) = delete;
    };
}

#endif