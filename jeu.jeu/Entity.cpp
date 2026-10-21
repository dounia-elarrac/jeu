#include "Entity.h"

// Constructeur par défaut
Entity::Entity() {
    position = sf::Vector2f(0, 0);
    velocity = sf::Vector2f(0, 0);
    active = true;
    flipped = false;
    points = 0;
    name = "Entity";
}

// Constructeur avec position
Entity::Entity(float x, float y) {
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0, 0);
    active = true;
    flipped = false;
    points = 0;
    name = "Entity";
    sprite.setPosition(position);
}

// Constructeur avec position et taille
Entity::Entity(float x, float y, float w, float h) {
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0, 0);
    active = true;
    flipped = false;
    points = 0;
    name = "Entity";
    sprite.setPosition(position);
}

// Destructeur
Entity::~Entity() {}

// Rendu de l'entité
void Entity::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

// Chargement d'une texture
void Entity::loadTexture(const std::string& path) {
    if (texture.loadFromFile(path)) {
        sprite.setTexture(texture);
    }
}

// Flip de l'image (retournement horizontal)
void Entity::setFlipped(bool flip) {
    flipped = flip;
    if (flipped) {
        sprite.setScale(-1.0f, 1.0f);
    }
    else {
        sprite.setScale(1.0f, 1.0f);
    }
}

// Obtention des limites de l'entité (pour collisions)
sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}

// Gestion de collision (à override)
void Entity::onCollision(Entity* other) {}

// Getters
sf::Vector2f Entity::getPosition() const {
    return position;
}

bool Entity::isActive() const {
    return active;
}

// Setters
void Entity::setActive(bool a) {
    active = a;
}

void Entity::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}