#pragma once
#include"stat_render/core/common.h"

// 

using Vector4f = Eigen::Vector4f;
using Point4f = Eigen::Vector4f;
inline Vector4f VectorTo4D(Vector3f coor)
{
    return Vector4f(coor.x(), coor.y(), coor.z(), 0.0f); 
}
inline Point4f PointTo4D(Point3f coor)
{
    return Point4f(coor.x(), coor.y(), coor.z(), 1.0f);
}
inline Vector3f Vector4DTo3D(Vector4f homo)
{
    return Vector3f(homo.x(), homo.y(), homo.z());
}
inline Point3f Point4DTo3D(Point4f homo)
{
    return Point3f(homo.x(), homo.y(), homo.z());
}


inline Eigen::Matrix4f ViewTransform(const Point3f p, Vector3f g, Vector3f t )
{
    g.normalize();
    t.normalize();
    
    
    Eigen::Matrix4f translation;
    translation << 1., 0., 0., -p.x(),
                   0., 1., 0., -p.y(),
                   0., 0., 1., -p.z(),
                   0., 0., 0., 1.;
                   
    auto gCrosst = Cross(g, t); 
    gCrosst.normalize();

    
    Eigen::Matrix4f rotation;
    rotation << gCrosst.x(), gCrosst.y(), gCrosst.z(), 0.,
                t.x(),       t.y(),       t.z(),       0.,
               -g.x(),      -g.y(),      -g.z(),       0.,
                0.,          0.,          0.,          1.;
                
    Eigen::Matrix4f View;
    View = rotation * translation;
    return View;
}

inline Eigen::Matrix4f CameraToWorldTransform(const Point3f p, Vector3f g, Vector3f t)
{
    g.normalize();
    t.normalize();
    
    auto u = Cross(g, t); 
    u.normalize();

    // 4. 直接构造 Camera-to-World 矩阵
    
    Eigen::Matrix4f camToWorld;
    camToWorld << u.x(), t.x(), -g.x(), p.x(),
                  u.y(), t.y(), -g.y(), p.y(),
                  u.z(), t.z(), -g.z(), p.z(),
                  0.f,   0.f,   0.f,    1.f;
                  
    return camToWorld;
}

inline Eigen::Matrix4f PerspectiveTransform()
{
    return Eigen::Matrix4f();
}
