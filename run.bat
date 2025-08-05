@echo off
zig cc -o main.exe main.c -I"C:\raylib\include" "C:\raylib\lib\libraylib.a" -lopengl32 -lgdi32 -lwinmm

if errorlevel 1 (
    exit /b
)

main.exe

echo.