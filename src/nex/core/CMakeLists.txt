project (nex-core)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/core)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/core)

set (NEX_CORE_HEADERS
    ${INC_DIR}/game.h
    ${INC_DIR}/gamelauncher.h
)

set (NEX_CORE_SRC
    ${SRC_DIR}/game.cpp
    ${SRC_DIR}/gamelauncher.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_CORE_LIB} STATIC ${NEX_CORE_HEADERS} ${NEX_CORE_SRC})
