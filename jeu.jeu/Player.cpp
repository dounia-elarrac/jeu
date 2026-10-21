#include "Player.h"
#include "Config.h"
#include <iostream>
#include <cmath>

Player::Player() : Entity(GameConstants::PLAYER_START_X, GameConstants::PLAYER_START_Y) {
    name = "Player";

    velocity = sf::Vector2f(0, 0);
    isGrounded = true;
    canJump = true;
    canDoubleJump = true;
    isAlive = true;
    isBig = false;
    hasSpeedBoost = false;
    facingLeft = false;

    normalSpeed = GameConstants::PLAYER_SPEED_NORMAL;
    boostedSpeed = GameConstants::PLAYER_SPEED_BOOSTED;
    speed = normalSpeed;
    jumpForce = GameConstants::PLAYER_JUMP_FORCE;
    gravity = GameConstants::PLAYER_GRAVITY;

    maxHearts = GameConstants::PLAYER_MAX_HEARTS;
    currentHearts = GameConstants::PLAYER_MAX_HEARTS;
    score = 0;
    coins = 0;

    invincibilityTimer = 0;
    speedBoostTimer = 0;
    hurtFlashTimer = 0;

    currentState = PlayerState::IDLE;
    previousState = PlayerState::IDLE;
    currentFrame = 0;
    animationTimer = 0;
    lastNonDeadState = PlayerState::IDLE;

    soundManager = nullptr;

    loadAnimations();

    sprite.setScale(2.0f, 2.0f);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

Player::~Player() {}

void Player::loadAnimations() {
    std::string basePath = "textures/";

    // IDLE
    std::vector<sf::Texture> idleFrames;
    sf::Texture idleTex;
    if (idleTex.loadFromFile(basePath + "idle.png")) {
        idleFrames.push_back(idleTex);
    }
    animations[PlayerState::IDLE] = idleFrames;
    animationSpeeds[PlayerState::IDLE] = 0.1f;

    // WALK
    std::vector<sf::Texture> walkFrames;
    for (int i = 1; i <= 8; i++) {
        sf::Texture tex;
        if (tex.loadFromFile(basePath + "walk" + std::to_string(i) + ".png")) {
            walkFrames.push_back(tex);
        }
    }
    animations[PlayerState::WALK] = walkFrames;
    animationSpeeds[PlayerState::WALK] = 0.08f;

    // RUN
    std::vector<sf::Texture> runFrames;
    for (int i = 1; i <= 8; i++) {
        sf::Texture tex;
        if (tex.loadFromFile(basePath + "run" + std::to_string(i) + ".png")) {
            runFrames.push_back(tex);
        }
    }
    animations[PlayerState::RUN] = runFrames;
    animationSpeeds[PlayerState::RUN] = 0.05f;

    // JUMP
    std::vector<sf::Texture> jumpFrames;
    for (int i = 1; i <= 8; i++) {
        sf::Texture tex;
        if (tex.loadFromFile(basePath + "jump" + std::to_string(i) + ".png")) {
            jumpFrames.push_back(tex);
        }
    }
    animations[PlayerState::JUMP] = jumpFrames;
    animationSpeeds[PlayerState::JUMP] = 0.06f;

    // FALL
    std::vector<sf::Texture> fallFrames;
    for (int i = 1; i <= 2; i++) {
        sf::Texture tex;
        if (tex.loadFromFile(basePath + "fall" + std::to_string(i) + ".png")) {
            fallFrames.push_back(tex);
        }
    }
    animations[PlayerState::FALL] = fallFrames;
    animationSpeeds[PlayerState::FALL] = 0.1f;

    // HURT
    std::vector<sf::Texture> hurtFrames;
    for (int i = 1; i <= 3; i++) {
        sf::Texture tex;
        if (tex.loadFromFile(basePath + "hurt" + std::to_string(i) + ".png")) {
            hurtFrames.push_back(tex);
        }
    }
    animations[PlayerState::HURT] = hurtFrames;
    animationSpeeds[PlayerState::HURT] = 0.1f;

    // DEAD
    std::vector<sf::Texture> deadFrames;
    for (int i = 1; i <= 3; i++) {
        sf::Texture tex;
        if (tex.loadFromFile(basePath + "dead" + std::to_string(i) + ".png")) {
            deadFrames.push_back(tex);
        }
    }
    animations[PlayerState::DEAD] = deadFrames;
    animationSpeeds[PlayerState::DEAD] = 0.15f;

    if (!animations[PlayerState::IDLE].empty()) {
        sprite.setTexture(animations[PlayerState::IDLE][0]);
    }
}

void Player::updateFlipped() {
    if (facingLeft) {
        sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y);
    }
    else {
        sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y);
    }
}

void Player::setState(PlayerState newState) {
    if (currentState == newState) return;

    previousState = currentState;
    currentState = newState;
    currentFrame = 0;
    animationTimer = 0;

    if (!animations[currentState].empty()) {
        sprite.setTexture(animations[currentState][0]);
    }
}

void Player::updateAnimation(float deltaTime) {
    auto& frames = animations[currentState];
    if (frames.empty()) return;

    float speed = animationSpeeds[currentState];
    animationTimer += deltaTime;

    if (animationTimer >= speed) {
        animationTimer = 0;
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTexture(frames[currentFrame]);
    }
}

void Player::handleInput() {
    if (!isAlive) return;

    float moveX = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveX = speed;
        facingLeft = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveX = -speed;
        facingLeft = true;
    }

    velocity.x = moveX;
    updateFlipped();

    static bool wasJumpKeyPressed = false;
    bool isJumpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (isJumpKeyPressed && !wasJumpKeyPressed) {
        if (isGrounded) {
            jump();
        }
        else if (!isGrounded && canDoubleJump) {
            doubleJump();
        }
    }
    wasJumpKeyPressed = isJumpKeyPressed;
}

void Player::jump() {
    if (isGrounded) {
        velocity.y = jumpForce;
        isGrounded = false;
        canJump = false;
        canDoubleJump = true;
        setState(PlayerState::JUMP);

        
        if (soundManager != nullptr) {
            soundManager->playSound("jump");
            std::cout << "🔊 Jump sound played!" << std::endl;
        }
    }
}

void Player::doubleJump() {
    if (!isGrounded && canDoubleJump) {
        velocity.y = jumpForce * 0.8f;
        canDoubleJump = false;
        setState(PlayerState::JUMP);

        
        if (soundManager != nullptr) {
            soundManager->playSound("jump");
        }
    }
}

void Player::update(float deltaTime) {
    if (!isAlive) {
        setState(PlayerState::DEAD);
        updateAnimation(deltaTime);
        sprite.setPosition(position);
        return;
    }

    
    if (invincibilityTimer > 0) invincibilityTimer -= deltaTime;
    if (speedBoostTimer > 0) {
        speedBoostTimer -= deltaTime;
        if (speedBoostTimer <= 0) {
            hasSpeedBoost = false;
            speed = normalSpeed;
        }
    }

    
    velocity.y += gravity * deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    
    if (position.x < 50) position.x = 50;
    if (position.x > GameConstants::WORLD_WIDTH - 50) position.x = GameConstants::WORLD_WIDTH - 50;
    if (position.y < 50) position.y = 50;
    if (position.y > GameConstants::WORLD_HEIGHT - 50) position.y = GameConstants::WORLD_HEIGHT - 50;

    
    if (position.y >= GameConstants::GROUND_LEVEL && !isGrounded) {
        position.y = GameConstants::GROUND_LEVEL;
        velocity.y = 0;
        isGrounded = true;
        canJump = true;
        canDoubleJump = true;
    }

    
    if (currentState != PlayerState::HURT) {
        if (isGrounded) {
            if (std::abs(velocity.x) > 200) {
                if (currentState != PlayerState::RUN)
                    setState(PlayerState::RUN);
            }
            else if (std::abs(velocity.x) > 10) {
                if (currentState != PlayerState::WALK)
                    setState(PlayerState::WALK);
            }
            else {
                if (currentState != PlayerState::IDLE)
                    setState(PlayerState::IDLE);
            }
        }
        else {
            if (velocity.y < 0) {
                if (currentState != PlayerState::JUMP)
                    setState(PlayerState::JUMP);
            }
            else if (velocity.y > 0) {
                if (currentState != PlayerState::FALL)
                    setState(PlayerState::FALL);
            }
        }
    }

    updateAnimation(deltaTime);

    if (isBig) {
        sprite.setScale(3.0f, 3.0f);
    }
    else {
        sprite.setScale(2.0f, 2.0f);
    }
    updateFlipped();

    sprite.setPosition(position);
}

void Player::render(sf::RenderWindow& window) {
    if (isAlive || currentState == PlayerState::DEAD) {
        window.draw(sprite);
    }
}

void Player::takeDamage(int damage) {
    if (!isAlive) return;
    if (invincibilityTimer > 0) return;

    currentHearts--;
    invincibilityTimer = GameConstants::INVINCIBILITY_DURATION;
    hurtFlashTimer = 0.3f;
    setState(PlayerState::HURT);

    
    if (soundManager != nullptr) {
        soundManager->playSound("hit");
    }

    if (isBig) shrink();
    if (currentHearts <= 0) die();
}

void Player::heal(int amount) {
    currentHearts += amount;
    if (currentHearts > maxHearts) currentHearts = maxHearts;
}

void Player::addCoin() {
    coins++;
    score += GameConstants::COIN_POINTS;

    
    if (soundManager != nullptr) {
        soundManager->playSound("coin");
    }

    if (coins % GameConstants::COINS_FOR_EXTRA_LIFE == 0 && currentHearts < maxHearts) {
        currentHearts++;
    }
}

void Player::addScore(int s) {
    score += s;
}

void Player::grow() {
    if (!isBig) {
        isBig = true;
        sprite.setScale(3.0f, 3.0f);
        updateFlipped();

        
        if (soundManager != nullptr) {
            soundManager->playSound("powerup");
        }
    }
}

void Player::shrink() {
    if (isBig) {
        isBig = false;
        sprite.setScale(2.0f, 2.0f);
        updateFlipped();
    }
}

void Player::activateSpeedBoost(float duration) {
    hasSpeedBoost = true;
    speed = boostedSpeed;
    speedBoostTimer = duration;

    if (soundManager != nullptr) {
        soundManager->playSound("powerup");
    }
}

void Player::die() {
    isAlive = false;
    setState(PlayerState::DEAD);
}

void Player::respawn() {
    position = sf::Vector2f(GameConstants::PLAYER_START_X, GameConstants::PLAYER_START_Y);
    velocity = sf::Vector2f(0, 0);
    isAlive = true;
    isBig = false;
    invincibilityTimer = 2.0f;
    setState(PlayerState::IDLE);
}


bool Player::isFallingOnEnemy(Entity* enemy) {
    if (!enemy || !enemy->isActive()) return false;
    if (velocity.y <= 0) return false;
    if (!isAlive) return false;
    if (invincibilityTimer > 0) return false;

    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    sf::FloatRect enemyBounds = enemy->getBounds();

    float playerBottom = playerBounds.top + playerBounds.height;
    float enemyTop = enemyBounds.top;

    return (playerBottom >= enemyTop - 5.0f &&
        playerBottom <= enemyTop + 25.0f &&
        playerBounds.intersects(enemyBounds));
}

void Player::onEnemyStomp(Entity* enemy) {
    if (!enemy || !enemy->isActive()) return;

    enemy->setActive(false);
    addScore(200);
    velocity.y = -400.0f;
    isGrounded = false;
    setState(PlayerState::JUMP);

    
    if (soundManager != nullptr) {
        soundManager->playSound("stomp");
    }
}