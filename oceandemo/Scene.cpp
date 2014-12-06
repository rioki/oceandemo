
#include "Scene.h"
#include "Entity.h"

#include <algorithm>

namespace od
{
    Scene::Scene() {}
    
    Scene::~Scene()
    {
        for (Entity* entity : entities)
        {
            delete entity;
        }
    }

    void Scene::add_enttiy(Entity* entity)
    {
        entities.push_back(entity);
    }

    void Scene::remove_entity(Entity* entity)
    {
        auto i = std::find(entities.begin(), entities.end(), entity);
        if (i != entities.end())
        {
            entities.erase(i);
        }
        else
        {
            throw std::logic_error("Enttiy not in scene.");
        }
    }

    void Scene::draw(Camera& camera) 
    {
        for (Entity* entity : entities)
        {
            entity->draw(camera);
        }
    }    
}
