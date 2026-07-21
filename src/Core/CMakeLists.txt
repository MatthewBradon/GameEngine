file(GLOB CORE_SOURCES
    "*.cpp"
    "Filesystem/*.cpp"
    "Memory/*.cpp"
    "Event/*.cpp"
)

add_library(Core STATIC ${CORE_SOURCES})

target_include_directories(Core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ThirdParty
)

target_link_libraries(Core PUBLIC
    spdlog::spdlog
    PlatformCommon
)
