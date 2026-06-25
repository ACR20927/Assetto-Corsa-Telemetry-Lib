#define ACTELEMETRY_EXPORTS
#include "actelemetry.h"
#include <windows.h>
#include <tlhelp32.h>
#include <string>

ACTelemetry::ACTelemetry(): hPhysicsMapping(nullptr), hGraphicMapping(nullptr),
      physicsData(nullptr), graphicData(nullptr), connected(false) {}

ACTelemetry::~ACTelemetry(){}

bool ACTelemetry::ReadData() 
{
    hPhysicsMapping = OpenFileMappingW(FILE_MAP_READ, FALSE, L"Local\\acpmf_physics");
    if(!hPhysicsMapping)return false;
    hGraphicMapping = OpenFileMappingW(FILE_MAP_READ, FALSE, L"Local\\acpmf_graphics");
    if(!hGraphicMapping)return false;

    physicsData = reinterpret_cast<SPageFilePhysics*>(
        MapViewOfFile(hPhysicsMapping, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics))
    ); 
    graphicData = reinterpret_cast<SPageFileGraphic*>(
        MapViewOfFile(hGraphicMapping, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic))
    );

    if (physicsData&&graphicData)return true;
    return false;
}

float ACTelemetry::GetThrottle() const {
    return physicsData ? physicsData->gas : 0.0f;
}

float ACTelemetry::GetBrake() const {
    return physicsData ? physicsData->brake : 0.0f;
}

float ACTelemetry::GetSpeedKmh() const {
    return physicsData ? physicsData->speedKmh : 0.0f;
}

float ACTelemetry::GetSpeedMs() const {
    return physicsData ? physicsData->speedKmh / 3.6f : 0.0f;
}

int32_t ACTelemetry::GetGear() const {
    return physicsData ? static_cast<int32_t>(physicsData->gear) : 0;
}

float ACTelemetry::GetEngineRPM() const {
    return physicsData ? physicsData->rpm : 0.0f;
}

float ACTelemetry::GetFuel() const {
    return physicsData ? physicsData->fuel : 0.0f;
}

float ACTelemetry::GetSteering() const {
    return physicsData ? physicsData->steerAngle : 0.0f;
}

float ACTelemetry::GetClutch() const {
    return physicsData ? physicsData->clutch : 0.0f;
}

float ACTelemetry::GetLapTime() const {
    return physicsData ? physicsData->lapTime : 0.0f;
}

float ACTelemetry::GetLastLapTime() const {
    return physicsData ? physicsData->lastLapTime : 0.0f;
}

float ACTelemetry::GetBestLapTime() const {
    return physicsData ? physicsData->bestLapTime : 0.0f;
}

float ACTelemetry::GetLapDistance() const {
    return physicsData ? physicsData->lapDistance : 0.0f;
}

float ACTelemetry::GetTotalDistance() const {
    return physicsData ? physicsData->totalDistance : 0.0f;
}

float ACTelemetry::GetEngineTemperature() const {
    return physicsData ? physicsData->oilTemp : 0.0f;
}

float ACTelemetry::GetTyreWear(int wheelIndex) const {
    if (!physicsData || wheelIndex < 0 || wheelIndex >= 4) return 0.0f;
    return physicsData->tyreLife[wheelIndex];
}

float ACTelemetry::GetTyreTemperature(int wheelIndex) const {
    if (!physicsData || wheelIndex < 0 || wheelIndex >= 4) return 0.0f;
    return physicsData->tiresTemp[wheelIndex];
}

float ACTelemetry::GetBrakeTemperature(int wheelIndex) const {
    if (!physicsData || wheelIndex < 0 || wheelIndex >= 4) return 0.0f;
    return physicsData->brakeTemp[wheelIndex];
}

float ACTelemetry::GetWheelSlip(int wheelIndex) const {
    if (!physicsData || wheelIndex < 0 || wheelIndex >= 4) return 0.0f;
    return physicsData->tireSlip[wheelIndex];
}

float ACTelemetry::GetAcceleration(int axis) const {
    if (!physicsData || axis < 0 || axis >= 3) return 0.0f;
    if (axis == 0) return physicsData->accX;
    if (axis == 1) return physicsData->accY;
    return physicsData->accZ;
}

float ACTelemetry::GetVelocity(int axis) const {
    if (!physicsData || axis < 0 || axis >= 3) return 0.0f;
    if (axis == 0) return physicsData->velocityX;
    if (axis == 1) return physicsData->velocityY;
    return physicsData->velocityZ;
}

int32_t ACTelemetry::GetSessionStatus() const {
    return graphicData ? graphicData->status : 0;
}

int32_t ACTelemetry::GetSessionType() const {
    return graphicData ? graphicData->session : 0;
}

int32_t ACTelemetry::GetLapCount() const {
    return graphicData ? graphicData->completedLaps : 0;
}

int32_t ACTelemetry::GetPosition() const {
    return graphicData ? graphicData->position : 0;
}

std::string ACTelemetry::GetTyreCompound() const {
    if (!graphicData) return "";
    return std::string(graphicData->tyreCompound);
}

const SPageFilePhysics* ACTelemetry::GetPhysicsData() const {
    return physicsData;
}

const SPageFileGraphic* ACTelemetry::GetGraphicData() const {
    return graphicData;
}