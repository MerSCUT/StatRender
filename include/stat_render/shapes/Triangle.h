#pragma once

#include"stat_render/shapes/Object.h"
class Triangle : public Object
{
private:
    Point3f v0, v1, v2;
    Vector3f n0, n1, n2;   //vertices normal
    Point2f uv;

public:
    // All zero by default
    Triangle() :
    v0(Point3f(0.,0.,0.)),
    v1(v0),
    v2(v0),
    uv(Point2f(0.,0.)) {}

    Triangle(Point3f v0_, Point3f v1_, Point3f v2_) : 
    v0(v0_), v1(v1_), v2(v2_), 
    uv(Point2f(0.f,0.f)) {}

    ~Triangle() = default;

    inline void SetVertex(const Point3f& _v0, const Point3f& _v1, const Point3f& _v2)
    {
        v0 = _v0 ; v1  = _v1; v2 = _v2;
    }
    Hit intersect(const Ray& ray) override;
    bool hit(const Ray& ray);
};