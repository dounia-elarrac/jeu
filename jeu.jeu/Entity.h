#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

class Entity {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool active;
    bool flipped;
    int points;
    std::string name;

public:
    // Constructeurs
    Entity();
    Entity(float x, float y);
    Entity(float x, float y, float w, float h);
    virtual ~Entity();

    // Fonctions virtuelles
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void onCollision(Entity* other);
    virtual sf::FloatRect getBounds() const;
    virtual void loadTexture(const std::string& path);

    // Getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const { return velocity; }
    bool isActive() const;
    int getPoints() const { return points; }
    std::string getName() const { return name; }
    sf::Sprite& getSprite() { return sprite; }

    // Setters
    void setActive(bool a);
    void setPosition(float x, float y);
    void setVelocityY(float vy) { velocity.y = vy; }
    void setVelocityX(float vx) { velocity.x = vx; }
    void setVelocity(float vx, float vy) { velocity.x = vx; velocity.y = vy; }
    void setFlipped(bool flip);
    void setPoints(int p) { points = p; }
    void setName(const std::string& n) { name = n; }
    void setScale(float x, float y) { sprite.setScale(x, y); }
    void setColor(sf::Color color) { sprite.setColor(color); }
};

#endif