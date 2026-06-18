file(GLOB RENDERER_SOURCES
    "*.cpp"
)

add_library(Renderer STATIC ${RENDERER_SOURCES})

target_include_directories(Renderer PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Renderer PUBLIC
    Core
    glad::glad
    glm::glm
)
