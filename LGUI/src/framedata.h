#pragma once

#include "gmath.h"
#include <string>

class FrameData{
public:
    FrameData() = default;
    ~FrameData() = default;

    float            rotation   = 0;
    GMath::GVec2f    anchorPoint {0.0f, 0.0f};
    GMath::UDim2     position    {{0, 0},{0.0}};
    GMath::UDim2     size        {{0, 0},{24, 24}};

    GMath::Color4    color       {127, 127, 127, 255};
    std::string      text       = "PLACEHOLDER";

    //Frame Class PTR
    void*            parent     = nullptr;
    int              layer      = 0;
};