file(GLOB PLATFORM_SOURCES
    "*.cpp"
)

add_library(PlatformCommon STATIC ${PLATFORM_SOURCES})

target_include_directories(PlatformCommon PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(PlatformCommon PUBLIC
    SDL3::SDL3
)

target_compile_options(PlatformCommon PRIVATE
    /utf-8
)

