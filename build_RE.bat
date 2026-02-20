@echo off

rd /s /q "bin"
rd /s /q "build"


cmake -S source -B build
REM cmake --build build --config Release

pause