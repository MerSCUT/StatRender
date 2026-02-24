#include"stat_render/materials/Diffuse.h"
#include<random>
Vector3f Diffuse::sample(const Vector3f& wi, const Vector3f& n)
{
    // 均匀采样单位半球
    // 局部坐标系中先采样, 再变换到实际采样点.
    
    Sampler sampler;
    float u1 = sampler.get1D();
    float u2 = sampler.get1D();
    float theta = std::acos(u1);
    float phi = 2 * Pi * u2;
    Vector3f local  = SphTo3D(theta,phi);
    return local;
}

float Diffuse::pdf(const Vector3f & wi, const Vector3f & wo, const Vector3f& n)
{
    // 给定 wo, n, 采样到 wi 的概率.
    return 0.5f * inv_Pi;
}
    
Color3f Diffuse::eval(const Vector3f & wi, const Vector3f& wo, const Vector3f & n)
{
    // BRDF 常数.
    // 确保 wo, wi 方向朝外
    if (Dot(n, wi) > 0.0f && Dot(n, wo) > 0.0f)
    {
        return albedo * inv_Pi;
    }
    return Color3f(0.0f, 0.0f, 0.0f);
}