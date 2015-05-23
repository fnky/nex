project (nex-math)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/math)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/math)

set (NEX_MATH_HEADERS
    ${INC_DIR}/vec2.h
    ${INC_DIR}/vec2.inl
    ${INC_DIR}/mathhelper.h
)

set (NEX_MATH_SRC
    ${SRC_DIR}/mathhelper.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_MATH_LIB} STATIC ${NEX_MATH_HEADERS} ${NEX_MATH_SRC})
