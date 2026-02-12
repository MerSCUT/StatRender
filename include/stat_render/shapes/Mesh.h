#pragma once

#include"stat_render/shapes/Triangle.h"
#include<vector>
#include<memory>
class Mesh : public Object{
private:
    std::vector<std::shared_ptr<Triangle>> list;
public:
    Mesh(std::vector<Triangle> triangles);
    ~Mesh();
};