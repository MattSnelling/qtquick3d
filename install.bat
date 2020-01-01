@echo off
setlocal

set QT_BIN_PATH=%1
set BUILD_TYPE=%2
set SOURCE_PATH=%3
set TARGET_PATH=%4

REM Necessary for Qt
set VCINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC

%QT_BIN_PATH%/windeployqt.exe --dir "%TARGET_PATH%" --libdir "%TARGET_PATH%" --qmldir %SOURCE_PATH% --%BUILD_TYPE% --force --compiler-runtime "%TARGET_PATH%/qtquick3d.exe"
if %errorlevel% NEQ 0 ( exit /b %errorlevel% )
