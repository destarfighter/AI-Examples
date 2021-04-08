#include "AnimatedSprite.h"

void AnimatedSprite::initialize(AnimData animData, unsigned int startingAnimNum) {
		animData_ = animData;
		animNum_ = startingAnimNum;
		sf::Sprite::setPosition(0.f, 0.f);
		sf::Sprite::setTexture(*animData_.spriteSheet_ptr_);
		// Set animation to default animation.
		changeAnim(0);
}

void AnimatedSprite::update(float deltaTime) {
	// Update how long the current frame has been displayed
	frameTime_ += deltaTime;
	// This check determines if it's time to change to the next frame.
	if (frameTime_ > (1 / animFPS_)) {
		// The number of frames to increment is the integral result of
		// FrameTime / (1 / animFPS), which is frameTime * animFPS
		frameNum_ += frameTime_ * animFPS_;
		// Check if we advanced past the last frame, and must wrap.
		if (frameNum_ >= animData_.frameInfo_[animNum_].numFrames_) {
			// The modulus (%) makes sure we wrap correctly.
			frameNum_ = frameNum_ % animData_.frameInfo_[animNum_].numFrames_;
		}

		// Update the active sprite with current frame.
		sf::Sprite::setTextureRect(sf::IntRect(
			animData_.frameInfo_[animNum_].animOffset_.left 
				+ animData_.frameInfo_[animNum_].animOffset_.width * frameNum_,
			animData_.frameInfo_[animNum_].animOffset_.top,
			animData_.frameInfo_[animNum_].animOffset_.width,
			animData_.frameInfo_[animNum_].animOffset_.height));

		// The modulus (%) makes sure we wrap FPS correctly. 
		frameTime_ = std::fmod(frameTime_, 1 / animFPS_);
	}
}

void AnimatedSprite::changeAnim(unsigned int num) {
	if (num > animData_.numOfAnimatons_)
		throw std::exception("Animation number out of range.");
	animNum_ = num;
	// The active animation is now at frame 0 and 0.0f time
	frameNum_ = 0;
	frameTime_ = 0.0f;

	// Set active sprite, which is just the starting frame.
	sf::Sprite::setTextureRect(sf::IntRect(
		animData_.frameInfo_[animNum_].animOffset_.left,
		animData_.frameInfo_[animNum_].animOffset_.top,
		animData_.frameInfo_[animNum_].animOffset_.width,
		animData_.frameInfo_[animNum_].animOffset_.height));
}