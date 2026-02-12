#include<iostream>
#include"stat_render/core/Film.h"
#include"stat_render/core/Ray.h"
#include"stat_render/shapes/Sphere.h"
#include"stat_render/core/Camera.h"
#include"stat_render/scenes/Scene.h"
#include"stat_render/shapes/Triangle.h"
void test_outputImage()
{
    Film film(32,32);
    //film.OutputImage();
    return;
}
void test_triangle()
{
    Triangle tri(Point3f(-0.5f, -0.5f, -4.0), Point3f(0.5f, -0.5f, -8.0f), Point3f(0.0f, 0.5f , -4.0f));
    Film film;
    // default set
    Camera camera(film);
    Scene scene;
    Object* obj = &tri;
    scene.AddObject(obj);
    
    
    auto p = camera.getPosition();
    auto fov = camera.getFov();
    auto asp = camera.getAspect();
    float l,r,t,b;
    float dis = 1.0f;

    // Ray generation
    t = dis * std::tan(deg2rad(fov * 0.5f));
    r = t * asp; 
    l = -r;
    b = -t;
    // Integrator
    for(int j = 0; j < film.getHeight(); j++)
    {
        for(int i = 0; i < film.getWidth(); i++)
        {
            // center of pixels
            float u = l + (float)(i+0.5)/(float)(film.getWidth()) * (r-l);
            float v = b + (float)(j+0.5)/(float)(film.getHeight()) * (t-b);
            v = -v;
            // Ray generation
            Ray ray(Point3f(p), Vector3f(u, v, -1));

            if (Hit payload = tri.intersect(ray); payload.intersected){
                film.set(i, j, Color3f(255., 0.,0.));
            }
            else{
                film.set(i,j, Color3f(0., 0., 255.));
            }
        }
    }
    film.Write("../images/test_triangle.ppm");
}
void test_sphere()
{
    Sphere sph( Point3f(0.f, 0.f, -2.f), 0.5f);
    Film film;
    // default set
    Camera camera(film);
    Scene scene;
    Object* obj = &sph;
    scene.AddObject(obj);
    
    
    auto p = camera.getPosition();
    auto fov = camera.getFov();
    auto asp = camera.getAspect();
    float l,r,t,b;
    float dis = 1.0f;

    // Ray generation
    t = dis * std::tan(deg2rad(fov * 0.5f));
    r = t * asp; 
    l = -r;
    b = -t;
    // Integrator
    for(int j = 0; j < film.getHeight(); j++)
    {
        for(int i = 0; i < film.getWidth(); i++)
        {
            // center of pixels
            float u = l + (float)(i+0.5)/(float)(film.getWidth()) * (r-l);
            float v = b + (float)(j+0.5)/(float)(film.getHeight()) * (t-b);
            v = -v;
            // Ray generation
            Ray ray(Point3f(p), Vector3f(u, v, -1));

            if (Hit payload = sph.intersect(ray); payload.intersected){
                film.set(i, j, Color3f(255., 0.,0.));
            }
            else{
                film.set(i,j, Color3f(0., 0., 255.));
            }
        }
    }
    film.Write("../images/test_sphere.ppm");
}

int main()
{
    test_triangle();
    std::cout << "Test_Finished" << std::endl;
    return 0;
}


