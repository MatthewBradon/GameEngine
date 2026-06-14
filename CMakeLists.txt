cmake_minimum_required(VERSION 3.15)
project(Sigil)
set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GLUT REQUIRED)
find_package(Stb REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Freetype CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Sigil executable
add_executable(Sigil
    src/main.cpp
    src/Engine.cpp
    src/Core/Window.cpp
    src/Core/Log.cpp
    src/Core/Input.cpp
    src/Core/Event/EngineInput.cpp
    src/Renderer/RenderCommand.cpp
    src/Renderer/BufferLayout.cpp
    src/Renderer/VertexArrayObject.cpp
    src/Renderer/VertexBufferObject.cpp
    src/Renderer/IndexBufferObject.cpp
    src/Renderer/Shader.cpp
    src/Platform/GLFWInputBridge.cpp
    src/Platform/OpenGL/OpenGLShader.cpp
    src/Platform/OpenGL/OpenGLVertexBufferObject.cpp
    src/Platform/OpenGL/OpenGLIndexBufferObject.cpp
    src/Platform/OpenGL/OpenGLVertexArrayObject.cpp
)

# Set output directory for all configurations
set_target_properties(Sigil PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}"
)

if (WIN32)
target_include_directories(Sigil PRIVATE
    ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ThirdParty
)
elseif(APPLE)
target_include_directories(Sigil PRIVATE
    ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/arm64-osx/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ThirdParty
)
endif()

# Link libraries
target_link_libraries(Sigil PRIVATE
    glad::glad
    glfw
    imgui::imgui
    GLUT::GLUT
    glm::glm
    assimp::assimp
    Freetype::Freetype
    spdlog::spdlog
)