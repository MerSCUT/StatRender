#pragma once
#include"stat_render/core/common.h"

struct Ray{
    Point3f origin;
    Vector3f direct;


    Ray() : 
    origin(Point3f(0.,0.,0.)), 
    direct(Vector3f(0.,0.,0.)) {}
    
    Ray(Point3f ori, Vector3f dir) : 
    origin(ori), 
    direct(dir) {}
    Point3f operator()(float t) const { return  t * direct + origin ; }
};
