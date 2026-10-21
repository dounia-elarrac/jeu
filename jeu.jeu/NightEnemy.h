#ifndef NIGHT_ENEMY_H
#define NIGHT_ENEMY_H

#include "Enemy.h"
#include "FireBall.h"
#include "Config.h"
#include <cmath>
#include <vector>


class Bat : public Enemy {
private:
    float amplitude;
    float frequency;
    float angle;
    float startY;
    std::vector<sf::Texture> flyFrames;
    int currentFlyFrame;
    float flyAnimTimer;

    void loadFlyAnimations() {
        std::string basePath = "textures/";
        for (int i = 1; i <= 9; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "fly" + std::to_string(i) + ".png")) {
                flyFrames.push_back(tex);
            }
        }
        if (!flyFrames.empty()) {
            sprite.setTexture(flyFrames[0]);
        }
    }

public:
    Bat(float x, float y) : Enemy(x, y, true) {
        name = "Bat";
        points = 150;
        damage = 15;
        speed = 100.0f;
        amplitude = 50.0f;
        frequency = 3.0f;
        angle = 0;
        startY = y;
        currentFlyFrame = 0;
        flyAnimTimer = 0;
        loadFlyAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;
        angle += frequency * deltaTime;
        position.y = startY + sin(angle) * amplitude;
        position.x -= speed * deltaTime;

        // Animation
        flyAnimTimer += deltaTime;
        if (flyAnimTimer >= 0.1f && !flyFrames.empty()) {
            flyAnimTimer = 0;
            currentFlyFrame = (currentFlyFrame + 1) % flyFrames.size();
            sprite.setTexture(flyFrames[currentFlyFrame]);
        }

        sprite.setPosition(position);
    }
};

class Ghost : public Enemy {
private:
    std::vector<sf::Texture> walkFrames;
    int currentWalkFrame;
    float walkAnimTimer;

    void loadWalkAnimations() {
        std::string basePath = "textures/";
        for (int i = 1; i <= 5; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "walkG" + std::to_string(i) + ".png")) {
                walkFrames.push_back(tex);
            }
        }
        if (!walkFrames.empty()) {
            sprite.setTexture(walkFrames[0]);
        }
    }

public:
    Ghost(float x, float y) : Enemy(x, y, true) {
        name = "Ghost";
        points = 200;
        damage = 20;
        speed = 70.0f;
        currentWalkFrame = 0;
        walkAnimTimer = 0;
        loadWalkAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;
        position.x -= speed * deltaTime;

        // Animation
        walkAnimTimer += deltaTime;
        if (walkAnimTimer >= 0.12f && !walkFrames.empty()) {
            walkAnimTimer = 0;
            currentWalkFrame = (currentWalkFrame + 1) % walkFrames.size();
            sprite.setTexture(walkFrames[currentWalkFrame]);
        }

        sprite.setPosition(position);
    }
};

 
class Spider : public Enemy {
private:
    bool onWeb;
    float webLength;
    float descendSpeed;
    float startY;
    std::vector<sf::Texture> walkFrames;
    int currentWalkFrame;
    float walkAnimTimer;

    void loadWalkAnimations() {
        std::string basePath = "textures/";
        for (int i = 1; i <= 8; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "walkS" + std::to_string(i) + ".png")) {
                walkFrames.push_back(tex);
            }
        }
        if (!walkFrames.empty()) {
            sprite.setTexture(walkFrames[0]);
        }
    }

public:
    Spider(float x, float y) : Enemy(x, y, false) {
        name = "Spider";
        points = 180;
        damage = 25;
        speed = 50.0f;
        onWeb = true;
        webLength = 200.0f;
        descendSpeed = 80.0f;
        startY = y;
        currentWalkFrame = 0;
        walkAnimTimer = 0;
        loadWalkAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;

        if (onWeb && position.y < startY + webLength) {
            position.y += descendSpeed * deltaTime;
        }
        else {
            onWeb = false;
        }

        // Animation
        if (!onWeb) {
            walkAnimTimer += deltaTime;
            if (walkAnimTimer >= 0.1f && !walkFrames.empty()) {
                walkAnimTimer = 0;
                currentWalkFrame = (currentWalkFrame + 1) % walkFrames.size();
                sprite.setTexture(walkFrames[currentWalkFrame]);
            }
        }

        sprite.setPosition(position);
    }
};


class Zombie : public Enemy {
private:
    float jumpCooldown;
    bool isJumping;
    std::vector<sf::Texture> walkFrames;
    std::vector<sf::Texture> jumpFrames;
    int currentWalkFrame;
    int currentJumpFrame;
    float walkAnimTimer;
    float jumpAnimTimer;

    void loadAnimations() {
        std::string basePath = "textures/";

        // Walk animations (8)
        for (int i = 1; i <= 8; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "walkZ" + std::to_string(i) + ".png")) {
                walkFrames.push_back(tex);
            }
        }

        // Jump animations (8)
        for (int i = 1; i <= 8; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "jumpZ" + std::to_string(i) + ".png")) {
                jumpFrames.push_back(tex);
            }
        }

        if (!walkFrames.empty()) {
            sprite.setTexture(walkFrames[0]);
        }
    }

public:
    Zombie(float x, float y) : Enemy(x, y, false) {
        name = "Zombie";
        points = 250;
        damage = 30;
        speed = 40.0f;
        jumpCooldown = 0;
        isJumping = false;
        currentWalkFrame = 0;
        currentJumpFrame = 0;
        walkAnimTimer = 0;
        jumpAnimTimer = 0;
        loadAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;

        position.x += speed * direction * deltaTime;

        jumpCooldown -= deltaTime;
        if (jumpCooldown <= 0 && rand() % 100 < 2) {
            velocity.y = -300;
            jumpCooldown = 2.0f;
            isJumping = true;
            currentJumpFrame = 0;
            jumpAnimTimer = 0;
        }

        velocity.y += 800 * deltaTime;
        position.y += velocity.y * deltaTime;

        if (position.y >= GameConstants::GROUND_LEVEL) {
            position.y = GameConstants::GROUND_LEVEL;
            velocity.y = 0;
            isJumping = false;
        }

        // Animation
        if (isJumping && !jumpFrames.empty()) {
            jumpAnimTimer += deltaTime;
            if (jumpAnimTimer >= 0.08f) {
                jumpAnimTimer = 0;
                currentJumpFrame = (currentJumpFrame + 1) % jumpFrames.size();
                sprite.setTexture(jumpFrames[currentJumpFrame]);
            }
        }
        else if (!walkFrames.empty()) {
            walkAnimTimer += deltaTime;
            if (walkAnimTimer >= 0.1f) {
                walkAnimTimer = 0;
                currentWalkFrame = (currentWalkFrame + 1) % walkFrames.size();
                sprite.setTexture(walkFrames[currentWalkFrame]);
            }
        }

        sprite.setPosition(position);
    }
};


class Wizard : public Enemy {
private:
    float shootCooldown;
    float shootTimer;
    bool isAttacking;
    float attackAnimTimer;
    std::vector<FireBall*> fireballs;
    std::vector<sf::Texture> walkFrames;
    std::vector<sf::Texture> attackFrames;
    int currentWalkFrame;
    int currentAttackFrame;
    float walkAnimTimer;

    void loadAnimations() {
        std::string basePath = "textures/";

        // Walk animations (6)
        for (int i = 1; i <= 6; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "walkW" + std::to_string(i) + ".png")) {
                walkFrames.push_back(tex);
            }
        }

        // Attack animations (8)
        for (int i = 1; i <= 8; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "attackW" + std::to_string(i) + ".png")) {
                attackFrames.push_back(tex);
            }
        }

        if (!walkFrames.empty()) {
            sprite.setTexture(walkFrames[0]);
        }
    }

public:
    Wizard(float x, float y) : Enemy(x, y, false) {
        name = "Wizard";
        points = 300;
        damage = 20;
        speed = 30.0f;
        shootCooldown = 2.0f;
        shootTimer = 0;
        isAttacking = false;
        attackAnimTimer = 0;
        currentWalkFrame = 0;
        currentAttackFrame = 0;
        walkAnimTimer = 0;
        loadAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    ~Wizard() {
        for (auto fb : fireballs) {
            delete fb;
        }
        fireballs.clear();
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;

       
        position.x -= speed * deltaTime;

       
        shootTimer += deltaTime;
        if (shootTimer >= shootCooldown) {
            shootTimer = 0;
            isAttacking = true;
            attackAnimTimer = 0.5f;
            currentAttackFrame = 0;

            FireBall* fb = new FireBall(
                sf::Vector2f(position.x, position.y + 20),
                sf::Vector2f(-200, 0)
            );
            fireballs.push_back(fb);
        }

        // Gestion de l'animation d'attaque
        if (isAttacking && !attackFrames.empty()) {
            attackAnimTimer -= deltaTime;
            if (attackAnimTimer > 0) {
                // Animation d'attaque
                walkAnimTimer += deltaTime;
                if (walkAnimTimer >= 0.08f) {
                    walkAnimTimer = 0;
                    currentAttackFrame = (currentAttackFrame + 1) % attackFrames.size();
                    sprite.setTexture(attackFrames[currentAttackFrame]);
                }
            }
            else {
                isAttacking = false;
                currentWalkFrame = 0;
            }
        }
        else if (!walkFrames.empty()) {
            // Animation de marche
            walkAnimTimer += deltaTime;
            if (walkAnimTimer >= 0.12f) {
                walkAnimTimer = 0;
                currentWalkFrame = (currentWalkFrame + 1) % walkFrames.size();
                sprite.setTexture(walkFrames[currentWalkFrame]);
            }
        }

        sprite.setPosition(position);

        for (int i = 0; i < fireballs.size(); i++) {
            fireballs[i]->update(deltaTime);
            if (fireballs[i]->isExpired() || !fireballs[i]->isActive()) {
                delete fireballs[i];
                fireballs.erase(fireballs.begin() + i);
                i--;
            }
        }
    }

    void render(sf::RenderWindow& window) override {
        Enemy::render(window);
        for (auto fb : fireballs) {
            fb->render(window);
        }
    }

    std::vector<FireBall*>& getFireballs() { return fireballs; }
};


class FlyingEye : public Enemy {
private:
    std::vector<sf::Texture> flyFrames;
    int currentFlyFrame;
    float flyAnimTimer;

    void loadFlyAnimations() {
        std::string basePath = "textures/";
        for (int i = 1; i <= 7; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "flyF" + std::to_string(i) + ".png")) {
                flyFrames.push_back(tex);
            }
        }
        if (!flyFrames.empty()) {
            sprite.setTexture(flyFrames[0]);
        }
    }

public:
    FlyingEye(float x, float y) : Enemy(x, y, true) {
        name = "FlyingEye";
        points = 120;
        damage = 15;
        speed = 90.0f;
        currentFlyFrame = 0;
        flyAnimTimer = 0;
        loadFlyAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;
        position.x -= speed * deltaTime;

        // Animation
        flyAnimTimer += deltaTime;
        if (flyAnimTimer >= 0.1f && !flyFrames.empty()) {
            flyAnimTimer = 0;
            currentFlyFrame = (currentFlyFrame + 1) % flyFrames.size();
            sprite.setTexture(flyFrames[currentFlyFrame]);
        }

        sprite.setPosition(position);
    }
};


class Werewolf : public Enemy {
private:
    std::vector<sf::Texture> runFrames;
    int currentRunFrame;
    float runAnimTimer;

    void loadRunAnimations() {
        std::string basePath = "textures/";
        for (int i = 1; i <= 9; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "runW" + std::to_string(i) + ".png")) {
                runFrames.push_back(tex);
            }
        }
        if (!runFrames.empty()) {
            sprite.setTexture(runFrames[0]);
        }
    }

public:
    Werewolf(float x, float y) : Enemy(x, y, false) {
        name = "Werewolf";
        points = 350;
        damage = 35;
        speed = 200.0f;
        currentRunFrame = 0;
        runAnimTimer = 0;
        loadRunAnimations();
        sprite.setScale(2.5f, 2.5f);
    }

    void update(float deltaTime) override {
        if (!active || isDead) return;
        position.x -= speed * deltaTime;

        // Animation (rapide car il court)
        runAnimTimer += deltaTime;
        if (runAnimTimer >= 0.07f && !runFrames.empty()) {
            runAnimTimer = 0;
            currentRunFrame = (currentRunFrame + 1) % runFrames.size();
            sprite.setTexture(runFrames[currentRunFrame]);
        }

        sprite.setPosition(position);
    }
};

#endif // NIGHT_ENEMY_H