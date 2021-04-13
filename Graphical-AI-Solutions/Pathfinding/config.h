#pragma once
#include <vector>

// Render Window
#define WINDOW_WIDTH 288
#define WINDOW_HEIGHT 288

// Map-Config
#define TILESET_TEXTURE_FILE ("Resources/Images/tileset.png")
#define MAP_NAME "maze"
#define TILESIZE 32
#define MAP_WIDTH 9
#define MAP_HEIGHT 9
#define MAP_WALLS std::vector<unsigned int> {1}
#define AMOUNT_OF_WALLS 25

// AI-Character
#define CHARACTER_SPRITESHEET_FILE ("Resources/Images/Positiv Animation Sheet.png")
#define AI_CHARACTER_NAME "problemSolver"
#define CHARACTER_START_X 0
#define CHARACTER_START_Y 0
#define AI_MOVING_SPEED 20.f

// AI-Character animation states
#define THINKING_ANIMATION 0
#define WALKING_UP_ANIMATION 0
#define WALKING_DOWN_ANIMATION AnimFrameData{ sf::Rect<int>(0, 5 * 48, 48, 48), 5, "walking down" }
#define WALKING_RIGHT_ANIMATION 0
#define WALKING_LEFT_ANIMATION 0
#define CELEBRATE_ANIMATION AnimFrameData{ sf::Rect<int>(6 * 48, 0, 48, 48), 5, "celebrate" }
#define CRY_ANIMATION 0