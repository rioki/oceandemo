
#ifndef _OD_ENTITY_H_
#define _OD_ENTITY_H_

#include <SDL.h>

#include "Matrix44.h"

namespace od
{
    class Camera;
    
    class Entity
    {
    public:

        Entity();

        virtual ~Entity();

        Matrix44 get_transform() const;

        void set_transform(Matrix44 value);

        void translate(const Vector3& v);

        void rotate(const Vector3& axis, float angle);

        virtual void draw(Camera& camera) const;

        virtual void update(float t, float dt);

        virtual void handle_event(const SDL_Event& e);

    protected:
        Matrix44 transform;

    private:
    

        Entity(const Entity&) = delete;
        const Entity& operator = (const Entity&) = delete;
    };
}

#endif