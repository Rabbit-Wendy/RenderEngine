@echo off

rd /s /q "build"

pause

cmake -S source -B build
REM cmake --build build --config Release

pause