#pragma once

#include "../LevelParsing/GleedColor.h"
#include "../utilities.h"

struct LightComponent {
    float colorR, colorG, colorB;
    LightComponent(GleedColor color) {
        colorR = color.r;
        colorG = color.g;
        colorB = color.b;
    }
};