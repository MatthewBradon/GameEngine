#pragma once

#include "Core/Window.h"
#include "Renderer/RHI/RHI.h"

#include <glm/glm.hpp>
#include <array>
#include <string>


class Renderer
{
public:

    void Initialize(Window&);

    void Shutdown();

    void LoadBasicShader();

private:

};
