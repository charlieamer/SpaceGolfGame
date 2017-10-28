#pragma once

#include <string>
#include <vector>

struct GameLevel
{
    GameLevel(std::string level, int par, int levelNumber) : level(level), par(par), levelNumber(levelNumber) {}
    std::string level;
    int par;
    int levelNumber;
};

std::vector<GameLevel> getAllGameLevels();