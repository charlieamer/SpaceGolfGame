#include "GameLevel.h"

std::vector<GameLevel> getAllGameLevels() {
    return {
        GameLevel("levels/test-2.gleed", 3, 1),
        GameLevel("levels/test-2.gleed", 4, 2),
        GameLevel("levels/test-2.gleed", 3, 3)
    };
}