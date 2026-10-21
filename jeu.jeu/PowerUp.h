#ifndef POWERUP_H
#define POWERUP_H

#include "Entity.h"

enum class PowerUpType {
    GROWTH,
    SPEED,
    HEALTH
};

class PowerUp : public Entity {
private:
    PowerUpType type;
    float bobOffset;

    // Textures pour chaque type
    sf::Texture growthTexture;
    sf::Texture speedTexture;
    sf::Texture healthTexture;

public:
    PowerUp();
    PowerUp(float x, float y, PowerUpType t);
    ~PowerUp();

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    void loadTextures();

    PowerUpType getType() const { return type; }
};

#endif