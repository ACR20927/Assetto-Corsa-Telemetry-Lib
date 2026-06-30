# Assetto-Corsa-Telemetry-Lib
基于读取共享内存实时获取Assetto Corsa遥测数据的c++库,只是简单封装了一下
# 样例
```cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <windows.h>

#include "actelemetry.h"

int main()
{
    //创建一个ACTelemetry类用于保存遥测数据
    ACTelemetry telemetry;
    
    while (true) 
    {
        //ReadData 函数每次调用会读取一次共享内存中的遥测数据并写入到ACTelemetry类中
        telemetry.ReadData();

        //用telemetry.GetXXX()函数获取你想要的值
        std::cout << "  Throttle:  " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetThrottle() * 100 << " %" << std::endl;
        std::cout << "  Brake:     " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetBrake() * 100 << " %" << std::endl;
        std::cout << "  Steering:  " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetSteering() << " rad" << std::endl;
        std::cout << "  Clutch:    " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetClutch() * 100 << " %" << std::endl;

        Sleep(200);
    }

}
```
# 你需要知道的
我没研究完共享内存块中的数据分别对应什么，所有目前除了油门刹车方向盘啥的别的基本都是错的。。
