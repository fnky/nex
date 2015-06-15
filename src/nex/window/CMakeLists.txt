project (nex-window)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/window)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/window)

set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (WINDOW_HEADERS
    ${INC_DIR}/windowhandle.h
    ${INC_DIR}/windowstyle.h
    ${INC_DIR}/window.h
)

set (WINDOW_SRC
    ${SRC_DIR}/window.cpp
)

set (OS_WINDOW_SRC
)

# Setup the default include paths.
include_directories (${NEX_INCLUDE_DIR} ${NEX_SOURCE_DIR})

# Setup our static library.
add_library (${NEX_WINDOW_LIB} STATIC ${WINDOW_HEADERS} ${WINDOW_SRC})

# Properly link the required libs on the specified platform.
if (WIN32)
    # TODO: Tyler
elseif (UNIX)
    target_link_libraries (${NEX_WINDOW_LIB} X11 ${X11_Xrandr_LIB})
elseif (APPLE)
    error ("apple os is currently unsupported!")
endif (WIN32)
