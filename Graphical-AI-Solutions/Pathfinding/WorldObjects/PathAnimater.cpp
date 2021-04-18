#include "PathAnimater.h"

void PathAnimater::initialize(const std::string& tilesetPath, std::vector<TileFrame> pathAnimation) {
	searchAnimation_ = pathAnimation;
	// Create empty map
	std::vector<int> emptyMap(MAP_WIDTH * MAP_HEIGHT, EMPTY_TILE_INDEX);
	MapData mapData = {sf::Vector2u(TILESIZE, TILESIZE), emptyMap, MAP_WIDTH, MAP_HEIGHT};
	tileMap_.initialize(TILESET_TEXTURE_FILE, mapData);
}

void PathAnimater::update(float deltaTime) {
	frameTime_ += deltaTime;

	switch (state_)
	{
	case DRAWING_SEARCH:
		// Check if next frame should be drawn
		if (frameTime_ > (1 / animFps_)) {
			frameNum_++;
			// If end of search has been drawn, change state and start drawing path
			if (frameNum_ == searchAnimation_.size()) {
				state_ = DONE;
				frameTime_ = 0;
				frameNum_ = 0;
				return;
			}
			// Change map in tilemap to "search" or "visited" texture
			tileMap_.SetTileData(searchAnimation_[frameNum_].tileIndex_, searchAnimation_[frameNum_].tileType_);
			// Rest frametime making sure it wraps correctly
			frameTime_ = std::fmod(frameTime_, 1 / animFps_);
		}
		break;
	case DRAWING_PATH:
		break;
	case DONE:
		break;
	default:
		break;
	}

	
}

void PathAnimater::draw(sf::RenderWindow& window) {
	window.draw(tileMap_);
}

PathAnimater::PathAnimater()
: tileMap_(TileMap())
, searchAnimation_(std::vector<TileFrame>())
, frameNum_(0)
, frameTime_(0)
, animFps_(FRAME_RATE)
, state_(DRAWING_SEARCH) {}
