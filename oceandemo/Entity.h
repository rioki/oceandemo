
#ifndef _OD_ENTITY_H_
#define _OD_ENTITY_H_

#include "Matrix44.h"

namespace od
{
    class Entity
    {
    public:

        Entity();

        virtual ~Entity();

        void translate(const Vector3& v);

    protected:
        Matrix44 transform;

    private:
    

        Entity(const Entity&) = delete;
        const Entity& operator = (const Entity&) = delete;
    };
}

#endif