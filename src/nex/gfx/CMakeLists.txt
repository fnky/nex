project (nex-gfx)

find_library (freetype STATIC REQUIRED)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/gfx)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/gfx)
set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (HEADERS
    ${INC_DIR}/color.h
    ${INC_DIR}/image.h

    ${INC_DIR}/drawtype.h
    ${INC_DIR}/shader.h
    ${INC_DIR}/vertex2d.h
    ${INC_DIR}/vertex3d.h
    ${INC_DIR}/vertexlist2d.h
    ${INC_DIR}/vertexlist3d.h
    ${INC_DIR}/vertexarray.h
    ${INC_DIR}/vertexbuffer.h
    ${INC_DIR}/elementbuffer.h
    
    ${INC_DIR}/texture.h
    ${INC_DIR}/glyph.h
    ${INC_DIR}/font.h

    ${INC_DIR}/text.h
)

set (SRC
    ${SRC_DIR}/color.cpp
    ${SRC_DIR}/image.cpp
    ${SRC_DIR}/imageloader.h
    ${SRC_DIR}/imageloader.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/shader.cpp
    ${SRC_DIR}/vertexlist2d.cpp
    ${SRC_DIR}/vertexlist3d.cpp
    ${SRC_DIR}/vertexarray.cpp
    ${SRC_DIR}/vertexbuffer.cpp
    ${SRC_DIR}/elementbuffer.cpp
    ${SRC_DIR}/font.cpp
    ${SRC_DIR}/text.cpp
)

include_directories (${NEX_INCLUDE_DIR} ${NEX_SOURCE_DIR})
include_directories (${NEX_STB_IMAGE_INCLUDE})

add_library (${NEX_GFX_LIB} STATIC ${HEADERS} ${SRC})

target_link_libraries (${NEX_GFX_LIB} freetype)
