#include "FireBall.h"
#include "Config.h"

FireBall::FireBall(sf::Vector2f pos, sf::Vector2f dir) : Entity(pos.x, pos.y) {
    name = "FireBall";
    direction = dir;
    lifeTime = 3.0f;

   
    if (direction.x == 0 && direction.y == 0) {
        direction.x = -GameConstants::FIREBALL_SPEED;
    }

    loadTexture("textures/fireball.png");
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(pos);
}

FireBall::~FireBall() {}

void FireBall::update(float deltaTime) {
    if (!active) return;

    lifeTime -= deltaTime;
    if (lifeTime <= 0) {
        active = false;
        return;
    }

    position.x += direction.x * deltaTime;
    position.y += direction.y * deltaTime;
    sprite.setPosition(position);
}

void FireBall::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}