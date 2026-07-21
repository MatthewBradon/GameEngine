add_library(Renderer INTERFACE)

target_include_directories(Renderer INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Renderer INTERFACE
    Core
    glm::glm
)
