cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(lib/hge181)

project(Racer CXX)

SET (RACER_INCLUDE_DIR ./include)
SET (RACER_SOURCE_DIR ./src)

file(GLOB_RECURSE RACER_HEADER_FILES ${RACER_INCLUDE_DIR}/*.h)
file(GLOB_RECURSE RACER_SOURCE_FILES ${RACER_SOURCE_DIR}/*.cpp)

include_directories(${RACER_INCLUDE_DIR})

SET (RACER_ALL_FILES
    ${RACER_HEADER_FILES}
    ${RACER_SOURCE_FILES}
)

SET (DIRECTX_SDK_DIR "D:/Programming/DXSDK")

#------ additional includes ------
include_directories( ${HGE_SOURCE_DIR}/include )
include_directories( ${HGE_SOURCE_DIR}/src/libPNG )
include_directories( ${HGE_SOURCE_DIR}/src/zlib-1.2.5 )
include_directories( ${DIRECTX_SDK_DIR}/include )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( hge )


#WIN32
add_executable(Racer WIN32 ${RACER_ALL_FILES})

if( MSVC )
    SET_TARGET_PROPERTIES( Racer PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()

#target_link_libraries(app School)