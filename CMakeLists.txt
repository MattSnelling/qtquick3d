cmake_minimum_required(VERSION 3.16.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(qtquick3d LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(BUILD_QT_ENVIRONMENT "Build the Qt environment to run the executable." OFF)

# Warning level
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -fno-strict-aliasing")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedef")
endif()

# Warning as error
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/WX-*")
		string(REGEX REPLACE "/WX-*" "/WX" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127") #warning 'conditional expression is constant'
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

find_package(Qt5 5.14.0 EXACT COMPONENTS Core Gui Quick Qml Quick3D REQUIRED)

include(${PROJECT_SOURCE_DIR}/include/include.cmake)
include(${PROJECT_SOURCE_DIR}/src/src.cmake)

set(QTQUICK3D_RESOURCES
	${PROJECT_SOURCE_DIR}/qml.qrc
)

add_executable(${PROJECT_NAME} ${QTQUICK3D_HEADERS} ${QTQUICK3D_SOURCES} ${QTQUICK3D_RESOURCES})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC "/fp:fast") # Floating point model
	target_compile_options(${PROJECT_NAME} PUBLIC "/MP") # Multi-processor compilation
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/entry:mainCRTStartup")

	if(BUILD_QT_ENVIRONMENT)
    	find_program(WINDEPLOYQT_EXE NAMES windeployqt PATHS ${CMAKE_PREFIX_PATH})
		if(NOT WINDEPLOYQT_EXE)
			message(FATAL_ERROR "Could not find windeployqt")
		endif()
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND cmd /c ${PROJECT_SOURCE_DIR}/install.bat ${CMAKE_PREFIX_PATH}/bin $<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>$<$<CONFIG:RelWithDebInfo>:release> ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}/$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo>)
	endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
	${Qt5Quick3D_OWN_PRIVATE_INCLUDE_DIRS}
	${Qt5Quick3DRender_OWN_PRIVATE_INCLUDE_DIRS}
	${Qt5Quick3DRuntimeRender_OWN_PRIVATE_INCLUDE_DIRS}
	${Qt5Quick3DUtils_OWN_PRIVATE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Quick
	Qt5::Qml
	Qt5::Quick3D
)

# Assets
if(MSVC)
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND cmd /c ${CMAKE_PREFIX_PATH}/bin/rcc -binary ${PROJECT_SOURCE_DIR}/assets.qrc -o ${PROJECT_BINARY_DIR}/$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>$<$<CONFIG:RelWithDebInfo>:RelWithDebInfo>/assets.rcc
    DEPENDS assets.qrc
  )
else()
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_PREFIX_PATH}/bin/rcc -binary ${PROJECT_SOURCE_DIR}/assets.qrc -o ${PROJECT_BINARY_DIR}/assets.rcc
    DEPENDS assets.qrc
  )
endif()
