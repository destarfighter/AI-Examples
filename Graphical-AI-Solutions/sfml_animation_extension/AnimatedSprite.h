#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

struct AnimFrameData {
	// the offset of the first frame and the size of the images of an animation
	sf::Rect<unsigned int> animOffset;
	// the total number of frames for said animation
	unsigned int numFrames;
};

struct AnimData {
	// ImageFile with all the animations
	std::shared_ptr<sf::Texture> spriteSheet_ptr;
	// the frame data for all the different animations
	std::shared_ptr<AnimFrameData[]> frameInfo;
	// the number of different animations
	unsigned int numOfAnimatons;
};

class AnimatedSprite : sf::Sprite {
	// All of the animation data (includes ImageFile and FrameData)
	AnimData animData;
	// The particular animation that is active
	unsigned int animNum{0};
	// The frame number of the active animation that's being displayed
	unsigned int frameNum{0};
	// Anmount of time the current frame has been displayed
	float frameTime{0};
	// The FPS the animation is running at (24FPS by default)
	float animFPS{ 24.0f };

public:
	void Initialize(AnimData _animData, unsigned int _startingAnimNum);
	void UpdateAnim(float _deltaTime);
	void ChangeAnim(unsigned int _num);
};