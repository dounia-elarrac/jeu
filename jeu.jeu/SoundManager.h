#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>

/**
 * Classe SoundManager (Gestionnaire de sons)
 * Concept: Encapsulation (page 84-88)
 * Concept: Conteneur STL map (page 107-117)
 * Role: Gerer le chargement et la lecture des effets sonores
 */
class SoundManager {
private:
    // Attributs prives (encapsulation, page 84-88)
    std::map<std::string, sf::SoundBuffer> buffers;  // Tampons sonores (STL map)
    std::map<std::string, sf::Sound> sounds;         // Sons jouables (STL map)
    float volume;                                     // Volume general (0-100)
    bool muted;                                       // Etat muet

    // Methodes privees
    void updateAllVolumes();                          // Mettre a jour tous les volumes

public:
    // Constructeurs (page 45-56)
    SoundManager();                                   // Constructeur par defaut
    SoundManager(const SoundManager& autre);          // Constructeur de copie

    // Destructeur (page 57-60)
    ~SoundManager();

    // Operateur d'affectation (page 31-42)
    SoundManager& operator=(const SoundManager& autre);

    // Methodes publiques
    void loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void stopAllSounds();

    // Accesseurs (getters) - methodes const (page 25-26)
    float getVolume() const { return volume; }
    bool isMuted() const { return muted; }
    bool isSoundLoaded(const std::string& name) const;
    sf::Sound::Status getSoundStatus(const std::string& name) const;

    // Mutateurs (setters)
    void setVolume(float vol);
    void toggleMute();
    void setMute(bool mute);

    // Methodes specifiques
    void pauseAllSounds();
    void resumeAllSounds();
};

#endif