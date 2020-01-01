@echo off
setlocal

REM Variables
set BUILD_GENERATOR=Visual Studio 16 2019
set BUILD_TOOLCHAIN=v142
set BUILD_DIR_PREFIX=build

set QT_ROOT=C:\Qt
set QT_VERSION=5.14.0
set QT_BUILD_64=msvc2017_64

set QT_PATH=%QT_ROOT%\%QT_VERSION%\

REM Find CMake
set CMAKE=cmake.exe
WHERE "%CMAKE%"
if %errorlevel% NEQ 0 (
	if exist "C:\Program Files\CMake\bin\%CMAKE%" (
		set CMAKE="C:\Program Files\CMake\bin\%CMAKE%"
		goto :CHOICE_RESET
	)
	
	if exist "C:\Program Files (x86)\CMake\bin\%CMAKE%" (
		set CMAKE="C:\Program Files (x86)\CMake\bin\%CMAKE%"
		goto :CHOICE_RESET
	)
	
	echo Cannot locate CMake, either it is not installed or it is not in the default locations.
	echo Please install CMake and run again this batch
	exit /B
)

REM Choice: reset the build
:CHOICE_RESET
set /P c=Do you want to reset the build[Y/N]? 
if /I "%c%" EQU "Y" (
	set BUILD_RESET=1
	goto :CONFIGURE
)
if /I "%c%" EQU "N" (
	set BUILD_RESET=0
	goto :CONFIGURE
)
goto :CHOICE_RESET

:CONFIGURE
set BUILD_GENERATOR="%BUILD_GENERATOR%"
set BUILD_DIR=%BUILD_DIR_PREFIX%-x64

if %BUILD_RESET%==1 (
	if exist %BUILD_DIR% (
		rmdir /S /Q %BUILD_DIR%
		if %errorlevel% NEQ 0 exit /B
	)
)

if not exist %BUILD_DIR% (
	mkdir %BUILD_DIR%
	if %errorlevel% NEQ 0 exit /B
)

set QT_PATH=%QT_PATH%%QT_BUILD_64%

pushd %BUILD_DIR%
	%CMAKE% -G %BUILD_GENERATOR% -T "%BUILD_TOOLCHAIN%" -DCMAKE_PREFIX_PATH="%QT_PATH%" -DBUILD_QT_ENVIRONMENT=ON .. 
popd
