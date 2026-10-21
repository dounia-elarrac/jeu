#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <unordered_map>
#include <vector>

enum class EnemyState {
    WALK,
    ATTACK,
    DEAD
};

class Enemy : public Entity {
protected:
    float speed;
    float moveRange;
    float startX;
    int direction;
    int damage;
    bool isFlying;

    sf::Texture graveTexture;
    sf::Sprite graveSprite;

    bool isDead;
    float deathTimer;
    float deathDuration;

    // === نظام الحركات ===
    EnemyState currentState;
    std::unordered_map<EnemyState, std::vector<sf::Texture>> animations;
    std::unordered_map<EnemyState, float> animationSpeeds;
    int currentFrame;
    float animationTimer;

    // === نظام الهجوم ===
    float attackRange;      // مسافة الهجوم
    float attackCooldown;   // وقت بين الهجمات
    float attackTimer;      // مؤقت الهجوم
    bool isAttacking;       // هل يهاجم الآن؟
    float attackAnimTimer;  // مؤقت حركة الهجوم

    void setState(EnemyState newState);
    void updateAnimation(float deltaTime);

public:
    Enemy();
    Enemy(float x, float y, bool flying = false);
    virtual ~Enemy();

    void update(float deltaTime) override;
    void updateAttack(float deltaTime, const sf::Vector2f& playerPos);
    void render(sf::RenderWindow& window) override;
    void die();

    sf::FloatRect getBounds() const override;

    int getDamage() const { return damage; }
    bool isAttackingNow() const { return isAttacking; }

    void startAttack() { setState(EnemyState::ATTACK); }
    void stopAttack() { setState(EnemyState::WALK); }
    EnemyState getState() const { return currentState; }
};

// ========== ENNEMIS DE BASE ==========

// العدو الأرضي العادي (مع حركات - 8 إطارات مشي + 8 هجوم)
class GroundEnemy : public Enemy {
public:
    GroundEnemy(float x, float y) : Enemy(x, y, false) {
        name = "GroundEnemy";
        points = 100;
        damage = 20;
        speed = 80.0f;
        attackRange = 60.0f;
        attackCooldown = 1.0f;
        loadAnimations();
        setState(EnemyState::WALK);
        sprite.setScale(2.0f, 2.0f);
    }

private:
    void loadAnimations() {
        std::string basePath = "textures/";

        // WALK (8 frames)
        std::vector<sf::Texture> walkFrames;
        for (int i = 1; i <= 8; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "walkK" + std::to_string(i) + ".png")) {
                walkFrames.push_back(tex);
            }
        }
        animations[EnemyState::WALK] = walkFrames;
        animationSpeeds[EnemyState::WALK] = 0.1f;

        // ATTACK (8 frames)
        std::vector<sf::Texture> attackFrames;
        for (int i = 1; i <= 8; i++) {
            sf::Texture tex;
            if (tex.loadFromFile(basePath + "attackK" + std::to_string(i) + ".png")) {
                attackFrames.push_back(tex);
            }
        }
        animations[EnemyState::ATTACK] = attackFrames;
        animationSpeeds[EnemyState::ATTACK] = 0.08f;

        if (!animations[EnemyState::WALK].empty()) {
            sprite.setTexture(animations[EnemyState::WALK][0]);
        }
    }
};

// العدو الطائر العادي (بدون حركات - صورة ثابتة)
class FlyingEnemy : public Enemy {
public:
    FlyingEnemy(float x, float y) : Enemy(x, y, true) {
        name = "FlyingEnemy";
        points = 100;
        damage = 20;
        speed = 120.0f;
        attackRange = 50.0f;
        attackCooldown = 1.2f;
        loadTexture("textures/enemy_fly.png");
        sprite.setScale(2.0f, 2.0f);
    }
};

#endif // ENEMY_H