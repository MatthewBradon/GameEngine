#pragma once

#include "ShaderStage.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

struct CompiledShader
{
    ShaderStage Stage;
    std::string EntryPoint;
    std::vector<uint32_t> SpirV;

    bool IsValid() const
    {
        return !SpirV.empty();
    }
};

class ShaderCompiler
{
public:

    ShaderCompiler();
    ~ShaderCompiler();

    ShaderCompiler(const ShaderCompiler&) = delete;
    ShaderCompiler& operator=(const ShaderCompiler&) = delete;

    bool Initialize();
    void Shutdown();

    bool Compile(
        const std::string& path,
        ShaderStage stage,
        const std::string& entryPoint,
        CompiledShader& output);

private:

    struct Impl;

    std::unique_ptr<Impl> m_Impl;
};
