#pragma once
#include<stat_render/core/common.h>
#include"stat_render/materials/Material.h"
// Intersection pakcages between Ray and Object / Bounding Box
struct Hit
{
    bool intersected;
    Point3f position;
    Vector3f normal;
    Material* material;
    float tmin;
    // time (Ray x Bounding Box)

    Hit() : intersected(false), position(Point3f(0.,0.,0.)), normal(Vector3f(0.,0.,0.)), material(nullptr), tmin(0.f) {}
};
