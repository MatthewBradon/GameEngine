file(GLOB RENDERER_SOURCES
    "*.cpp"
    "Vulkan/*.cpp"
)


add_library(Renderer ${RENDERER_SOURCES})

target_include_directories(Renderer PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Renderer PUBLIC
    Core
    SDL3::SDL3
    spdlog::spdlog
    glm::glm
    KTX::ktx
    tinyobjloader::tinyobjloader
    volk::volk
    volk::volk_headers
    Vulkan::Headers
    GPUOpen::VulkanMemoryAllocator
    slang::slang
)
