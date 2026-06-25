#pragma once

#pragma pack(push, 4)

#ifdef ACTELEMETRY_EXPORTS
#   define ACTELEMETRY_API __declspec(dllexport)
#else
#   define ACTELEMETRY_API __declspec(dllimport)
#endif

#include <cstdint>
#include <string>

struct SPageFilePhysics {
    float packetId;
    float gas;
    float brake;
    float fuel;
    float gear;
    float rpm;
    float steerAngle;
    float speedKmh;
    float velocityX;
    float velocityY;
    float velocityZ;
    float accX;
    float accY;
    float accZ;
    float lapTime;
    float lastLapTime;
    float bestLapTime;
    float lapDistance;
    float totalDistance;
    float trackPosition;
    float error;
    float courseVariation;
    float tiresPressure[4];
    float tiresTemp[4];
    float wheelsAngularSpeed[4];
    float slipAngle[4];
    float slipAngleContactPatch[4];
    float tireSlip[4];
    float longitudinalSlip[4];
    float lateralSlip[4];
    float normalLoad[4];
    float lateralForce[4];
    float longitudinalForce[4];
    float suspensionTravel[4];
    float suspensionVelocity[4];
    float suspensionForce[4];
    float tractionControl;
    float abs;
    float turboBoost;
    float fuelFlow;
    float fuelPressure;
    float oilTemp;
    float oilPressure;
    float waterTemp;
    float waterPressure;
    float brakeTemp[4];
    float clutch;
    float brakeBias;
    float steeringTorque;
    float wheelForce[4];
    float delta;
    float heading;
    float pitch;
    float roll;
    float cgHeight;
    float carDamage[5];
    float numberOfTyresOut;
    float pitLimiterOn;
    float absInAction;
    float tcInAction;
    float tractionControlLevel;
    float kersCharge;
    float kersInput;
    float autoShifterOn;
    float rideHeightFront;
    float rideHeightRear;
    float turboRpm;
    float ballast;
    float airDensity;
    float airTemp;
    float roadTemp;
    float localAngularVelX;
    float localAngularVelY;
    float localAngularVelZ;
    float finalFF;
    float performanceMeter;
    float engineBrake;
    float ersRecoveryLevel;
    float ersPowerLevel;
    float ersHeatCharging;
    float ersIsCharging;
    float currentMaxRpm;
    float mz;
    float me;
    float surfaceGrip;
    float carSlope;
    float carRollAngle;
    float carPitchAngle;
    float tyreContactPoint[4][3];
    float tyreContactNormal[4][3];
    float tyreContactHeading[4][3];
    float brakeCompound;
    float frontBrakeCompound;
    float rearBrakeCompound;
    float padLife[4];
    float discLife[4];
    float tyreLife[4];
    float tyreDirtyLevel[4];
    float tyreCoreTemperature[4];
    float camber[4];
    float toe[4];
    float caster;
    float suspensionDamage[4];
    float engineDamage;
    float gearBoxDamage;
    float exhaustDamage;
    float drsState;
    float drsAvailable;
    float drsEnabled;
    float brakeTempAvg[4];
    float tcAvailable;
    float tcEnabled;
    float absAvailable;
    float absEnabled;
    float ignitionOn;
    float starterEngineOn;
    float isEngineRunning;
    float kerbVibration;
    float slipVibrations;
    float gVibrations;
    float absVibrations;
};
#pragma pack(pop)

struct SPageFileGraphic {
    float packetId;
    int32_t status;
    int32_t session;
    int32_t currentTime;
    int32_t lastTime;
    int32_t bestTime;
    int32_t split;
    int32_t completedLaps;
    int32_t position;
    int32_t iCurrentTime;
    int32_t iLastTime;
    int32_t iBestTime;
    int32_t sessionTimeLeft;
    float distanceTraveled;
    int32_t isInPit;
    float currentSectorTime;
    int32_t lastSectorTime;
    int32_t bestSectorTime;
    int32_t numberOfLaps;
    char tyreCompound[32];
    int32_t replayTimeMultiplier;
    float normalizedCarPosition;
    float carCoordinates[3];
};

class ACTelemetry {
public:
    ACTELEMETRY_API ACTelemetry();
    ACTELEMETRY_API ~ACTelemetry();

    ACTELEMETRY_API bool IsGameRunning() const;
    ACTELEMETRY_API bool ReadData();
    ACTELEMETRY_API void Disconnect();
    ACTELEMETRY_API bool IsConnected() const;

    ACTELEMETRY_API float GetThrottle() const;
    ACTELEMETRY_API float GetBrake() const;
    ACTELEMETRY_API float GetSpeedKmh() const;
    ACTELEMETRY_API float GetSpeedMs() const;
    ACTELEMETRY_API int32_t GetGear() const;
    ACTELEMETRY_API float GetEngineRPM() const;
    ACTELEMETRY_API float GetFuel() const;
    ACTELEMETRY_API float GetSteering() const;
    ACTELEMETRY_API float GetClutch() const;
    ACTELEMETRY_API float GetLapTime() const;
    ACTELEMETRY_API float GetLastLapTime() const;
    ACTELEMETRY_API float GetBestLapTime() const;
    ACTELEMETRY_API float GetLapDistance() const;
    ACTELEMETRY_API float GetTotalDistance() const;
    ACTELEMETRY_API float GetEngineTemperature() const;
    ACTELEMETRY_API float GetTyreWear(int wheelIndex) const;
    ACTELEMETRY_API float GetTyreTemperature(int wheelIndex) const;
    ACTELEMETRY_API float GetBrakeTemperature(int wheelIndex) const;
    ACTELEMETRY_API float GetWheelSlip(int wheelIndex) const;
    ACTELEMETRY_API float GetAcceleration(int axis) const;
    ACTELEMETRY_API float GetVelocity(int axis) const;

    ACTELEMETRY_API int32_t GetSessionStatus() const;
    ACTELEMETRY_API int32_t GetSessionType() const;
    ACTELEMETRY_API int32_t GetLapCount() const;
    ACTELEMETRY_API int32_t GetPosition() const;
    ACTELEMETRY_API std::string GetTyreCompound() const;

    ACTELEMETRY_API const SPageFilePhysics* GetPhysicsData() const;
    ACTELEMETRY_API const SPageFileGraphic* GetGraphicData() const;

private:
    void* hPhysicsMapping;
    void* hGraphicMapping;
    SPageFilePhysics* physicsData;
    SPageFileGraphic* graphicData;
    bool connected;
};