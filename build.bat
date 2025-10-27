@echo off
REM Build script for Windows
REM Usage: build.bat [clean]

setlocal enabledelayedexpansion

set "PROJECT_DIR=%~dp0"
set "BUILD_DIR=%PROJECT_DIR%build"

echo ===============================================
echo Building normalize project with CMake
echo ===============================================

if "%1"=="clean" (
    echo Cleaning build directory...
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
    echo Done!
    exit /b 0
)

REM Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

REM Configure with CMake
echo Configuring with CMake...
cmake -DCMAKE_BUILD_TYPE=Release ..
if errorlevel 1 (
    echo CMake configuration failed!
    exit /b 1
)

REM Build
echo Building...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo.
echo ===============================================
echo Build successful!
echo ===============================================
echo.
echo Executable: %BUILD_DIR%\Release\normalize.exe
echo.
echo Usage examples:
echo   %BUILD_DIR%\Release\normalize.exe ..\tests\sample_data.csv baseline
echo   %BUILD_DIR%\Release\normalize.exe ..\tests\data_1000x10.csv quake
echo   %BUILD_DIR%\Release\normalize.exe ..\tests\data_1000x100.csv sse
echo.
