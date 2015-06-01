project (nex-game)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/game)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/game)

set (NEX_GAME_HEADERS
    ${INC_DIR}/game.h
    ${INC_DIR}/gamelauncher.h
)

set (NEX_GAME_SRC
    ${SRC_DIR}/game.cpp
    ${SRC_DIR}/gamelauncher.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_GAME_LIB} STATIC ${NEX_GAME_HEADERS} ${NEX_GAME_SRC})
