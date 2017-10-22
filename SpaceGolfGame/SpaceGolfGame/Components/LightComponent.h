#pragma once

#include "../LevelParsing/GleedColor.h"
#include "../utilities.h"

struct LightComponent {
    float colorR, colorG, colorB;
    LightComponent(GleedColor color) {
        colorR = color.r / 255.0f;
        colorG = color.g / 255.0f;
        colorB = color.b / 255.0f;
    }
};