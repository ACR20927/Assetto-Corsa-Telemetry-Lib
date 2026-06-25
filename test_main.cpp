#include "actelemetry.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <windows.h>

void PrintTelemetryData(const ACTelemetry& telemetry) 
{
    system("cls");
    
    std::cout << "  Throttle:  " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetThrottle() * 100 << " %" << std::endl;
    std::cout << "  Brake:     " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetBrake() * 100 << " %" << std::endl;
    std::cout << "  Steering:  " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetSteering() << " rad" << std::endl;
    std::cout << "  Clutch:    " << std::setw(6) << std::fixed << std::setprecision(2) 
              << telemetry.GetClutch() * 100 << " %" << std::endl;
}

int main() {
    ACTelemetry telemetry;
    
    while (true) 
    {
        telemetry.ReadData();
        PrintTelemetryData(telemetry);
        Sleep(200);
    }
    
    return 0;
}