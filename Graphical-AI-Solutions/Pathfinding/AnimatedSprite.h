#pragma once
#include <SFML/Graphics.hpp>

struct AnimFrameData {
	// the offset of the first frame and the size of the images of an animation
	sf::Rect<int> animOffset;
	// the total number of frames for said animation
	unsigned int numFrames;
};

struct AnimData {
	// ImageFile with all the animations
	std::shared_ptr<sf::Texture> spriteSheet_ptr;
	// the frame data for all the different animations
	std::vector<AnimFrameData> frameInfo; // make into vector? 
	// the number of different animations
	unsigned int numOfAnimatons;
};

class AnimatedSprite : public sf::Sprite {

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
	// the draw order of the animation in the render-pipeline. (0 by default)
	int drawOrder{ 0 };

public:
	void Initialize(AnimData _animData, unsigned int _startingAnimNum);
	void UpdateAnim(float _deltaTime);
	void ChangeAnim(unsigned int _num);
	void setDrawOrder(int value);
};