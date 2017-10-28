#pragma once

// Classes for game completition, such as number of completed levels, unlocked levels, how many stars per level, etc

#include <string>
#include "GameLevel.h"

struct GameCompletition
{
};

struct LevelCompletition {
    int stars;
    int tries; // Total number of tries for the level
    int bestScore;
    LevelCompletition(int stars, int tries, int bestScore) : stars(stars), tries(tries), bestScore(bestScore) {}
};

LevelCompletition getCompletitionForLevel(GameLevel level);