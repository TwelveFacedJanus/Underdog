#pragma once
#include <string>
#include <vector>
#include <memory>
#include "vulkan_support.hpp"
// #include <glm/mat4x4.hpp> // Если понадобится матрица трансформации

class Underdog; // Forward declaration

class Component {
public:
    std::string uuid;
    std::vector<std::shared_ptr<Component>> children;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    Component(const std::string& uuid,
              const std::string& vertShader = "",
              const std::string& fragShader = "")
        : uuid(uuid), vertexShaderPath(vertShader), fragmentShaderPath(fragShader) {}

    virtual ~Component() = default;

    void addChild(const std::shared_ptr<Component>& child) {
        children.push_back(child);
    }

    // Виртуальный метод рендера
    virtual void render(Underdog& vk /*, const glm::mat4& transform = glm::mat4(1.0f) */) {
        // По умолчанию рендерим всех детей
        for (auto& child : children) {
            child->render(vk /*, transform */);
        }
    }
};

class Rect : public Component {
public:
    Rect(const std::string& uuid,
         const std::string& vertShader = "shaders/rect.vert",
         const std::string& fragShader = "shaders/rect.frag")
        : Component(uuid, vertShader, fragShader) {}

    void render(Underdog& vk /*, const glm::mat4& transform = glm::mat4(1.0f) */) override {
        vk.drawRect();
        Component::render(vk /*, transform */);
    }
};

class Triangle : public Component {
public:
    Triangle(const std::string& uuid,
             const std::string& vertShader = "shaders/triangle.vert",
             const std::string& fragShader = "shaders/triangle.frag")
        : Component(uuid, vertShader, fragShader) {}

    void render(Underdog& vk /*, const glm::mat4& transform = glm::mat4(1.0f) */) override {
        vk.drawTriangle();
        Component::render(vk /*, transform */);
    }
};
