project (nex-filesystem)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/filesystem)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/filesystem)
set (OS_DIR ${SRC_DIR}/${NEX_OS})

set (HEADERS
    ${INC_DIR}/file.h
    ${INC_DIR}/fileinfo.h
    ${INC_DIR}/directory.h
    ${INC_DIR}/directoryinfo.h
    ${INC_DIR}/path.h
    ${INC_DIR}/fileinputstream.h
    ${INC_DIR}/fileoutputstream.h
)

set (SRC
    ${SRC_DIR}/file.cpp
    ${SRC_DIR}/fileinfo.cpp
    ${SRC_DIR}/directory.cpp
    ${SRC_DIR}/directoryinfo.cpp
    ${SRC_DIR}/path.cpp
    ${SRC_DIR}/fileinputstream.cpp
    ${SRC_DIR}/fileoutputstream.cpp
)

set (OS_SRC
    ${OS_DIR}/osfileimpl.cpp
    ${OS_DIR}/osdirectoryimpl.cpp
    ${OS_DIR}/ospathimpl.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_FILESYSTEM_LIB} STATIC ${HEADERS} ${SRC} ${OS_SRC})
target_link_libraries (${NEX_FILESYSTEM_LIB} ${NEX_SYSTEM_LIB})
if (WIN32)
    target_link_libraries (${NEX_FILESYSTEM_LIB} Shlwapi)
endif (WIN32)
