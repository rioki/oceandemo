
#include "Entity.h"

namespace od
{
    Entity::Entity()
    : transform(1) {}

    Entity::~Entity() {}

    Matrix44 Entity::get_transform() const
    {
        return transform;
    }

    void Entity::set_transform(Matrix44 value)
    {
        transform = value;
    }

    void Entity::translate(const Vector3& v)
    {
        transform = ::od::translate(transform, v);
    }

    void Entity::rotate(const Vector3& axis, float angle)
    {
        transform = ::od::rotate(transform, axis, angle);
    }

    void Entity::draw(Camera& camera) const {}

    void Entity::update(float t, float dt) {}

    void Entity::handle_event(const SDL_Event& e) {}
}
