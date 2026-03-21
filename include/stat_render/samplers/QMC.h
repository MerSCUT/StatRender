#pragma once

#include"stat_render/core/common.h"
#include<random>
class QMC
{
private:
    uint64_t sampleIndex = 0;   // 当前是第几个采样 (SPP)
    uint32_t currentDim = 0;    // 当前处于积分域的第几个维度
    uint32_t scrambleSeed = 0;  // Hash seed : each (x,y,k)
public:

    QMC() = default;
    ~QMC() = default;

    uint32_t Hash(int x, int y);
    // 新的像素
    virtual void startPixel(const Vec2f& v) {
        sampleIndex = 0;
        currentDim = 0;
        scrambleSeed = Hash(v.x, v.y);
    }
    // 新的样本 SPP
    virtual void NextSample()
    {
        currentDim = 0;
        sampleIndex++;
    }
    virtual float get1D() = 0;
    virtual Vec2f get2D() { return Vec2f(get1D(), get1D()); };

};
class SobolSampler : public QMC
{
private:

public:
    SobolSampler() = default;
    ~SobolSampler() = default;

    float get1D() override{

    };
};