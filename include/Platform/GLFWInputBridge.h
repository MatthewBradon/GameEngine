#pragma once

struct GLFWwindow;

class EventQueue;

namespace GLFWInputBridge
{
    void Attach(GLFWwindow* window, EventQueue* queue);
}