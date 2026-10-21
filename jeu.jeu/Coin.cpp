#include "Coin.h"
#include "Config.h"
#include <cmath>

Coin::Coin() : Entity() {
    name = "Coin";
    points = GameConstants::COIN_POINTS;
    bobOffset = 0;
    loadTexture();
    sprite.setTexture(coinTexture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setOrigin(12, 12);
}

Coin::Coin(float x, float y) : Entity(x, y) {
    name = "Coin";
    points = GameConstants::COIN_POINTS;
    bobOffset = 0;
    loadTexture();
    sprite.setTexture(coinTexture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setOrigin(12, 12);
    sprite.setPosition(x, y);
}

Coin::~Coin() {}

void Coin::loadTexture() {
    coinTexture.loadFromFile("textures/coin.png");
}

void Coin::update(float deltaTime) {
    if (!active) return;
    bobOffset += 5 * deltaTime;
    float bobY = sin(bobOffset) * 5;
    sprite.setPosition(position.x, position.y + bobY);
}

void Coin::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

sf::FloatRect Coin::getBounds() const {
    return sprite.getGlobalBounds();
}