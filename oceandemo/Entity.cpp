
#include "Entity.h"

namespace od
{
    Entity::Entity()
    : transform(1) {}

    Entity::~Entity() {}

    void Entity::translate(const Vector3& v)
    {
        ::od::translate(transform, v);
    }
}
