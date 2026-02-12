#pragma once
#include<vector>
#include"stat_render/shapes/Object.h"
class Scene
{
private:
    
    std::vector<Object*> objects;
    //std::vector<Light*> lights;
public:
    Scene() {}
    
    ~Scene() = default;
    void AddObject(Object* object) { objects.push_back(object); }
    
};