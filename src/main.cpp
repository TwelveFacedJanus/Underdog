#include <iostream>
#include "vulkan_support.hpp"
#include "components.hpp"


int main() {
    Underdog underdog;
    auto rect = std::make_shared<Rect>("rect1");
    auto triangle = std::make_shared<Triangle>("triangle1");
    rect->addChild(triangle);
    underdog.components.push_back(rect);
    underdog.mainLoop();
}