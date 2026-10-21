#include "Game.h"
#include "Config.h"
#include "FontManager.h"
#include <random>
#include <iostream>
#include <ctime>

// ============================================================================
// CONSTRUCTEUR
// ============================================================================

Game::Game() : window(sf::VideoMode(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT),
    "Mario Style - Jeu de Cachette") {
    window.setFramerateLimit(60);

    camera.setSize(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT);
    camera.setCenter(GameConstants::SCREEN_WIDTH / 2, GameConstants::SCREEN_HEIGHT / 2);

    FontManager::initialiser();
    initTexts();
    loadTextures();
    loadMusic();

    gameTime = 0;
    timeLimit = GameConstants::TIME_LIMIT;
    isPlaying = false;
    isPaused = false;
    isMuted = false;
    showVictory = false;
    showAbout = false;
    showPauseMenu = false;
    showResultWindow = false;
    currentMode = GameMode::DAY;
    showCastle = false;
    currentBackgroundMusic = nullptr;

    miniMap.setMapPosition(10, 10);
    miniMap.setMapSize(180, 100);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Game::~Game() {}

// ============================================================================
// CHARGEMENT DES MUSIQUES
// ============================================================================

void Game::loadMusic() {
    
    if (!backgroundMusicDay.openFromFile("sounds/background_music_day.wav")) {
        std::cerr << "Erreur: Impossible de charger background_music_day.wav" << std::endl;
    }
    else {
        backgroundMusicDay.setLoop(true);
        backgroundMusicDay.setVolume(25);
    }

    
    if (!backgroundMusicNight.openFromFile("sounds/background_music_night.mp3")) {
        std::cerr << "Erreur: Impossible de charger background_music_night.wav" << std::endl;
    }
    else {
        backgroundMusicNight.setLoop(true);
        backgroundMusicNight.setVolume(25);
    }
}

// ============================================================================
// FONCTION POUR CENTRER LES TEXTES
// ============================================================================

void Game::centerText(sf::Text& text, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    float x = (GameConstants::SCREEN_WIDTH - textRect.width) / 2.0f;
    text.setPosition(x, y);
}

// ============================================================================
// CHARGEMENT DES TEXTURES
// ============================================================================

void Game::loadTextures() {
    // Chargement des backgrounds
    if (!backgroundDayTexture.loadFromFile("textures/background_day.png")) {
        std::cerr << "Erreur: Impossible de charger background_day.png" << std::endl;
    }
    backgroundDayTexture.setRepeated(true);
    backgroundDaySprite.setTexture(backgroundDayTexture);

    if (!backgroundNightTexture.loadFromFile("textures/background_night.jpg")) {
        std::cerr << "Erreur: Impossible de charger background_night.jpg" << std::endl;
    }
    backgroundNightTexture.setRepeated(true);
    backgroundNightSprite.setTexture(backgroundNightTexture);

    // Chargement du château
    if (!castleTexture.loadFromFile("textures/castle.png")) {
        std::cerr << "Erreur: Impossible de charger castle.png" << std::endl;
    }
    castleSprite.setTexture(castleTexture);
    castleSprite.setScale(2.0f, 2.0f);
    castleX = GameConstants::GOAL_X - 100;
    castleSprite.setPosition(castleX, GameConstants::GROUND_LEVEL - 200);

    // Chargement des boutons
    if (!muteTexture.loadFromFile("textures/btn_mute.png")) {
        std::cerr << "Erreur: Impossible de charger btn_mute.png" << std::endl;
    }
    muteSprite.setTexture(muteTexture);
    muteSprite.setScale(1.0f, 1.0f);

    if (!pauseTexture.loadFromFile("textures/btn_pause.png")) {
        std::cerr << "Erreur: Impossible de charger btn_pause.png" << std::endl;
    }
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setScale(1.0f, 1.0f);

    if (!menuTexture.loadFromFile("textures/btn_menu.png")) {
        std::cerr << "Erreur: Impossible de charger btn_menu.png" << std::endl;
    }
    menuSprite.setTexture(menuTexture);
    menuSprite.setScale(1.0f, 1.0f);

    if (!aboutTexture.loadFromFile("textures/btn_about.png")) {
        std::cerr << "Erreur: Impossible de charger btn_about.png" << std::endl;
    }
    aboutSprite.setTexture(aboutTexture);
    aboutSprite.setScale(1.0f, 1.0f);

    if (!playTexture.loadFromFile("textures/btn_play.png")) {
        std::cerr << "Erreur: Impossible de charger btn_play.png" << std::endl;
    }
    playSprite.setTexture(playTexture);
    playSprite.setScale(1.0f, 1.0f);

    if (!heartTexture.loadFromFile("textures/heart.png")) {
        std::cerr << "Erreur: Impossible de charger heart.png" << std::endl;
    }

    // ===== IMAGES POUR GAME OVER, VICTORY, ABOUT ET PAUSE =====
    if (!gameOverTexture.loadFromFile("textures/gameover.jpg")) {
        std::cerr << "Erreur: Impossible de charger gameover.jpg" << std::endl;
    }
    else {
        gameOverSprite.setTexture(gameOverTexture);
        sf::Vector2u texSize = gameOverTexture.getSize();
        float scaleX = GameConstants::SCREEN_WIDTH / static_cast<float>(texSize.x);
        float scaleY = GameConstants::SCREEN_HEIGHT / static_cast<float>(texSize.y);
        gameOverSprite.setScale(scaleX, scaleY);
        gameOverSprite.setPosition(0, 0);
    }

    if (!victoryTexture.loadFromFile("textures/victory.jpg")) {
        std::cerr << "Erreur: Impossible de charger victory.jpg" << std::endl;
    }
    else {
        victorySprite.setTexture(victoryTexture);
        sf::Vector2u texSize = victoryTexture.getSize();
        float scaleX = GameConstants::SCREEN_WIDTH / static_cast<float>(texSize.x);
        float scaleY = GameConstants::SCREEN_HEIGHT / static_cast<float>(texSize.y);
        victorySprite.setScale(scaleX, scaleY);
        victorySprite.setPosition(0, 0);
    }

    if (!aboutBgTexture.loadFromFile("textures/about_bg.jpg")) {
        std::cerr << "Erreur: Impossible de charger about_bg.jpg" << std::endl;
    }
    else {
        aboutBgSprite.setTexture(aboutBgTexture);
        sf::Vector2u texSize = aboutBgTexture.getSize();
        float scaleX = GameConstants::SCREEN_WIDTH / static_cast<float>(texSize.x);
        float scaleY = GameConstants::SCREEN_HEIGHT / static_cast<float>(texSize.y);
        aboutBgSprite.setScale(scaleX, scaleY);
        aboutBgSprite.setPosition(0, 0);
    }

    if (!pauseBgTexture.loadFromFile("textures/pause_bg.jpg")) {
        std::cerr << "Erreur: Impossible de charger pause_bg.jpg" << std::endl;
    }
    else {
        pauseBgSprite.setTexture(pauseBgTexture);
        sf::Vector2u texSize = pauseBgTexture.getSize();
        float scaleX = GameConstants::SCREEN_WIDTH / static_cast<float>(texSize.x);
        float scaleY = GameConstants::SCREEN_HEIGHT / static_cast<float>(texSize.y);
        pauseBgSprite.setScale(scaleX, scaleY);
        pauseBgSprite.setPosition(0, 0);
    }
}

void Game::updateHeartsDisplay() {
    heartSprites.clear();
    for (int i = 0; i < player.getCurrentHearts(); i++) {
        sf::Sprite heart;
        heart.setTexture(heartTexture);
        heart.setScale(0.8f, 0.8f);
        heart.setPosition(10 + i * 45, 145);
        heartSprites.push_back(heart);
    }
}

// ============================================================================
// INITIALISATION DES TEXTES
// ============================================================================

void Game::initTexts() {
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(10, 120);

    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Cyan);
    timerText.setOutlineColor(sf::Color::Black);
    timerText.setOutlineThickness(2);
    timerText.setStyle(sf::Text::Bold);
    timerText.setPosition(GameConstants::SCREEN_WIDTH - 150, 10);

    distanceText.setCharacterSize(16);
    distanceText.setFillColor(sf::Color::Yellow);
    distanceText.setOutlineColor(sf::Color::Black);
    distanceText.setOutlineThickness(2);
    distanceText.setStyle(sf::Text::Bold);
    distanceText.setPosition(GameConstants::SCREEN_WIDTH - 150, 40);

    aboutScreenText.setString(
        "==================== JEU DE CACHETTE ====================\n\n"
        "OBJECTIF: Atteindre la fin du niveau avant la fin du temps!\n\n"
        "CONTROLES:\n"
        "  fleche droite ou D : Courir vers la droite\n"
        "  fleche gauche ou A : Courir vers la gauche\n"
        "  fleche dessus ou ESPACE : Sauter (double saut possible!)\n"
        "  ESC : Pause / Fermer\n\n"
        "MODE JOUR: Ennemis normaux\n"
        "MODE NUIT: Ennemis speciaux (7 types!)\n\n"
        "POWER-UPS:\n"
        "  Grise : Grandir\n"
        "  Jaune : Speed boost\n"
        "  Rouge : Soin\n\n"
        "PLATEFORMES:\n"
        "  PLATEFORMES NORMALES: Marchez dessus normalement\n"
        "  PLATEFORMES NAPPSES (JAUNES): Rebondissez plus haut!\n\n"
        "==========================================================\n"
        "   Cliquez sur X ou appuyez sur ECHAP pour fermer"
    );
    aboutScreenText.setCharacterSize(16);
    aboutScreenText.setFillColor(sf::Color::White);
    aboutScreenText.setOutlineColor(sf::Color::Black);
    aboutScreenText.setOutlineThickness(1);
    aboutScreenText.setPosition(50, 100);

    if (FontManager::estInitialise()) {
        const sf::Font& font = FontManager::getPolice("default");
        scoreText.setFont(font);
        timerText.setFont(font);
        distanceText.setFont(font);
        aboutScreenText.setFont(font);
    }

    soundManager.loadSound("jump", SoundPaths::JUMP);
    soundManager.loadSound("coin", SoundPaths::COIN);
    soundManager.loadSound("hit", SoundPaths::HIT);
    soundManager.loadSound("stomp", SoundPaths::STOMP);
    soundManager.loadSound("gameover", SoundPaths::GAMEOVER);
    soundManager.loadSound("victory", SoundPaths::VICTORY);
    soundManager.loadSound("powerup", SoundPaths::POWERUP);
}

// ============================================================================
// FENÊTRE GAME OVER / VICTOIRE
// ============================================================================

void Game::showResultWindowFunction(const std::string& title, const std::string& message, int score) {
    showResultWindow = true;

    float startX = 20;
    float centerY = GameConstants::SCREEN_HEIGHT / 2.0f;

    resultTitle.setString(title);
    resultTitle.setCharacterSize(50);
    resultTitle.setFillColor((title == "VICTOIRE !") ? sf::Color::Yellow : sf::Color::Red);
    resultTitle.setOutlineColor(sf::Color::Black);
    resultTitle.setOutlineThickness(3);
    resultTitle.setStyle(sf::Text::Bold);
    resultTitle.setPosition(startX, centerY - 180);

    resultMessage.setString(message);
    resultMessage.setCharacterSize(20);
    resultMessage.setFillColor(sf::Color::White);
    resultMessage.setOutlineColor(sf::Color::Black);
    resultMessage.setOutlineThickness(2);
    resultMessage.setPosition(startX, centerY - 80);

    resultScoreText.setString("SCORE: " + std::to_string(score));
    resultScoreText.setCharacterSize(32);
    resultScoreText.setFillColor(sf::Color::Cyan);
    resultScoreText.setOutlineColor(sf::Color::Black);
    resultScoreText.setOutlineThickness(2);
    resultScoreText.setStyle(sf::Text::Bold);
    resultScoreText.setPosition(startX, centerY + 20);

    resultInstruction.setString("Appuyez sur R pour rejouer ou ESC pour quitter");
    resultInstruction.setCharacterSize(16);
    resultInstruction.setFillColor(sf::Color(200, 200, 200));
    resultInstruction.setOutlineColor(sf::Color::Black);
    resultInstruction.setOutlineThickness(1);
    resultInstruction.setPosition(startX, centerY + 100);

    if (FontManager::estInitialise()) {
        const sf::Font& font = FontManager::getPolice("default");
        resultTitle.setFont(font);
        resultMessage.setFont(font);
        resultScoreText.setFont(font);
        resultInstruction.setFont(font);
    }
}

// ============================================================================
// UPDATE UI
// ============================================================================

void Game::updateUI() {
    scoreText.setString("SCORE: " + std::to_string(player.getScore()));

    float remainingTime = std::max(0.0f, timeLimit - gameTime);
    timerText.setString("TIME: " + std::to_string((int)remainingTime) + "s");

    float distanceRemaining = (GameConstants::WORLD_WIDTH - player.getPosition().x) / 100.0f;
    distanceText.setString("DIST: " + std::to_string((int)distanceRemaining) + "m");

    updateHeartsDisplay();
}

// ============================================================================
// LOAD LEVEL - 45 PLATEFORMES
// ============================================================================

void Game::loadLevel(GameMode mode) {
    platforms.clear();
    enemies.clear();
    coins.clear();
    powerUps.clear();
    fireBalls.clear();

    platforms.push_back(Platform(0, GameConstants::GROUND_LEVEL,
        GameConstants::WORLD_WIDTH, 50, false, true));

    // ZONE 1: DÉPART (0 - 1500)
    platforms.push_back(Platform(200, 420, 80, 25, false));
    platforms.push_back(Platform(600, 450, 80, 25, false));
    platforms.push_back(Platform(800, 320, 80, 25, false));
    platforms.push_back(Platform(1000, 400, 80, 25, true));
    platforms.push_back(Platform(1200, 280, 80, 25, false));
    platforms.push_back(Platform(1400, 380, 80, 25, true));

    // ZONE 2: PREMIER DÉFI (1500 - 3500)
    platforms.push_back(Platform(1650, 450, 80, 25, false));
    platforms.push_back(Platform(1850, 350, 80, 25, true));
    platforms.push_back(Platform(2050, 400, 80, 25, false));
    platforms.push_back(Platform(2250, 300, 80, 25, false));
    platforms.push_back(Platform(2450, 420, 80, 25, true));
    platforms.push_back(Platform(2650, 340, 80, 25, false));
    platforms.push_back(Platform(2850, 460, 80, 25, false));
    platforms.push_back(Platform(3050, 310, 80, 25, true));
    platforms.push_back(Platform(3250, 380, 80, 25, false));
    platforms.push_back(Platform(3450, 270, 80, 25, false));

    // ZONE 3: DÉFI DIFFICILE (3500 - 6000)
    platforms.push_back(Platform(3700, 430, 80, 25, true));
    platforms.push_back(Platform(3950, 330, 80, 25, false));
    platforms.push_back(Platform(4200, 380, 80, 25, false));
    platforms.push_back(Platform(4450, 290, 80, 25, true));
    platforms.push_back(Platform(4700, 440, 80, 25, false));
    platforms.push_back(Platform(4950, 350, 80, 25, false));
    platforms.push_back(Platform(5200, 400, 80, 25, true));
    platforms.push_back(Platform(5450, 310, 80, 25, false));
    platforms.push_back(Platform(5700, 450, 80, 25, false));
    platforms.push_back(Platform(5950, 280, 80, 25, true));

    // ZONE 4: APPROCHE (6000 - 8000)
    platforms.push_back(Platform(6200, 400, 80, 25, false));
    platforms.push_back(Platform(6450, 320, 80, 25, true));
    platforms.push_back(Platform(6700, 370, 80, 25, false));
    platforms.push_back(Platform(6950, 280, 80, 25, false));
    platforms.push_back(Platform(7200, 430, 80, 25, true));
    platforms.push_back(Platform(7450, 340, 80, 25, false));
    platforms.push_back(Platform(7700, 390, 80, 25, false));
    platforms.push_back(Platform(7950, 300, 80, 25, true));
    platforms.push_back(Platform(8200, 420, 80, 25, false));
    platforms.push_back(Platform(8450, 260, 80, 25, false));

    // ZONE 5: FINALE (8500 - 10000)
    platforms.push_back(Platform(8700, 380, 80, 25, true));
    platforms.push_back(Platform(8950, 310, 80, 25, false));
    platforms.push_back(Platform(9200, 440, 80, 25, false));
    platforms.push_back(Platform(9450, 350, 80, 25, true));

    // PIÈCES DE MONNAIE
    for (int i = 0; i < GameConstants::COIN_COUNT; i++) {
        float x = 50.0f + (rand() % 9700);
        float y = 200.0f + (rand() % 250);
        coins.push_back(std::make_unique<Coin>(x, y));
    }

    // POWER-UPS
    powerUps.push_back(std::make_unique<PowerUp>(500.0f, 370.0f, PowerUpType::GROWTH));
    powerUps.push_back(std::make_unique<PowerUp>(1500.0f, 400.0f, PowerUpType::SPEED));
    powerUps.push_back(std::make_unique<PowerUp>(2500.0f, 350.0f, PowerUpType::HEALTH));
    powerUps.push_back(std::make_unique<PowerUp>(3600.0f, 380.0f, PowerUpType::GROWTH));
    powerUps.push_back(std::make_unique<PowerUp>(4700.0f, 400.0f, PowerUpType::SPEED));
    powerUps.push_back(std::make_unique<PowerUp>(5800.0f, 350.0f, PowerUpType::HEALTH));
    powerUps.push_back(std::make_unique<PowerUp>(6900.0f, 370.0f, PowerUpType::GROWTH));
    powerUps.push_back(std::make_unique<PowerUp>(8000.0f, 380.0f, PowerUpType::SPEED));

    // ENNEMIS MODE JOUR
    if (mode == GameMode::DAY) {
        for (int i = 0; i < 40; i++) {
            float x = 200.0f + (rand() % 9500);
            float y = GameConstants::GROUND_LEVEL - 160;
            enemies.push_back(std::make_unique<GroundEnemy>(x, y));
        }
        for (int i = 0; i < 15; i++) {
            float x = 400.0f + (rand() % 9200);
            float y = 100 + (rand() % 100);
            enemies.push_back(std::make_unique<FlyingEnemy>(x, y));
        }
    }
    // ENNEMIS MODE NUIT
    else {
        for (int i = 0; i < 15; i++) {
            float x = 200.0f + (rand() % 9500);
            float y = 150 + (rand() % 150);
            enemies.push_back(std::make_unique<Bat>(x, y));
        }
        for (int i = 0; i < 10; i++) {
            float x = 500.0f + (rand() % 9000);
            float y = 200 + (rand() % 150);
            enemies.push_back(std::make_unique<Ghost>(x, y));
        }
        for (int i = 0; i < 8; i++) {
            float x = 800.0f + (rand() % 8500);
            float y = 100 + (rand() % 200);
            enemies.push_back(std::make_unique<Spider>(x, y));
        }
        for (int i = 0; i < 12; i++) {
            float x = 300.0f + (rand() % 9400);
            float y = GameConstants::GROUND_LEVEL - 30;
            enemies.push_back(std::make_unique<Zombie>(x, y));
        }
        for (int i = 0; i < 6; i++) {
            float x = 1500.0f + (rand() % 8000);
            float y = 520;
            enemies.push_back(std::make_unique<Wizard>(x, y));
        }
        for (int i = 0; i < 10; i++) {
            float x = 600.0f + (rand() % 8800);
            float y = 100 + (rand() % 100);
            enemies.push_back(std::make_unique<FlyingEye>(x, y));
        }
        for (int i = 0; i < 4; i++) {
            float x = 2500.0f + i * 2500.0f;
            float y = GameConstants::GROUND_LEVEL - 30;
            enemies.push_back(std::make_unique<Werewolf>(x, y));
        }
    }
}

// ============================================================================
// CHECK COLLISIONS
// ============================================================================

void Game::checkCollisions(float deltaTime) {
    bool onGround = false;

    // COLLISIONS AVEC LES PLATEFORMES
    for (auto& platform : platforms) {
        if (player.getBounds().intersects(platform.getBounds())) {
            sf::FloatRect playerBounds = player.getBounds();
            sf::FloatRect platformBounds = platform.getBounds();

            float playerBottom = playerBounds.top + playerBounds.height;
            float platformTop = platformBounds.top;

            if (player.getVelocity().y > 0 && playerBottom > platformTop && playerBottom < platformTop + 35) {
                player.setPosition(player.getPosition().x, platformTop - playerBounds.height / 2);
                player.setGrounded(true);
                player.setVelocityY(0);
                onGround = true;

                if (platform.isBouncyPlatform()) {
                    player.setVelocityY(GameConstants::BOUNCE_FORCE);
                    soundManager.playSound("jump");
                }
            }
        }
    }

    player.setGrounded(onGround);

    // MISE À JOUR DE L'ATTAQUE DES ENNEMIS
    for (auto& enemy : enemies) {
        if (!enemy->isActive()) continue;
        enemy->updateAttack(deltaTime, player.getPosition());
    }

    // COLLISIONS AVEC LES ENNEMIS
    for (auto& enemy : enemies) {
        if (!enemy->isActive()) continue;

        if (player.getBounds().intersects(enemy->getBounds())) {
            sf::FloatRect playerBounds = player.getBounds();
            float playerBottom = playerBounds.top + playerBounds.height;
            float enemyTop = enemy->getBounds().top;

            if (player.getVelocity().y > 0 && playerBottom > enemyTop && playerBottom < enemyTop + 25) {
                enemy->die();
                player.addScore(enemy->getPoints());
                player.setVelocityY(-400);
                soundManager.playSound("stomp");
            }
            else {
                if (enemy->isAttackingNow()) {
                    player.takeDamage(enemy->getDamage());
                    soundManager.playSound("hit");
                }
                else {
                    player.takeDamage(enemy->getDamage());
                    soundManager.playSound("hit");
                }
            }
        }
    }

    // COLLISIONS AVEC LES PIÈCES
    for (auto& coin : coins) {
        if (!coin->isActive()) continue;
        if (player.getBounds().intersects(coin->getBounds())) {
            coin->setActive(false);
            player.addCoin();
            soundManager.playSound("coin");
        }
    }

    // COLLISIONS AVEC LES POWER-UPS
    for (auto& powerUp : powerUps) {
        if (!powerUp->isActive()) continue;
        if (player.getBounds().intersects(powerUp->getBounds())) {
            powerUp->setActive(false);
            soundManager.playSound("powerup");

            switch (powerUp->getType()) {
            case PowerUpType::GROWTH:
                player.grow();
                break;
            case PowerUpType::SPEED:
                player.activateSpeedBoost(GameConstants::SPEED_BOOST_DURATION);
                break;
            case PowerUpType::HEALTH:
                player.heal(1);
                break;
            }
            player.addScore(powerUp->getPoints());
        }
    }
}

// ============================================================================
// CHECK WIN CONDITION
// ============================================================================

void Game::checkWinCondition() {
    if (player.getBounds().intersects(castleSprite.getGlobalBounds())) {
        
        if (currentBackgroundMusic != nullptr) {
            currentBackgroundMusic->stop();
        }
        isPlaying = false;
        soundManager.playSound("victory");

        int score = player.getScore();
        std::string message;

        if (score >= 5000) {
            message = "PARFAIT ! Vous etes un champion !\nVous avez battu tous les records !";
        }
        else if (score >= 3000) {
            message = "EXCELLENT ! Tres bonne performance !";
        }
        else if (score >= 1500) {
            message = "BIEN ! Continuez comme ca !";
        }
        else {
            message = "PAS MAL ! Essayez de faire mieux la prochaine fois !";
        }

        showResultWindowFunction("VICTOIRE !", message, score);
    }

    if (!player.getIsAlive()) {
        
        if (currentBackgroundMusic != nullptr) {
            currentBackgroundMusic->stop();
        }
        isPlaying = false;
        soundManager.playSound("gameover");

        int score = player.getScore();
        std::string message;

        if (score >= 3000) {
            message = "DOMMAGE ! Vous etiez si proche de la victoire !";
        }
        else if (score >= 1500) {
            message = "BON ESSAI ! Reessayez pour faire mieux !";
        }
        else {
            message = "N'ABANDONNEZ PAS ! Entrainez-vous encore !";
        }

        showResultWindowFunction("GAME OVER", message, score);
    }
}

// ============================================================================
// UPDATE
// ============================================================================

void Game::update(float deltaTime) {
    if (!isPlaying || isPaused || showAbout || showResultWindow) return;

    gameTime += deltaTime;
    if (gameTime >= timeLimit) {
        isPlaying = false;
        showResultWindowFunction("GAME OVER", "TEMPS ECOULE !\nVous n'avez pas atteint la fin a temps !", player.getScore());
        return;
    }

    player.handleInput();
    player.update(deltaTime);

    sf::Vector2f targetPos = player.getPosition();
    sf::Vector2f currentPos = camera.getCenter();
    camera.setCenter(currentPos + (targetPos - currentPos) * GameConstants::CAMERA_SMOOTHNESS);

    if (camera.getCenter().x < GameConstants::CAMERA_MIN_X)
        camera.setCenter(GameConstants::CAMERA_MIN_X, camera.getCenter().y);
    if (camera.getCenter().x > GameConstants::CAMERA_MAX_X)
        camera.setCenter(GameConstants::CAMERA_MAX_X, camera.getCenter().y);
    if (camera.getCenter().y < GameConstants::CAMERA_MIN_Y)
        camera.setCenter(camera.getCenter().x, GameConstants::CAMERA_MIN_Y);
    if (camera.getCenter().y > GameConstants::CAMERA_MAX_Y)
        camera.setCenter(camera.getCenter().x, GameConstants::CAMERA_MAX_Y);

    for (auto& platform : platforms) platform.update(deltaTime);
    for (auto& enemy : enemies) enemy->update(deltaTime);
    for (auto& coin : coins) coin->update(deltaTime);
    for (auto& powerUp : powerUps) powerUp->update(deltaTime);
    for (auto& ball : fireBalls) ball->update(deltaTime);

    checkCollisions(deltaTime);
    checkWinCondition();

    miniMap.update(player.getPosition(), GameConstants::WORLD_WIDTH, GameConstants::WORLD_HEIGHT);
    updateUI();
}

// ============================================================================
// RENDER
// ============================================================================

void Game::render() {
    window.clear();
    window.setView(camera);

    // BACKGROUND
    sf::Vector2f viewSize = camera.getSize();

    if (currentMode == GameMode::DAY) {
        sf::Vector2u textureSize = backgroundDayTexture.getSize();
        backgroundDaySprite.setScale(viewSize.x / textureSize.x, viewSize.y / textureSize.y);
        backgroundDaySprite.setPosition(camera.getCenter().x - viewSize.x / 2,
            camera.getCenter().y - viewSize.y / 2);
        window.draw(backgroundDaySprite);
    }
    else {
        sf::Vector2u textureSize = backgroundNightTexture.getSize();
        backgroundNightSprite.setScale(viewSize.x / textureSize.x, viewSize.y / textureSize.y);
        backgroundNightSprite.setPosition(camera.getCenter().x - viewSize.x / 2,
            camera.getCenter().y - viewSize.y / 2);
        window.draw(backgroundNightSprite);
    }

    // CHÂTEAU
    if (player.getPosition().x > castleX - 500) {
        window.draw(castleSprite);
    }

    // PLATEFORMES ET OBJETS
    for (auto& platform : platforms) platform.render(window);
    for (auto& coin : coins) coin->render(window);
    for (auto& powerUp : powerUps) powerUp->render(window);
    for (auto& enemy : enemies) enemy->render(window);
    for (auto& ball : fireBalls) ball->render(window);
    player.render(window);

    // INTERFACE FIXE
    window.setView(window.getDefaultView());

    miniMap.render(window);

    float btnX = 200;
    float btnY = 10;
    float btnSpacing = 55;

    muteSprite.setPosition(btnX, btnY);
    pauseSprite.setPosition(btnX + btnSpacing, btnY);
    menuSprite.setPosition(btnX + btnSpacing * 2, btnY);
    aboutSprite.setPosition(btnX + btnSpacing * 3, btnY);

    window.draw(muteSprite);
    window.draw(pauseSprite);
    window.draw(menuSprite);
    window.draw(aboutSprite);

    window.draw(scoreText);
    for (auto& heart : heartSprites) window.draw(heart);
    window.draw(timerText);
    window.draw(distanceText);

    // ===== ÉCRAN ABOUT =====
    if (showAbout) {
        if (aboutBgTexture.getSize().x > 0) {
            window.draw(aboutBgSprite);
        }
        else {
            sf::RectangleShape overlay(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT));
            overlay.setFillColor(sf::Color(0, 0, 0, 230));
            window.draw(overlay);
        }

        sf::RectangleShape textOverlay(sf::Vector2f(GameConstants::SCREEN_WIDTH - 100, GameConstants::SCREEN_HEIGHT - 100));
        textOverlay.setFillColor(sf::Color(0, 0, 0, 200));
        textOverlay.setPosition(50, 50);
        window.draw(textOverlay);

        sf::RectangleShape closeButton(sf::Vector2f(35, 35));
        closeButton.setFillColor(sf::Color(200, 50, 50));
        closeButton.setOutlineColor(sf::Color::White);
        closeButton.setOutlineThickness(2);
        closeButton.setPosition(GameConstants::SCREEN_WIDTH - 50, 15);
        window.draw(closeButton);

        sf::Text closeText;
        if (FontManager::estInitialise()) closeText.setFont(FontManager::getPolice("default"));
        closeText.setString("X");
        closeText.setCharacterSize(22);
        closeText.setFillColor(sf::Color::White);
        closeText.setOutlineColor(sf::Color::Black);
        closeText.setOutlineThickness(1);
        closeText.setStyle(sf::Text::Bold);
        closeText.setPosition(GameConstants::SCREEN_WIDTH - 42, 20);
        window.draw(closeText);

        window.draw(aboutScreenText);
    }

    // ===== GAME OVER / VICTOIRE =====
    if (showResultWindow && !isPlaying) {
        sf::View savedView = window.getView();
        window.setView(window.getDefaultView());

        if (resultTitle.getString() == "GAME OVER") {
            if (gameOverTexture.getSize().x > 0) {
                window.draw(gameOverSprite);
            }
            else {
                sf::RectangleShape bg(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT));
                bg.setFillColor(sf::Color(0, 0, 0));
                window.draw(bg);
            }
        }
        else {
            if (victoryTexture.getSize().x > 0) {
                window.draw(victorySprite);
            }
            else {
                sf::RectangleShape bg(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT));
                bg.setFillColor(sf::Color(0, 0, 0));
                window.draw(bg);
            }
        }

        sf::RectangleShape fullOverlay(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT));
        fullOverlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(fullOverlay);

        sf::RectangleShape textFrame(sf::Vector2f(GameConstants::SCREEN_WIDTH - 200, 350));
        textFrame.setFillColor(sf::Color(0, 0, 0, 220));
        textFrame.setOutlineColor(sf::Color(255, 215, 0, 150));
        textFrame.setOutlineThickness(3);
        textFrame.setPosition(100, GameConstants::SCREEN_HEIGHT / 2 - 175);
        window.draw(textFrame);

        float centerY = GameConstants::SCREEN_HEIGHT / 2.0f;

        resultTitle.setPosition(120, centerY - 140);
        resultMessage.setPosition(120, centerY - 60);
        resultScoreText.setPosition(120, centerY + 40);
        resultInstruction.setPosition(120, centerY + 140);

        window.draw(resultTitle);
        window.draw(resultMessage);
        window.draw(resultScoreText);
        window.draw(resultInstruction);

        window.setView(savedView);
    }

    // ===== PAUSE AVEC BACKGROUND =====
    if (isPaused && !showAbout && !showResultWindow) {
        sf::View savedView = window.getView();
        window.setView(window.getDefaultView());

        if (pauseBgTexture.getSize().x > 0) {
            window.draw(pauseBgSprite);
        }
        else {
            sf::RectangleShape bg(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT));
            bg.setFillColor(sf::Color(30, 30, 60));
            window.draw(bg);
        }

        sf::RectangleShape fullOverlay(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT));
        fullOverlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(fullOverlay);

        sf::RectangleShape pauseFrame(sf::Vector2f(GameConstants::SCREEN_WIDTH - 200, 300));
        pauseFrame.setFillColor(sf::Color(0, 0, 0, 200));
        pauseFrame.setOutlineColor(sf::Color(255, 215, 0, 200));
        pauseFrame.setOutlineThickness(4);
        pauseFrame.setPosition(100, GameConstants::SCREEN_HEIGHT / 2 - 150);
        window.draw(pauseFrame);

        sf::Text pauseTitle;
        if (FontManager::estInitialise()) pauseTitle.setFont(FontManager::getPolice("default"));
        pauseTitle.setString("PAUSE");
        pauseTitle.setCharacterSize(55);
        pauseTitle.setFillColor(sf::Color(255, 215, 0));
        pauseTitle.setOutlineColor(sf::Color::Black);
        pauseTitle.setOutlineThickness(4);
        pauseTitle.setStyle(sf::Text::Bold);

        sf::FloatRect titleRect = pauseTitle.getLocalBounds();
        float titleX = (GameConstants::SCREEN_WIDTH - titleRect.width) / 2.0f;

        sf::Text shadowTitle = pauseTitle;
        shadowTitle.setPosition(titleX + 3, GameConstants::SCREEN_HEIGHT / 2 - 110);
        shadowTitle.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(shadowTitle);

        pauseTitle.setPosition(titleX, GameConstants::SCREEN_HEIGHT / 2 - 115);
        window.draw(pauseTitle);

        sf::Text pauseMsg;
        if (FontManager::estInitialise()) pauseMsg.setFont(FontManager::getPolice("default"));
        pauseMsg.setString("Appuyez sur ESC ou cliquez sur Play pour continuer");
        pauseMsg.setCharacterSize(22);
        pauseMsg.setFillColor(sf::Color::White);
        pauseMsg.setOutlineColor(sf::Color::Black);
        pauseMsg.setOutlineThickness(2);
        pauseMsg.setStyle(sf::Text::Bold);

        sf::FloatRect msgRect = pauseMsg.getLocalBounds();
        float msgX = (GameConstants::SCREEN_WIDTH - msgRect.width) / 2.0f;

        sf::Text shadowMsg = pauseMsg;
        shadowMsg.setPosition(msgX + 2, GameConstants::SCREEN_HEIGHT / 2 - 20);
        shadowMsg.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(shadowMsg);

        pauseMsg.setPosition(msgX, GameConstants::SCREEN_HEIGHT / 2 - 25);
        window.draw(pauseMsg);

        playSprite.setPosition(GameConstants::SCREEN_WIDTH / 2 - 30, GameConstants::SCREEN_HEIGHT / 2 + 60);
        window.draw(playSprite);

        window.setView(savedView);
    }

    window.display();
}

// ============================================================================
// PROCESS EVENTS
// ============================================================================

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (showResultWindow && !isPlaying) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    showResultWindow = false;
                    startGame(currentMode);
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    showResultWindow = false;
                    window.close();
                }
            }
            return;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (showAbout) showAbout = false;
                else if (isPlaying && !isPaused && !showResultWindow) pauseGame();
                else if (isPaused) resumeGame();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            float btnX = 200, btnY = 10, btnSpacing = 55;
            sf::FloatRect muteRect(btnX, btnY, 50, 50);
            sf::FloatRect pauseRect(btnX + btnSpacing, btnY, 50, 50);
            sf::FloatRect menuRect(btnX + btnSpacing * 2, btnY, 50, 50);
            sf::FloatRect aboutRect(btnX + btnSpacing * 3, btnY, 50, 50);
            sf::FloatRect playRect(GameConstants::SCREEN_WIDTH / 2 - 30, 370, 60, 60);
            sf::FloatRect closeRect(GameConstants::SCREEN_WIDTH - 50, 15, 35, 35);

            if (muteRect.contains(worldPos)) toggleMute();
            if (pauseRect.contains(worldPos) && !showAbout && !showResultWindow) {
                if (isPlaying && !isPaused) pauseGame();
                else if (isPaused) resumeGame();
            }
            if (menuRect.contains(worldPos)) exitToMenu();
            if (aboutRect.contains(worldPos)) {
                if (isPlaying && !isPaused) pauseGame();
                showAbout = true;
            }
            if (isPaused && playRect.contains(worldPos)) resumeGame();
            if (showAbout && closeRect.contains(worldPos)) showAbout = false;
        }
    }
}

// ============================================================================
// GAME CONTROL
// ============================================================================

void Game::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        processEvents();
        float deltaTime = deltaClock.restart().asSeconds();
        if (deltaTime > 0.033f) deltaTime = 0.033f;
        update(deltaTime);
        render();
    }
}

void Game::startGame(GameMode mode) {
    currentMode = mode;
    loadLevel(mode);
    player = Player();
    player.setSoundManager(&soundManager);
    gameTime = 0;
    isPlaying = true;
    isPaused = false;
    showVictory = false;
    showAbout = false;
    showResultWindow = false;
    soundManager.setVolume(isMuted ? 0 : 100);

    if (!isMuted) {
        if (currentBackgroundMusic != nullptr) {
            currentBackgroundMusic->stop();
        }

        if (mode == GameMode::DAY) {
            currentBackgroundMusic = &backgroundMusicDay;
        }
        else {
            currentBackgroundMusic = &backgroundMusicNight;
        }

        currentBackgroundMusic->play();
        std::cout << "🎵 Background music started for "
            << (mode == GameMode::DAY ? "DAY" : "NIGHT") << " mode!" << std::endl;
    }
}

void Game::pauseGame() {
    isPaused = true;
    if (currentBackgroundMusic != nullptr) {
        currentBackgroundMusic->pause();
    }
}

void Game::resumeGame() {
    isPaused = false;
    if (currentBackgroundMusic != nullptr && !isMuted) {
        currentBackgroundMusic->play();
    }
}

void Game::toggleMute() {
    isMuted = !isMuted;
    soundManager.setVolume(isMuted ? 0 : 100);

    if (currentBackgroundMusic != nullptr) {
        if (isMuted) {
            currentBackgroundMusic->setVolume(0);
        }
        else {
            currentBackgroundMusic->setVolume(25);
        }
    }
}

void Game::exitToMenu() {
    isPlaying = false;
    if (currentBackgroundMusic != nullptr) {
        currentBackgroundMusic->stop();
    }
    window.close();
}