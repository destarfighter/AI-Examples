#pragma once
#include <SFML/Graphics.hpp>

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

struct AnimFrameData {
	// the index of the first frame of an animation
	int startFrame;
	// the total number of frames for said animation
	int numFrames;
};

struct AnimData {
	// ImageFile with all the animations
	sf::Texture spriteSheet;
	// the frame data for all the different animations
	AnimFrameData* frameInfo;
};