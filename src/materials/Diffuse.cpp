#include"stat_render/materials/Diffuse.h"
#include<random>

Diffuse::Diffuse(DiffuseColor dc)
{
    switch (dc)
    {
    case DiffuseColor::BLUE :
    {
        albedo = Color3f(0.14, 0.14, 0.45);
        break;
    }
    case DiffuseColor::GREEN :
    {
        albedo = Color3f(0.14, 0.45, 0.091);
        break;
    }
    case DiffuseColor::WHITE :
    {
        albedo = Color3f(0.725, 0.71, 0.68);
        break;
    }
    case DiffuseColor::RED :
    {
        albedo = Color3f(0.63, 0.065, 0.05);
        break;
    }
    }
}

Vec3f Diffuse::sample(const Vec3f& wi, const Vec3f& n)
{
    // 均匀采样单位半球
    // 局部坐标系中先采样, 再变换到实际采样点.
    
    Sampler sampler;
    float u1 = sampler.get1D();
    float u2 = sampler.get1D();
    float theta = std::acos(u1);
    float phi = 2.0f * Pi * u2;


    float sin_theta = std::sin(theta);
    float x = sin_theta * std::cos(phi);
    float y = sin_theta * std::sin(phi);
    float z = std::cos(theta); // 即 u1

    Vec3f t;
    if (std::abs(n.x) > std::abs(n.y)) {
        float invLen = 1.0f / std::sqrt(n.x * n.x + n.z * n.z);
        t = Vec3f(n.z * invLen, 0.0f, -n.x * invLen);
    } else {
        float invLen = 1.0f / std::sqrt(n.y * n.y + n.z * n.z);
        t = Vec3f(0.0f, n.z * invLen, -n.y * invLen);
    }
    // 通过叉乘得到副切向量 b
    Vec3f b = cross(n, t);

    return x * t + y * b + z * n;
}

float Diffuse::pdf(const Vec3f & wi, const Vec3f & wo, const Vec3f& n)
{
    // 给定 wo, n, 采样到 wi 的概率.
    return 0.5f * inv_Pi;
}
    
Color3f Diffuse::eval(const Vec3f & wi, const Vec3f& wo, const Vec3f & n)
{
    // BRDF 常数.
    // 确保 wo, wi 方向朝外
    if (dot(n, wi) > 0.0f && dot(n, wo) > 0.0f)
    {
        return albedo * inv_Pi;
    }
    return Color3f(0.0f, 0.0f, 0.0f);
}