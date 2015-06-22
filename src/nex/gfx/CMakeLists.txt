project (nex-gfx)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/gfx)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/gfx)
set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (HEADERS
    ${INC_DIR}/color.h
    ${INC_DIR}/image.h
)

set (SRC
    ${SRC_DIR}/color.cpp
    ${SRC_DIR}/image.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_GFX_LIB} STATIC ${HEADERS} ${SRC})
