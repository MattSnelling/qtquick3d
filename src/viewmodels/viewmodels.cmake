set(QTQUICK3D_SOURCES_VIEWMODELS

)

source_group("src\\viewmodels" FILES ${QTQUICK3D_SOURCES_VIEWMODELS})

include(${PROJECT_SOURCE_DIR}/src/viewmodels/view3D/view3D.cmake)

set(QTQUICK3D_SOURCES_VIEWMODELS
	${QTQUICK3D_SOURCES_VIEWMODELS}
	${QTQUICK3D_SOURCES_VIEWMODELS_VIEW3D}
)
