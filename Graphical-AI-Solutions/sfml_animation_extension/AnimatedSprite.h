#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

struct AnimFrameData {
	// the index of the first frame of an animation
	int startFrame;
	// the total number of frames for said animation
	int numFrames;
	// the offset of the first frame of an animation
	int offsetX;
	int offsetY;
	// the size of each frame of an animation
	int animWidth;
	int animHeight;
};

struct AnimData {
	// ImageFile with all the animations
	sf::Texture spriteSheet;
	// the frame data for all the different animations
	AnimFrameData* frameInfo;
	// the number of different animations
	unsigned int numOfAnimatons;
};

class AnimatedSprite : sf::Sprite {
	// All of the animation data (includes ImageFile and FrameData)
	AnimData animData;
	// The particular animation that is active
	int animNum;
	// The frame number of the active animation that's being displayed
	int frameNum;
	// Anmount of time the current frame has been displayed
	float frameTime;
	// The FPS the animation is running at (24FPS by default)
	float animFPS = 24.0f;

	void Initialize(AnimData, int startingAnimNum);
	void UpdateAnim(float deltaTime);
	void ChangeAnim(int num);
};