#include "AnimatedSprite.h"

void AnimatedSprite::Initialize(AnimData _animData, unsigned int _startingAnimNum) {
		animData = _animData;
		animNum = _startingAnimNum;
		sf::Sprite::setPosition(0.f, 0.f);
		sf::Sprite::setTexture(*animData.spriteSheet_ptr);
		// Set animation to default animation.
		ChangeAnim(0);
}

void AnimatedSprite::UpdateAnim(float _deltaTime) {
	// Update how long the current frame has been displayed
	frameTime += _deltaTime;

	// This check determines if it's time to change to the next frame.
	if (frameTime > (1 / animFPS)) {
		// The number of frames to increment is the integral result of
		// frameTime / (1 / animFPS), which is frameTime * animFPS
		frameNum += static_cast<unsigned int>(frameTime * animFPS);
		// Check if we advanced past the last frame, and must wrap.
		if (frameNum >= animData.frameInfo[animNum].numFrames) {
			// The modulus (%) makes sure we wrap correctly.
			frameNum = frameNum % animData.frameInfo[animNum].numFrames;
		}

		// Update the active sprite with current frame.
		sf::Sprite::setTextureRect(sf::IntRect(
			animData.frameInfo[animNum].animOffset.left 
				+ animData.frameInfo[animNum].animOffset.width * frameNum,
			animData.frameInfo[animNum].animOffset.top,
			animData.frameInfo[animNum].animOffset.width,
			animData.frameInfo[animNum].animOffset.height));

		// the modulus (%) makes sure we wrap FPS correctly. 
		frameTime = std::fmod(frameTime, 1 / animFPS);
	}
}

void AnimatedSprite::ChangeAnim(unsigned int _num) {
	if (_num > animData.numOfAnimatons)
		throw std::exception("Animation number out of range.");
	animNum = _num;
	// The active animation is now at frame 0 and 0.0f time
	frameNum = 0;
	frameTime = 0.0f;

	// Set active sprite, which is just the starting frame.
	sf::Sprite::setTextureRect(sf::IntRect(
		animData.frameInfo[animNum].animOffset.left,
		animData.frameInfo[animNum].animOffset.top,
		animData.frameInfo[animNum].animOffset.width,
		animData.frameInfo[animNum].animOffset.height));
}

void AnimatedSprite::setDrawOrder(int value) {
	drawOrder = value;
}
