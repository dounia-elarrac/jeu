#include "Platform.h"
#include "Config.h"

Platform::Platform() : Entity() {
    name = "Platform";
    isBouncy = false;
    isGround = false;
    shape.setSize(sf::Vector2f(80, 25));
    shape.setFillColor(sf::Color(50, 200, 50));
    shape.setOutlineColor(sf::Color(30, 150, 30));
    shape.setOutlineThickness(2);
}

Platform::Platform(float x, float y, float w, float h, bool bouncy, bool ground) : Entity(x, y, w, h) {
    name = "Platform";
    isBouncy = bouncy;
    isGround = ground;

    // Créer la forme de la plateforme
    shape.setSize(sf::Vector2f(w, h));
    shape.setPosition(x, y);
    shape.setOrigin(0, 0);

    if (isGround) {
        
        shape.setFillColor(sf::Color(0, 0, 0, 0));
        shape.setOutlineColor(sf::Color(0, 0, 0, 0));
        shape.setOutlineThickness(0);
    }
    else if (isBouncy) {
        
        shape.setFillColor(sf::Color(255, 215, 0));      
        shape.setOutlineColor(sf::Color(200, 150, 0));   
        shape.setOutlineThickness(3);
    }
    else {
        shape.setFillColor(sf::Color(50, 200, 50));      
        shape.setOutlineColor(sf::Color(30, 150, 30));   
        shape.setOutlineThickness(2);
    }
}

Platform::~Platform() {}

void Platform::loadTextures() {
    
}

void Platform::update(float deltaTime) {}

void Platform::render(sf::RenderWindow& window) {
    if (active && !isGround) {
        if (!isBouncy) {
            
            window.draw(shape);

            sf::RectangleShape topLine(sf::Vector2f(shape.getSize().x, 5));
            topLine.setPosition(shape.getPosition().x, shape.getPosition().y);
            topLine.setFillColor(sf::Color(100, 255, 100));
            window.draw(topLine);

            
            sf::RectangleShape bottomLine(sf::Vector2f(shape.getSize().x, 3));
            bottomLine.setPosition(shape.getPosition().x, shape.getPosition().y + shape.getSize().y - 3);
            bottomLine.setFillColor(sf::Color(30, 120, 30));
            window.draw(bottomLine);
        }
        else {
            
            window.draw(shape);

            
            sf::RectangleShape topLine(sf::Vector2f(shape.getSize().x, 5));
            topLine.setPosition(shape.getPosition().x, shape.getPosition().y);
            topLine.setFillColor(sf::Color(255, 240, 100));
            window.draw(topLine);

            
            sf::CircleShape dot(3);
            dot.setFillColor(sf::Color(255, 100, 0));
            dot.setPosition(shape.getPosition().x + 10, shape.getPosition().y + shape.getSize().y / 2 - 3);
            window.draw(dot);

            sf::CircleShape dot2(3);
            dot2.setFillColor(sf::Color(255, 100, 0));
            dot2.setPosition(shape.getPosition().x + shape.getSize().x - 20, shape.getPosition().y + shape.getSize().y / 2 - 3);
            window.draw(dot2);
        }
    }
}