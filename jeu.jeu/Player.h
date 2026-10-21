#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

enum class PlayerState {
    IDLE,
    WALK,
    RUN,
    JUMP,
    FALL,
    HURT,
    DEAD
};

class Player : public Entity {
private:
    
    PlayerState currentState;
    PlayerState previousState;

    bool isGrounded;
    bool canJump;
    bool canDoubleJump;
    bool isAlive;
    bool isBig;
    bool hasSpeedBoost;
    bool facingLeft;

    float speed;
    float normalSpeed;
    float boostedSpeed;
    float jumpForce;
    float gravity;

    int maxHearts;
    int currentHearts;
    int score;
    int coins;

    float invincibilityTimer;
    float speedBoostTimer;
    float hurtFlashTimer;

    
    std::unordered_map<PlayerState, std::vector<sf::Texture>> animations;
    std::unordered_map<PlayerState, float> animationSpeeds;

    int currentFrame;
    float animationTimer;
    PlayerState lastNonDeadState;

    // === Sound Manager ===
    SoundManager* soundManager;

    void loadAnimations();
    void updateAnimation(float deltaTime);
    void setState(PlayerState newState);
    void updateFlipped();

public:
    Player();
    ~Player();

    void handleInput();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void jump();
    void doubleJump();
    void takeDamage(int damage);
    void heal(int amount);
    void addCoin();
    void addScore(int s);
    void grow();
    void shrink();
    void activateSpeedBoost(float duration);
    void die();
    void respawn();

    // === دوال قتل العدو بالقفز ===
    bool isFallingOnEnemy(Entity* enemy);
    void onEnemyStomp(Entity* enemy);

    // === Sound Manager ===
    void setSoundManager(SoundManager* sm) { soundManager = sm; }

    // Getters
    int getCurrentHearts() const { return currentHearts; }
    int getScore() const { return score; }
    int getCoins() const { return coins; }
    bool getIsAlive() const { return isAlive; }
    bool getIsGrounded() const { return isGrounded; }
    bool getIsBig() const { return isBig; }
    float getVelocityY() const { return velocity.y; }

    void setGrounded(bool g) { isGrounded = g; }
    void setVelocityY(float vy) { velocity.y = vy; }
};

#endif