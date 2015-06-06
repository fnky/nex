project (nex-core)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/core)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/core)
set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (CORE_HEADERS
    ${INC_DIR}/windowhandle.h
    ${INC_DIR}/windowstyle.h
    ${INC_DIR}/windowprovider.h
)

set (CORE_SRC
    ${SRC_DIR}/windowprovider.cpp
)

set (OS_CORE_SRC
    ${OS_DIR}/oswindowprovider.h
    ${OS_DIR}/oswindowprovider.cpp
)

include_directories (${NEX_INCLUDE_DIR} ${NEX_SOURCE_DIR})
add_library (${NEX_CORE_LIB} STATIC ${CORE_HEADERS} ${CORE_SRC} ${OS_CORE_SRC})
