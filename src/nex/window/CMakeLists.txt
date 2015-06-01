project (nex-window)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/window)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/window)
set (OS_SRC ${SRC_DIR}/${NEX_OS})

set (NEX_WINDOW_HEADERS
    ${INC_DIR}/windowhandle.h
    ${INC_DIR}/window.h
)

set (NEX_WINDOW_SRC
    ${SRC_DIR}/window.cpp
)

set (NEX_OS_SRC
    ${OS_SRC}/windowimpl.h
    ${OS_SRC}/windowimpl.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_WINDOW_LIB} STATIC ${NEX_WINDOW_HEADERS} ${NEX_WINDOW_SRC} ${NEX_OS_SRC})
