
set(QTQUICK3D_HEADERS
	${PROJECT_SOURCE_DIR}/include/Common.h
	${PROJECT_SOURCE_DIR}/include/Singleton.h
)

source_group("include" FILES ${QTQUICK3D_HEADERS})

include(${PROJECT_SOURCE_DIR}/include/utilities/utilities.cmake)
include(${PROJECT_SOURCE_DIR}/include/viewmodels/viewmodels.cmake)

set(QTQUICK3D_HEADERS
	${QTQUICK3D_HEADERS}
	${QTQUICK3D_HEADERS_UTILITIES}
	${QTQUICK3D_HEADERS_VIEWMODELS}
)
