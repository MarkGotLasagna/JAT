@echo off
set QT_DIR=C:\Qt\6.8.1\msvc2022_64
set BUILD_DIR=build\Release

REM Run windeployqt to copy all required Qt dependencies
"%QT_DIR%\bin\windeployqt.exe" --release --no-compiler-runtime --no-translations "%BUILD_DIR%\JAT.exe"

echo Deployment complete! 