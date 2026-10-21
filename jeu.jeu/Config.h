#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <string>

namespace GameConstants {
    // Screen
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int WORLD_WIDTH = 10000;
    const int WORLD_HEIGHT = 600;

    // Camera
    const float CAMERA_SMOOTHNESS = 0.1f;
    const float CAMERA_MIN_X = 400;
    const float CAMERA_MAX_X = WORLD_WIDTH - 400;
    const float CAMERA_MIN_Y = 300;
    const float CAMERA_MAX_Y = 500;

    // Player
    const float PLAYER_START_X = 100.0f;
    const float PLAYER_START_Y = 500.0f;
    const float PLAYER_WIDTH = 32.0f;
    const float PLAYER_HEIGHT = 32.0f;
    const float PLAYER_WIDTH_BIG = 40.0f;
    const float PLAYER_HEIGHT_BIG = 48.0f;
    const float PLAYER_SPEED_NORMAL = 200.0f;
    const float PLAYER_SPEED_BOOSTED = 350.0f;
    const float PLAYER_JUMP_FORCE = -550.0f;
    const float PLAYER_GRAVITY = 1000.0f;
    const int PLAYER_MAX_HEARTS = 5;

    // Ground
    const float GROUND_LEVEL = 550.0f;

    // Game
    const float TIME_LIMIT = 120.0f;
    const float INVINCIBILITY_DURATION = 1.5f;
    const float SPEED_BOOST_DURATION = 5.0f;
    const float BOUNCE_FORCE = -600.0f;
    const float GOAL_X = 9500.0f;

    // Coins
    const int COIN_COUNT = 50;
    const int COIN_POINTS = 100;
    const int COINS_FOR_EXTRA_LIFE = 20;

    // PowerUp
    const int POWERUP_POINTS_GROWTH = 500;
    const int POWERUP_POINTS_SPEED = 500;
    const int POWERUP_POINTS_HEALTH = 500;

    // Platform
    const float PLATFORM_WIDTH = 80.0f;
    const float PLATFORM_HEIGHT = 30.0f;

    // FireBall
    const float FIREBALL_SPEED = 300.0f;
}

// Colors (pour les formes - à supprimer progressivement)
namespace GameConstants {
    namespace Colors {
        // Player
        const sf::Color PLAYER_NORMAL(255, 0, 0);
        const sf::Color PLAYER_BIG(255, 100, 0);
        const sf::Color PLAYER_HAT(200, 0, 0);

        // Enemy
        const sf::Color ENEMY_GROUND(150, 75, 0);
        const sf::Color ENEMY_FLYING(100, 100, 150);
        const sf::Color BAT(80, 40, 80);
        const sf::Color GHOST(200, 200, 220);
        const sf::Color SPIDER(80, 40, 40);
        const sf::Color ZOMBIE(40, 80, 40);
        const sf::Color WIZARD(0, 0, 100);
        const sf::Color FLYING_EYE(150, 50, 150);
        const sf::Color WEREWOLF(100, 50, 20);

        // Platform
        const sf::Color PLATFORM_NORMAL(139, 69, 19);
        const sf::Color PLATFORM_BOUNCY(255, 200, 0);
        const sf::Color PLATFORM_OUTLINE(100, 50, 10);

        // Water
        const sf::Color WATER(0, 100, 200, 150);

        // PowerUp
        const sf::Color POWERUP_GROWTH(255, 100, 0);
        const sf::Color POWERUP_SPEED(0, 255, 0);
        const sf::Color POWERUP_HEALTH(255, 0, 0);

        // Coin
        const sf::Color COIN(255, 215, 0);
        const sf::Color COIN_OUTLINE(200, 150, 0);

        // Background
        const sf::Color SKY_DAY(135, 206, 235);
        const sf::Color SKY_NIGHT(25, 25, 50);
    }
}

// Texture Paths
namespace TexturePaths {
    const std::string HEART = "textures/heart.png";
    const std::string BTN_MUTE = "textures/btn_mute.png";
    const std::string BTN_PAUSE = "textures/btn_pause.png";
    const std::string BTN_MENU = "textures/btn_menu.png";
    const std::string BTN_ABOUT = "textures/btn_about.png";
    const std::string BTN_PLAY = "textures/btn_play.png";
}

// Sound Paths
namespace SoundPaths {
    // Sound effects
    const std::string JUMP = "sounds/jump.mp3";
    const std::string COIN = "sounds/coin.mp3";
    const std::string HIT = "sounds/hit.mp3";
    const std::string STOMP = "sounds/stomp.mp3";
    const std::string GAMEOVER = "sounds/gameover.mp3";
    const std::string VICTORY = "sounds/victory.mp3";
    const std::string POWERUP = "sounds/powerup.mp3";

    // Background music
    const std::string BACKGROUND_MUSIC_DAY = "sounds/background_music_day.mp3";
    const std::string BACKGROUND_MUSIC_NIGHT = "sounds/background_music_night.mp3";
}

#endif // CONFIG_H