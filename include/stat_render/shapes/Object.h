#pragma once
#include"stat_render/core/Ray.h"
#include"stat_render/core/Hit.h"
#include"stat_render/materials/Material.h"
#include"stat_render/acclerators/Bound.h"
// 物体抽象基类
class Object{
public:
    // API
    Bound bound;
    Material* material;
    // 1. Ojbect x Ray
    virtual Hit intersect(const Ray& ray) = 0;
    // 2. Bounding Box
    //virtual Bound getBound() = 0;
    Object() {}
    
    Object(Material* m) : material(m) {};
    virtual ~Object() = default;
};