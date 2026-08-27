cmake_minimum_required(VERSION 3.15)
project(Sigil)
set(CMAKE_CXX_STANDARD 20)

# Packages
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(ktx CONFIG REQUIRED)
find_package(volk CONFIG REQUIRED)
find_package(Vulkan)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(slang CONFIG REQUIRED)


# Sigil executable
add_subdirectory(src/Platform)
add_subdirectory(src/Core)
add_subdirectory(src/Renderer)
add_subdirectory(src/Core/Assets)
add_subdirectory(ThirdParty)

add_executable(Sigil
    src/main.cpp
    src/Engine.cpp
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
    ${CMAKE_SOURCE_DIR}/ThirdParty/tlsf
    ${CMAKE_SOURCE_DIR}/src/Renderer
)
elseif(APPLE)
target_include_directories(Sigil PRIVATE
    ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/arm64-osx/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ThirdParty
    ${CMAKE_SOURCE_DIR}/src/Renderer
)
endif()

# Link libraries
target_link_libraries(Sigil PRIVATE
    Core
    Renderer
    Assets
    ThirdParty
    imgui::imgui
    glm::glm
    Freetype::Freetype
    spdlog::spdlog
    yaml-cpp::yaml-cpp
    SDL3::SDL3
    KTX::ktx
    tinyobjloader::tinyobjloader
    volk::volk
    volk::volk_headers
    Vulkan::Headers
    GPUOpen::VulkanMemoryAllocator
    slang::slang
)