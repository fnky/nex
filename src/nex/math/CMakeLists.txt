project (nex-math)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/math)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/math)

set (NEX_MATH_HEADERS

    ${INC_DIR}/vec2.h
    ${INC_DIR}/vec2.inl

    ${INC_DIR}/vec3.h
    ${INC_DIR}/vec3.inl

    ${INC_DIR}/vec4.h
    ${INC_DIR}/vec4.inl

    ${INC_DIR}/matrix.h
    ${INC_DIR}/matrix.inl

    ${INC_DIR}/quaternion.h
    ${INC_DIR}/quaternion.inl

    ${INC_DIR}/rect.h
    ${INC_DIR}/rect.inl

    ${INC_DIR}/ray.h
    ${INC_DIR}/ray.inl

    ${INC_DIR}/plane.h
    ${INC_DIR}/plane.inl

    ${INC_DIR}/planeintersectiontype.h
    ${INC_DIR}/containmenttype.h

    ${INC_DIR}/boundingbox.h
    ${INC_DIR}/boundingsphere.h
    ${INC_DIR}/boundingfrustum.h

    ${INC_DIR}/gjk.h

    ${INC_DIR}/mathhelper.h
)

set (NEX_MATH_SRC
    ${SRC_DIR}/gjk.cpp
    ${SRC_DIR}/ray.cpp
    ${SRC_DIR}/plane.cpp
    ${SRC_DIR}/boundingbox.cpp
    ${SRC_DIR}/boundingsphere.cpp
    ${SRC_DIR}/boundingfrustum.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_MATH_LIB} STATIC ${NEX_MATH_HEADERS} ${NEX_MATH_SRC})
