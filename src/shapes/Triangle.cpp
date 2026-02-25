#include"stat_render/shapes/Triangle.h"
#include"stat_render/samplers/sampler.h"

Hit Triangle::intersect(const Ray& ray)
{
    Hit payload;
    payload.intersected = false; // 确保默认状态为未击中

    Vec3f e1 = v1 - v0;
    Vec3f e2 = v2 - v0;

    // 计算射线方向与 e2 的叉积
    Vec3f pvec = cross(ray.direct, e2);
    
    // 计算行列式 det
    float det = dot(e1, pvec);

    // det 接近 0，说明射线与三角形所在平面平行
    // 使用 std::fabs 允许背面相交 (不剔除背面)
    if (std::fabs(det) < 1e-12) {
        return payload;
    }

    float invDet = 1.0f / det;
    Vec3f tvec = ray.origin - v0;

    // 计算重心坐标 u，并进行边界检查
    
    float u = dot(tvec, pvec) * invDet;
    if (u < -Epsilon || u > 1.0f + Epsilon) {
        return payload;
    }

    // 计算 qvec 并求出重心坐标 v
    Vec3f qvec = cross(tvec, e1);
    float v = dot(ray.direct, qvec) * invDet;
    if (v < -Epsilon || u + v > 1.0f + Epsilon) {
        return payload;
    }

    // 计算射线参数 t
    float t = dot(e2, qvec) * invDet;
    
    // 剔除位于射线起点的背后或极近处的交点 (避免自相交噪点)
    if (t < 0.0) {
        return payload;
    }

    // --- 求交成功，组装 Hit ---
    payload.intersected = true;
    payload.tmin = t;
    payload.position = ray(t);
    payload.incident = -ray.direct;
    payload.material = material;
    payload.obj = this;
    // 计算几何法线
    Vec3f normal = cross(e1, e2).normalized();
    
    // 关键细节：如果光线从三角形背面击中，需要翻转法线
    // 这对于后续正确的物理着色（如玻璃折射、微表面反射）至关重要
    if (det < 0.0f) {
        normal = -normal;
    }
    payload.normal = normal;

    return payload;
}

bool Triangle::hit(const Ray& ray)
{
    return true;
}

void Triangle::sample(float xi1, float xi2, Point3f& position, Vec3f& normal, float& pdf) const
{

    float sqrt_xi1 = std::sqrt(xi1);
    float b0 = 1.0f - sqrt_xi1;
    float b1 = xi2 * sqrt_xi1;
    float b2 = 1.0f - b0 - b1;
    position = b0 * v0 + b1 * v1 + b2 * v2;

    // 无平滑法线, 直接返回面法线:
    normal = cross(v1 - v0, v2 - v0).normalized();
    pdf = 1.0f / SurfaceArea();
    return;
}

void Triangle::transform(const Mat4f& M)
{
    auto v0h = toPoint4D(v0);
    auto v1h = toPoint4D(v1);
    auto v2h = toPoint4D(v2);
    v0 = (M * v0h).xyz();
    v1 = (M * v1h).xyz();
    v2 = (M * v2h).xyz();
    Vec3f pmin = v0.cwiseMin(v1).cwiseMin(v2);
    Vec3f pmax = v0.cwiseMax(v1).cwiseMax(v2);
    bound = Bound(pmin, pmax); 
}