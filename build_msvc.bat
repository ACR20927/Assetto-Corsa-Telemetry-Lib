@echo off
echo Building ACTelemetry with MSVC...

setlocal

set "VC_PATH="
for /f "tokens=*" %%i in ('where /r "C:\Program Files (x86)\Microsoft Visual Studio" "vcvars64.bat" 2^>nul') do (
    set "VC_PATH=%%i"
    goto :found_vc
)
for /f "tokens=*" %%i in ('where /r "C:\Program Files\Microsoft Visual Studio" "vcvars64.bat" 2^>nul') do (
    set "VC_PATH=%%i"
    goto :found_vc
)

:found_vc
if not defined VC_PATH (
    echo Error: vcvars64.bat not found. Please install Visual Studio with C++ development tools.
    pause
    exit /b 1
)

echo Found vcvars64.bat: %VC_PATH%
call "%VC_PATH%"

echo.
echo Compiling actelemetry.dll...
cl /EHsc /W4 /O2 /MT /D ACTELEMETRY_EXPORTS /D UNICODE /D _UNICODE /LD /Fe:actelemetry.dll actelemetry.cpp /link psapi.lib

if %errorlevel% neq 0 (
    echo Error: Failed to compile actelemetry.dll
    pause
    exit /b 1
)

echo.
echo Compiling ac_telemetry_test.exe...
cl /EHsc /W4 /O2 /MT /D UNICODE /D _UNICODE /Fe:ac_telemetry_test.exe test_main.cpp /link actelemetry.lib

if %errorlevel% neq 0 (
    echo Error: Failed to compile ac_telemetry_test.exe
    pause
    exit /b 1
)

echo.
echo Build completed successfully!
echo Output files:
echo   - actelemetry.dll
echo   - actelemetry.lib
echo   - ac_telemetry_test.exe
pause