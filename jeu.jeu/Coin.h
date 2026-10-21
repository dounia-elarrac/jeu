#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity {
private:
    float bobOffset;
    sf::Texture coinTexture;

public:
    Coin();
    Coin(float x, float y);
    ~Coin();

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    void loadTexture();
};

#endif