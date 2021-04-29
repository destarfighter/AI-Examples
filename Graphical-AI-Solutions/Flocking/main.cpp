#include <SFML/Graphics.hpp>
#include "WorldState.hpp"
#include "WorldStateLocator.h"
#include "Objects/Map.h"
#include "config.h"
#include "Objects/Animal.h"
#include "AI/AnimalStates.h"

std::shared_ptr<sf::Texture> loadTexture(std::string texturePath) {
    auto texture_ptr = std::make_shared<sf::Texture>();
    if (!texture_ptr->loadFromFile(texturePath))
        throw std::exception("Failed to load image from file.");
    texture_ptr->setRepeated(false);
    texture_ptr->setSmooth(true);
    return texture_ptr;
}

std::shared_ptr<Map> createMap() {

    std::vector<int> tileData(MAP_HEIGHT * MAP_WIDTH, 0);

    for (unsigned int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i) {
        tileData[i] = rand() % NUMBER_OF_GRASS_TILES;
    }

    MapData mapData { sf::Vector2u(TILESIZE, TILESIZE), tileData, MAP_WIDTH, MAP_HEIGHT };
    auto newMap_ptr = std::make_shared<Map>(Map());
    newMap_ptr->initialize(TILESET_TEXTURE_FILE, mapData);

    return newMap_ptr;
}

std::shared_ptr<Animal> createAnimal(AnimData animData, AnimalState* startState, std::string name, sf::Vector2u spawnArea, int numberOfAnimals) {

    auto newAnimal_ptr = std::make_shared<Animal>(*(new Animal));

    // Set Random position withing spawn area
    int spawnOffset = numberOfAnimals * TILESIZE;

    sf::Vector2f startPosition(spawnArea.x + ((rand() % spawnOffset) - (spawnOffset / 2)),
        spawnArea.y + (rand() % spawnOffset) - (spawnOffset / 2));

    // TODO: clamp position to be within screen boundries

    // Set Random orientation
    float startRotation = rand() % 360;

    newAnimal_ptr->initialize(animData, 0, startPosition, startState, startRotation);
    return newAnimal_ptr;
}

std::shared_ptr<Animal> createSheep(std::shared_ptr<sf::Texture> texture, int sheepIndex) {
    auto frameInfo = std::vector<AnimFrameData>();
    frameInfo.push_back(SHEEP_IDLE_ANIMATION);
    frameInfo.push_back(SHEEP_STRETCHING_ANIMATION);
    frameInfo.push_back(SHEEP_WALKING_ANIMATION);
    frameInfo.push_back(SHEEP_EATING_ANIMATION);
    frameInfo.push_back(SHEEP_DYING_ANIMATION);
    AnimData animData{ texture, frameInfo, frameInfo.size() };

    return createAnimal(animData, new AnimalState(nullptr, nullptr), SHEEP_NAME, SHEEP_SPAWN_AREA, NUMBER_OF_SHEEP); // TODO: Add startState for sheep
}

std::shared_ptr<Animal> createPredator(std::shared_ptr<sf::Texture> texture, int predatorIndex) {
    auto frameInfo = std::vector<AnimFrameData>();
    frameInfo.push_back(PREDATOR_IDLE_ANIMATION);
    frameInfo.push_back(PREDATOR_WALKING_ANIMATION);
    frameInfo.push_back(PREDATOR_RUNNING_ANIMATION);
    frameInfo.push_back(PREDATOR_EATING_ANIMATION);
    AnimData animData{ texture, frameInfo, frameInfo.size()};
    
    return createAnimal(animData, new AnimalState(nullptr, nullptr), PREDATOR_NAME, PREDATOR_SPAWN_AREA, NUMBER_OF_PREDATORS); // TODO: Add startState for predator
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flocking");
   
    // Create provider for worlsState
    WorldStateProvider* worldState = new WorldStateProvider();
    WorldStateLocator::provide(worldState);

    // Create Map
    auto map = createMap();
    worldState->addNewObject({ MAP_NAME, -1 }, map, true, false);

    srand(time(NULL));

    // Create Sheep
    auto sheepTexture_ptr = loadTexture(SHEEP_SPRITESHEET_FILE);
    for (unsigned int i = 0; i < NUMBER_OF_SHEEP; ++i) {
        worldState->addNewObject({ SHEEP_NAME + std::to_string(i), 5 }, createSheep(sheepTexture_ptr, i), true, true);
    }
    
    // Create Predators
    auto predatorTexture_ptr = loadTexture(PREDATOR_SPRITESHEET_FILE);
    for (unsigned int i = 0; i < NUMBER_OF_PREDATORS; ++i) {
        worldState->addNewObject({ PREDATOR_NAME + std::to_string(i), 10 }, createPredator(predatorTexture_ptr, i), true, true);
    }

    // Create clock to keep track of frame deltas.
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Restart clock and get the time passed since last frame.
        sf::Time deltaTime = clock.restart();
        window.clear();

        // Update Objects
        for (auto obj_ptr : worldState->getUpdatables()) {
            obj_ptr.second->update(deltaTime.asSeconds());
        }

        // Draw Objects
        for (auto obj_ptr : worldState->getDrawables()) {
            obj_ptr.second->draw(window);
        }

        window.display();
    }

    return 0;
}