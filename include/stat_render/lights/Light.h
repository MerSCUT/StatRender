#pragma once

#include"stat_render/core/common.h"
#include"stat_render/shapes/Object.h"
struct LightSample
{
    Point3f position;
    Vector3f normal;
    Color3f radiance;
    float pdf;  
};

class Light{
private:
    // 光源需要什么成员?
    // Object->Material 中包括自发光 Texture 的, 则其光源会被拿下.
    // 这里定义光源需要获取的计算数据接口.  
public:
    virtual ~Light() = default;

    // u1, u2 是随机数
    virtual LightSample sampleLight(float u1, float u2) const = 0;
    virtual Object* getObject() const { return nullptr; }
};