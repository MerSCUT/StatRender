#pragma once
#include"stat_render/core/common.h"
#include"stat_render/materials/Material.h"

enum class DiffuseColor { BLUE, GREEN, RED, WHITE };


class Diffuse : public Material{
private:
    Color3f albedo = Color3f(0.f, 0.f, 0.f);     // 漫反射系数
public:
    Diffuse() = default;
    Diffuse(Color3f k) : albedo(k) {}
    Diffuse(DiffuseColor dc);
    

    Vec3f sample(const Vec3f& wi, const Vec3f& n) override;
    
    float pdf(const Vec3f & wi, const Vec3f & wo, const Vec3f& n) override;
    
    Color3f eval(const Vec3f & wi, const Vec3f& wo, const Vec3f & n) override;
};