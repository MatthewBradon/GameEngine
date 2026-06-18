file(GLOB OPENGL_SOURCES
    "*.cpp"
)

add_library(OpenGLPlatform STATIC ${OPENGL_SOURCES})

target_include_directories(OpenGLPlatform PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(OpenGLPlatform PUBLIC
    Renderer
    glad::glad
    glfw
)
