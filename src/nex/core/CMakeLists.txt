project (nex-core)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/core)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/core)
set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (CORE_HEADERS
    ${INC_DIR}/event.h
    ${INC_DIR}/eventprovider.h
    ${INC_DIR}/gfxprovider.h
)

set (CORE_SRC
    ${SRC_DIR}/eventproviderimpl.h
    ${SRC_DIR}/eventproviderimpl.cpp
    ${SRC_DIR}/eventprovider.cpp

    ${SRC_DIR}/gfxproviderimpl.h
    ${SRC_DIR}/gfxproviderimpl.cpp
    ${SRC_DIR}/gfxprovider.cpp
)

set (CORE_OS_SRC
    ${OS_DIR}/oseventproviderimpl.h
    ${OS_DIR}/oseventproviderimpl.cpp

    ${OS_DIR}/osgfxproviderimpl.h
    ${OS_DIR}/osgfxproviderimpl.cpp
)


include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_CORE_LIB} STATIC ${CORE_HEADERS} ${CORE_SRC} ${CORE_OS_SRC})
