project (nex-system)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/system)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/system)

set (NEX_SYSTEM_HEADERS
    ${INC_DIR}/typedefs.h
    ${INC_DIR}/utf.h
    ${INC_DIR}/utf.inl
    ${INC_DIR}/string.h
    ${INC_DIR}/string.inl
    ${INC_DIR}/instream.h
    ${INC_DIR}/outstream.h
)

set (NEX_SYSTEM_SRC
    ${SRC_DIR}/string.cpp
    ${SRC_DIR}/instream.cpp
    ${SRC_DIR}/outstream.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_SYSTEM_LIB} STATIC ${NEX_SYSTEM_HEADERS} ${NEX_SYSTEM_SRC})
