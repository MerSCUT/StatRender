#include"stat_render/renderers/Renderer.h"
#include"stat_render/core/transform.h"
#include<iostream>
void Renderer::RenderPipeline(const Scene& scene, Film& film)
{
    int progress = 0;
    for(int j = 0; j < film.getHeight(); j++)
    {
        for(int i = 0; i < film.getWidth(); i++)
        {
            
            float u = l + (float)(i+0.5f)/(float)(film.getWidth()) * (r-l);
            float v = -b - (float)(j+0.5f)/(float)(film.getHeight()) * (t-b);
            // Ray generation
            Vector3f dir = Vector3f(u, v, -1);
            auto M = CameraToWorldTransform(camera.getPosition(), camera.getGaze(), camera.getTop());
            
            Vector4f ret = M * VectorTo4D(dir);
            dir = Vector3f(ret.x(), ret.y(), ret.z()).normalized();
            Ray ray(Point3f(camera.getPosition()), dir);

            auto res = CastRay(ray, scene);
            film.set(i,j, res);
            progress++;
            std::cout << "\r进度: " << progress << " / " << film.getHeight() * film.getWidth() << std::flush;
        }
    }
    std::cout << std::endl;
}

Color3f Renderer::CastRay(const Ray& ray, const Scene& scene)
{
    if (Hit payload = scene.intersect(ray);  
    payload.intersected)
    {
        switch (mode)
        {
        case Mode::PathTracing :
        {
            // 光源
            Object* ob = payload.obj;
            ob->getBound();
            Material* w = payload.obj->getMaterial();
            if (payload.obj->getMaterial()->isEmissive())
            {
                return payload.obj->getMaterial()->getEmission();
            }
            
            // 非光源
            // 1. 直接光照
            Color3f L_dir(0.0f, 0.0f, 0.0f);
            LightSample ls = scene.sampleLight();
            auto p = payload.position;
            auto l = ls.position;
            Vector3f wi = (l - p ).normalized();    // outwards
            // 相交测试
            Ray test(p, wi);
            auto hit_test = scene.intersect(test);
            // if ((test(hit_test.tmin) - payload.position).norm() > (ls.position - payload.position).norm())
            if (Dot(test(hit_test.tmin) - l, wi) >= 0) 
            {
                // light-obj 与 wi 同向, 未被阻挡
                Vector3f wo = payload.incident.normalized();
                auto n_p = payload.normal;
                auto n_l = ls.normal;

                // 根据 payload.material 计算 L_o
                // L_o = fr * L_i * Dot(n, wi) * Dot(-n_l, wi) / Dot(p-l, p-l) / ls.pdf_A
                auto fr = payload.material->eval(wi, wo, n_p);
                auto Li = ls.radiance;
                auto cos_thetai = Dot(n_p, wi);
                auto cos_thetaip = Dot(n_l, wi);
                

                assert(cos_thetaip >= 0.f);
                auto dis = Dot(p-l, p-l);
                
                L_dir = fr * Li * cos_thetai * cos_thetaip / (dis * ls.pdf) ;
            }

            Color3f L_indir(0.f, 0.f, 0.f);
            // Russian Roulette

            // 采样入射方向 wi

            // 采样入射方向.
            
            return L_dir + L_indir;
            
            
            break;
        }
            
        // normal
        case (Mode::NormalMap) :
        {
            auto n = payload.normal;
            // [-1,1] -> [0,1]
            
            float R = n.x() * 0.5f + 0.5f;
            float G = n.y() * 0.5f + 0.5f;
            float B = n.z() * 0.5f + 0.5f;
            
            return Color3f(255. * R, 255. * G,255. * B);

            break;
        }
            
            
        }
        return Color3f(255.0f, 0.f, 0.f);
    }
    //return Color3f(0.f, 0.f, 0.f);
    return Color3f(199.f,233.f,233.f);
}