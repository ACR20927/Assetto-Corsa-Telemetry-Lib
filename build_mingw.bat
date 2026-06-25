@echo off
echo Building ACTelemetry with MinGW...

setlocal

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: g++ not found. Please install MinGW and add it to PATH.
    pause
    exit /b 1
)

echo.
echo Compiling actelemetry.dll...
g++ -shared -o actelemetry.dll actelemetry.cpp -Wl,--export-all-symbols -lpsapi -O2 -Wall

if %errorlevel% neq 0 (
    echo Error: Failed to compile actelemetry.dll
    pause
    exit /b 1
)

echo.
echo Compiling ac_telemetry_test.exe...
g++ -o ac_telemetry_test.exe test_main.cpp actelemetry.dll -O2 -Wall

if %errorlevel% neq 0 (
    echo Error: Failed to compile ac_telemetry_test.exe
    pause
    exit /b 1
)

echo.
echo Build completed successfully!
echo Output files:
echo   - actelemetry.dll
echo   - ac_telemetry_test.exe
pause