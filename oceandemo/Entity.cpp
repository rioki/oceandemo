
#include "Entity.h"

namespace od
{
    Entity::Entity()
    : transform(1) {}

    Entity::~Entity() {}

    rgm::mat4 Entity::get_transform() const
    {
        return transform;
    }

    void Entity::set_transform(rgm::mat4 value)
    {
        transform = value;
    }

    void Entity::translate(const rgm::vec3& v)
    {
        transform = rgm::translate(transform, v);
    }

    void Entity::rotate(const rgm::vec3& axis, float angle)
    {
        transform = rgm::rotate(transform, axis, angle);
    }

    void Entity::draw(Camera& camera) const {}

    void Entity::update(float t, float dt) {}

    void Entity::handle_event(const SDL_Event& e) {}
}
