project (nex-core)

find_package(X11 REQUIRED)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/core)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/core)
set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (CORE_HEADERS
    ${INC_DIR}/windowhandle.h
    ${INC_DIR}/windowstyle.h
    ${INC_DIR}/windowprovider.h
    ${INC_DIR}/displaymode.h
    ${INC_DIR}/contextsettings.h
)

set (CORE_SRC
    ${SRC_DIR}/windowprovider.cpp
    ${SRC_DIR}/displaymode.cpp
)

set (OS_CORE_SRC
    ${OS_DIR}/oswindowprovider.h
    ${OS_DIR}/oswindowprovider.cpp
    ${OS_DIR}/displaymodeimpl.cpp
)

include_directories (${NEX_INCLUDE_DIR} ${NEX_SOURCE_DIR})
add_library (${NEX_CORE_LIB} STATIC ${CORE_HEADERS} ${CORE_SRC} ${OS_CORE_SRC})

# Properly link the required libs on the specified platform.
if (WIN32)
    # Nothing here at the moment.
elseif (UNIX)
    target_link_libraries (${NEX_CORE_LIB} X11 ${X11_Xrandr_LIB})
elseif (APPLE)
    error ("apple os is currently unsupported!")
endif (WIN32)
