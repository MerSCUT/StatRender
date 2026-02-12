#include"stat_render/core/Film.h"
#include<fstream>
#include<iostream>

// 自定义输出路径
void Film::Write(std::string path)
{
    std::ofstream f(path, std::ios::out);
    if (!f) {std::cout << "Fail to open file !" << std::endl; return; }

    f << "P3\n" << width << ' ' << height << "\n255\n"; 
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            auto c = frame_buffer[j*width + i];
            f << c[0] << ' ' << c[1] << ' ' << c[2] << '\n';
        }
    }
    f.close();
    return;
} 