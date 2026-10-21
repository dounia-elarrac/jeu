#include "PowerUp.h"
#include "Config.h"
#include <cmath>

PowerUp::PowerUp() : Entity() {
    name = "PowerUp";
    type = PowerUpType::GROWTH;
    bobOffset = 0;
    points = GameConstants::POWERUP_POINTS_GROWTH;
    loadTextures();
    sprite.setTexture(growthTexture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(position);
}

PowerUp::PowerUp(float x, float y, PowerUpType t) : Entity(x, y) {
    name = "PowerUp";
    type = t;
    bobOffset = 0;
    loadTextures();

    switch (type) {
    case PowerUpType::GROWTH:
        sprite.setTexture(growthTexture);
        points = GameConstants::POWERUP_POINTS_GROWTH;
        break;
    case PowerUpType::SPEED:
        sprite.setTexture(speedTexture);
        points = GameConstants::POWERUP_POINTS_SPEED;
        break;
    case PowerUpType::HEALTH:
        sprite.setTexture(healthTexture);
        points = GameConstants::POWERUP_POINTS_HEALTH;
        break;
    }

    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(x, y);
}

PowerUp::~PowerUp() {}

void PowerUp::loadTextures() {
    growthTexture.loadFromFile("textures/powerup_growth.png");
    speedTexture.loadFromFile("textures/powerup_speed.png");
    healthTexture.loadFromFile("textures/powerup_health.png");
}

void PowerUp::update(float deltaTime) {
    if (!active) return;
    bobOffset += 3 * deltaTime;
    float bobY = sin(bobOffset) * 5;
    sprite.setPosition(position.x, position.y + bobY);
}

void PowerUp::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

sf::FloatRect PowerUp::getBounds() const {
    return sprite.getGlobalBounds();
}