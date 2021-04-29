#pragma once
#include "AnimatedSprite.h"

// Render Window
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 960

// Map-Config
#define TILESET_TEXTURE_FILE ("Resources/Images/tileset.png")
#define MAP_NAME "map"
#define TILESIZE 32
#define MAP_WIDTH 30
#define MAP_HEIGHT 30
#define NUMBER_OF_GRASS_TILES 9

// Animation
#define FRAME_RATE 12

// Sheep
#define SHEEP_SPAWN_AREA sf::Vector2u(100, 100)
#define SHEEP_NAME "sheep"
#define SHEEP_SPRITESHEET_FILE "Resources/Images/flockSpriteSheet.png"
#define SHEEP_WALKING_SPEED 0
#define SHEEP_RUNNING_SPEED 0
#define NUMBER_OF_SHEEP 20
// Sheep Animations
#define SHEEP_IDLE_ANIMATION AnimFrameData{ sf::Rect<int>(0, 0, 20, 24), 6, "idle" }
#define SHEEP_STRETCHING_ANIMATION AnimFrameData{ sf::Rect<int>(0, 24, 20, 24), 25, "stretching" }
#define SHEEP_WALKING_ANIMATION AnimFrameData{ sf::Rect<int>(0, 48, 20, 24), 7, "walking" }
#define SHEEP_EATING_ANIMATION AnimFrameData{ sf::Rect<int>(160, 48, 20, 24), 0, "eating" }
#define SHEEP_DYING_ANIMATION AnimFrameData{ sf::Rect<int>(140, 0, 20, 24), 9, "dying" }
// Sheep Behavior Weights

// Predator
#define PREDATOR_SPAWN_AREA sf::Vector2u(800, 800)
#define PREDATOR_NAME "predator"
#define PREDATOR_SPRITESHEET_FILE "Resources/Images/flockSpriteSheet.png"
#define PREDATOR_WALKING_SPEED 0
#define PREDATOR_RUNNING_SPEED 0
#define NUMBER_OF_PREDATORS 5
// Predator Animations
#define PREDATOR_IDLE_ANIMATION AnimFrameData{ sf::Rect<int>(0, 78, 21, 26), 5, "idle" }
#define PREDATOR_RUNNING_ANIMATION AnimFrameData{ sf::Rect<int>(273, 78, 21, 26), 4, "running" }
#define PREDATOR_WALKING_ANIMATION AnimFrameData{ sf::Rect<int>(126, 78, 21, 26), 6, "walking" }
#define PREDATOR_EATING_ANIMATION AnimFrameData{ sf::Rect<int>(104, 0, 21, 26), 10, "eating" }
// Predator Behavior Weights
