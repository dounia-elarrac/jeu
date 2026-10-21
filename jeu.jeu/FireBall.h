#ifndef FIREBALL_H
#define FIREBALL_H

#include "Entity.h"

class FireBall : public Entity {
private:
    sf::Vector2f direction;
    float lifeTime;

public:
    FireBall(sf::Vector2f pos, sf::Vector2f dir);
    ~FireBall();

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    bool isExpired() const { return lifeTime <= 0; }
};

#endif