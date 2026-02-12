#include"stat_render/shapes/Triangle.h"

Hit Triangle::intersect(const Ray& ray)
{
    Hit payload;
    Vector3f normal = Cross(v1-v0, v2-v0);
    
    float t = Dot(v0 - ray.origin , normal)/Dot(ray.direct, normal);
    if (t < -Epsilon) return payload;

    Vector3f t1 = Cross(ray(t)-v0, v1-v0);
    Vector3f t2 = Cross(ray(t)-v1, v2-v1);
    Vector3f t3 = Cross(ray(t)-v2, v0-v2);
    bool con1 = Dot(t1, normal) >= -Epsilon &&  Dot(t2,normal) >= -Epsilon && Dot(t3, normal) >= -Epsilon;
    bool con2 = Dot(t1, normal) <= Epsilon &&  Dot(t2,normal) <= Epsilon && Dot(t3, normal) <= Epsilon;
    if (!con1 && !con2) return payload;

    payload.intersected = true;
    payload.position = ray(t);
    payload.material = material;
    //payload.normal = n_interp; 法向量插值
    payload.tmin = t;
    return payload;
}

bool Triangle::hit(const Ray& ray)
{
    return true;
}