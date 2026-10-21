#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

class Platform : public Entity {
private:
    bool isBouncy;
    bool isGround;
    sf::RectangleShape shape;  
    sf::Texture normalTexture;
    sf::Texture bouncyTexture;

    void loadTextures();

public:
    Platform();
    Platform(float x, float y, float w, float h, bool bouncy = false, bool ground = false);
    ~Platform();

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    bool isBouncyPlatform() const { return isBouncy; }
    bool isGroundPlatform() const { return isGround; }

    
    sf::FloatRect getBounds() const override { return shape.getGlobalBounds(); }
};

#endif