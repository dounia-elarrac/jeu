#include "Enemy.h"
#include "Config.h"
#include <iostream>

Enemy::Enemy() : Entity() {
    name = "Enemy";
    points = 100;
    speed = 80.0f;
    moveRange = 150.0f;
    startX = position.x;
    direction = 1;
    damage = 20;
    isFlying = false;
    isDead = false;
    deathTimer = 0.0f;
    deathDuration = 3.0f;

    currentState = EnemyState::WALK;
    currentFrame = 0;
    animationTimer = 0;

    // Initialisation des variables d'attaque
    attackRange = 50.0f;
    attackCooldown = 1.0f;
    attackTimer = 0.0f;
    isAttacking = false;
    attackAnimTimer = 0.0f;

    graveTexture.loadFromFile("textures/grave.png");
    graveSprite.setTexture(graveTexture);
    graveSprite.setScale(1.5f, 1.5f);
}

Enemy::Enemy(float x, float y, bool flying) : Entity(x, y) {
    name = "Enemy";
    points = 100;
    damage = 20;
    isFlying = flying;
    isDead = false;
    deathTimer = 0.0f;
    deathDuration = 3.0f;
    moveRange = 150.0f;
    startX = x;
    direction = 1;

    currentState = EnemyState::WALK;
    currentFrame = 0;
    animationTimer = 0;

    // Initialisation des variables d'attaque
    attackRange = 50.0f;
    attackCooldown = 1.0f;
    attackTimer = 0.0f;
    isAttacking = false;
    attackAnimTimer = 0.0f;

    if (flying) {
        speed = 120.0f;
    }
    else {
        speed = 80.0f;
    }

    sprite.setPosition(position);

    graveTexture.loadFromFile("textures/grave.png");
    graveSprite.setTexture(graveTexture);
    graveSprite.setScale(1.5f, 1.5f);
}

Enemy::~Enemy() {}

void Enemy::setState(EnemyState newState) {
    if (currentState == newState) return;
    currentState = newState;
    currentFrame = 0;
    animationTimer = 0;
    if (!animations[currentState].empty()) {
        sprite.setTexture(animations[currentState][0]);
    }
}

void Enemy::updateAnimation(float deltaTime) {
    auto& frames = animations[currentState];
    if (frames.empty()) return;

    animationTimer += deltaTime;
    if (animationTimer >= animationSpeeds[currentState]) {
        animationTimer = 0;
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTexture(frames[currentFrame]);
    }
}

void Enemy::updateAttack(float deltaTime, const sf::Vector2f& playerPos) {
    // Mise à jour du cooldown
    if (attackTimer > 0) {
        attackTimer -= deltaTime;
    }

    // Calcul de la distance avec le joueur
    float distance = std::abs(position.x - playerPos.x);

    // Vérifier si le joueur est dans la range d'attaque
    if (distance < attackRange && attackTimer <= 0 && !isDead) {
        // Commencer l'attaque
        isAttacking = true;
        attackAnimTimer = 0.5f;  // Durée de l'animation d'attaque
        setState(EnemyState::ATTACK);
        attackTimer = attackCooldown;
    }

    // Gérer la fin de l'animation d'attaque
    if (isAttacking) {
        attackAnimTimer -= deltaTime;
        if (attackAnimTimer <= 0) {
            isAttacking = false;
            setState(EnemyState::WALK);
        }
    }
}

void Enemy::update(float deltaTime) {
    // Si l'ennemi est mort
    if (isDead) {
        deathTimer -= deltaTime;
        if (deathTimer <= 0.0f) {
            isDead = false;
            active = false;
        }
        return;
    }

    if (!active) return;

    // Mouvement normal (seulement si pas en train d'attaquer)
    if (!isAttacking) {
        position.x += speed * direction * deltaTime;

        if (position.x > startX + moveRange) {
            position.x = startX + moveRange;
            direction = -1;
            setFlipped(true);
        }
        if (position.x < startX - moveRange) {
            position.x = startX - moveRange;
            direction = 1;
            setFlipped(false);
        }
    }

    sprite.setPosition(position);

    // Mise à jour de l'animation pour les ennemis terrestres
    if (!isFlying && !animations.empty()) {
        updateAnimation(deltaTime);
    }
}

void Enemy::render(sf::RenderWindow& window) {
    if (isDead && deathTimer > 0) {
        graveSprite.setPosition(position);
        window.draw(graveSprite);
    }
    else if (active && !isDead) {
        window.draw(sprite);
    }
}

void Enemy::die() {
    if (!isDead) {
        isDead = true;
        active = false;
        deathTimer = deathDuration;
        isAttacking = false;
        graveSprite.setPosition(position);
        std::cout << " Enemy died! Grave will disappear in " << deathDuration << " seconds" << std::endl;
    }
}

sf::FloatRect Enemy::getBounds() const {
    if (!active || isDead) {
        return sf::FloatRect(0, 0, 0, 0);
    }
    return sprite.getGlobalBounds();
}