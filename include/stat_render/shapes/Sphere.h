#pragma once

#include"stat_render/shapes/Object.h"

class Sphere :public Object{
private:
    Point3f center;
    float radius;
    
public:
    Sphere() : radius(0.0f), center(Point3f(0.f,0.f,0.f)) {}
    Sphere(Point3f cen, float r) : radius(r), center(cen) {}
    ~Sphere() = default;

    float getSurfaceArea();
    bool hit(const Ray & ray);     
    Hit intersect(const Ray& ray) override;
};