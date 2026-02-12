#pragma once

#include"stat_render/core/common.h"
#include<limits>
class Bound{
private:
    Point3f Pmin, Pmax;
public:
    Bound() : 
    Pmin(std::numeric_limits<float>::min(),std::numeric_limits<float>::min(),std::numeric_limits<float>::min() ), 
    Pmax(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()) {}
    ~Bound() = default;
    // 包围盒合并函数
    Bound Union(const Bound& b1,const Bound& b2);
};