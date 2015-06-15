project (nex-test)

find_library (${NEX_SYSTEM_LIB} STATIC)
find_library (${NEX_MATH_LIB} STATIC)
find_library (${NEX_FILESYSTEM_LIB} STATIC)

set (TEST_SRC
    main.cpp
)

set (TEST_HEADERS

)

set (EXE_NAME nex-test)

add_executable (${EXE_NAME} ${TEST_SRC} ${TEST_HEADERS})
include_directories (${NEX_INCLUDE_DIR})

target_link_libraries(${EXE_NAME} ${NEX_SYSTEM_LIB} ${NEX_MATH_LIB} ${NEX_FILESYSTEM_LIB})
