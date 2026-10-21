#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "NightEnemy.h"
#include "Coin.h"
#include "PowerUp.h"
#include "FireBall.h"
#include "MiniMap.h"
#include "SoundManager.h"
#include "FontManager.h"

// ============================================================================
// CONSTANTES DE DÉCALAGE VERTICAL
// ============================================================================
const float VERTICAL_OFFSET = 150.0f;

enum class GameMode {
    DAY,
    NIGHT
};

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;

    Player player;
    std::vector<Platform> platforms;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<PowerUp>> powerUps;
    std::vector<std::unique_ptr<FireBall>> fireBalls;

    MiniMap miniMap;
    SoundManager soundManager;

    // ===== TEXTURES ET SPRITES =====
    sf::Texture backgroundDayTexture;
    sf::Sprite backgroundDaySprite;
    sf::Texture backgroundNightTexture;
    sf::Sprite backgroundNightSprite;

    sf::Texture castleTexture;
    sf::Sprite castleSprite;
    bool showCastle;
    float castleX;

    sf::Texture muteTexture;
    sf::Sprite muteSprite;
    sf::Texture pauseTexture;
    sf::Sprite pauseSprite;
    sf::Texture menuTexture;
    sf::Sprite menuSprite;
    sf::Texture aboutTexture;
    sf::Sprite aboutSprite;
    sf::Texture playTexture;
    sf::Sprite playSprite;

    sf::Texture heartTexture;
    std::vector<sf::Sprite> heartSprites;

    // ===== IMAGES POUR GAME OVER, VICTORY, ABOUT ET PAUSE =====
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    sf::Texture victoryTexture;
    sf::Sprite victorySprite;
    sf::Texture aboutBgTexture;
    sf::Sprite aboutBgSprite;
    sf::Texture pauseBgTexture;
    sf::Sprite pauseBgSprite;

    // ===== MUSIQUES DE FOND =====
    sf::Music backgroundMusicDay;
    sf::Music backgroundMusicNight;
    sf::Music* currentBackgroundMusic;

    // ===== TEXTS =====
    sf::Text scoreText;
    sf::Text timerText;
    sf::Text distanceText;
    sf::Text aboutScreenText;

    // ===== FENÊTRE RESULTAT =====
    sf::Text resultTitle;
    sf::Text resultMessage;
    sf::Text resultScoreText;
    sf::Text resultInstruction;
    bool showResultWindow;

    // ===== STATES =====
    GameMode currentMode;
    float gameTime;
    float timeLimit;
    bool isPlaying;
    bool isPaused;
    bool isMuted;
    bool showVictory;
    bool showAbout;
    bool showPauseMenu;

    // ===== PRIVATE METHODS =====
    void loadLevel(GameMode mode);
    void checkCollisions(float deltaTime);
    void updateUI();
    void checkWinCondition();
    void initTexts();
    void loadTextures();
    void loadMusic();                    // ← AJOUTER CETTE LIGNE
    void updateHeartsDisplay();
    void showResultWindowFunction(const std::string& title, const std::string& message, int score);
    void centerText(sf::Text& text, float y);

public:
    Game();
    ~Game();

    void run();
    void processEvents();
    void update(float deltaTime);
    void render();

    void startGame(GameMode mode);
    void pauseGame();
    void resumeGame();
    void toggleMute();
    void exitToMenu();
};

#endif // GAME_H