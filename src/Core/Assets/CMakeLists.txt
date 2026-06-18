file(GLOB ASSET_SOURCES
    "*.cpp"
)

add_library(Assets STATIC ${ASSET_SOURCES})

target_include_directories(Assets PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Assets PUBLIC
    Core
    yaml-cpp::yaml-cpp
)
