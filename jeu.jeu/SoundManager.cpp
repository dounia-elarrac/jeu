#include "SoundManager.h"
#include <iostream>

using namespace std;  // Espace de nom std (page 182-183)

// ------------------------------------------------------------------
// Constructeur par defaut (page 45-46, 51-53)
// Utilisation de la liste d'initialisation (page 48-50)
// ------------------------------------------------------------------
SoundManager::SoundManager()
    : volume(100.0f)
    , muted(false) {
    cout << "SoundManager initialise avec volume = " << volume << endl;
}

// ------------------------------------------------------------------
// Constructeur de copie (page 54-56)
// ------------------------------------------------------------------
SoundManager::SoundManager(const SoundManager& autre) {
    // Copie des attributs (page 54-56)
    this->buffers = autre.buffers;
    this->sounds = autre.sounds;
    this->volume = autre.volume;
    this->muted = autre.muted;
}

// ------------------------------------------------------------------
// Destructeur (page 57-60)
// ------------------------------------------------------------------
SoundManager::~SoundManager() {
    stopAllSounds();
    cout << "SoundManager detruit" << endl;
}

// ------------------------------------------------------------------
// Operateur d'affectation (page 31-42)
// ------------------------------------------------------------------
SoundManager& SoundManager::operator=(const SoundManager& autre) {
    // Verification d'auto-affectation (page 66-67)
    if (this != &autre) {
        this->buffers = autre.buffers;
        this->sounds = autre.sounds;
        this->volume = autre.volume;
        this->muted = autre.muted;
    }
    return *this;  // Retourne l'objet courant (page 66-67)
}

// ------------------------------------------------------------------
// Mise a jour de tous les volumes
// ------------------------------------------------------------------
void SoundManager::updateAllVolumes() {
    // Parcours de la map avec iterateur (page 114-115)
    for (map<string, sf::Sound>::iterator it = sounds.begin();
        it != sounds.end(); ++it) {
        if (muted) {
            it->second.setVolume(0.0f);
        }
        else {
            it->second.setVolume(volume);
        }
    }
}

// ------------------------------------------------------------------
// Chargement d'un son
// ------------------------------------------------------------------
void SoundManager::loadSound(const string& name, const string& filename) {
    sf::SoundBuffer buffer;

    // Tentative de chargement
    if (buffer.loadFromFile(filename)) {
        buffers[name] = buffer;
        sounds[name].setBuffer(buffers[name]);
        sounds[name].setVolume(muted ? 0.0f : volume);

        cout << "Son charge avec succes: " << name
            << " depuis " << filename << endl;
    }
    else {
        cerr << "Erreur: Impossible de charger le son "
            << name << " depuis " << filename << endl;
    }
}

// ------------------------------------------------------------------
// Lecture d'un son
// ------------------------------------------------------------------
void SoundManager::playSound(const string& name) {
    // Verification si le son existe (page 107-117 pour map)
    map<string, sf::Sound>::iterator it = sounds.find(name);

    if (it != sounds.end()) {
        // Ne pas jouer si muet
        if (muted) {
            return;
        }

        // Arreter le son s'il est deja en cours de lecture
        if (it->second.getStatus() == sf::Sound::Playing) {
            it->second.stop();
        }

        // Jouer le son
        it->second.play();
    }
    else {
        cerr << "Attention: Son '" << name << "' non trouve!" << endl;
    }
}

// ------------------------------------------------------------------
// Arret d'un son
// ------------------------------------------------------------------
void SoundManager::stopSound(const string& name) {
    // Verification si le son existe (page 107-117)
    map<string, sf::Sound>::iterator it = sounds.find(name);

    if (it != sounds.end()) {
        it->second.stop();
    }
}

// ------------------------------------------------------------------
// Arret de tous les sons
// ------------------------------------------------------------------
void SoundManager::stopAllSounds() {
    // Parcours de la map (page 114-115)
    for (map<string, sf::Sound>::iterator it = sounds.begin();
        it != sounds.end(); ++it) {
        it->second.stop();
    }
}

// ------------------------------------------------------------------
// Pause de tous les sons
// ------------------------------------------------------------------
void SoundManager::pauseAllSounds() {
    for (map<string, sf::Sound>::iterator it = sounds.begin();
        it != sounds.end(); ++it) {
        if (it->second.getStatus() == sf::Sound::Playing) {
            it->second.pause();
        }
    }
}

// ------------------------------------------------------------------
// Reprise de tous les sons
// ------------------------------------------------------------------
void SoundManager::resumeAllSounds() {
    if (!muted) {
        for (map<string, sf::Sound>::iterator it = sounds.begin();
            it != sounds.end(); ++it) {
            if (it->second.getStatus() == sf::Sound::Paused) {
                it->second.play();
            }
        }
    }
}

// ------------------------------------------------------------------
// Definition du volume (0-100)
// ------------------------------------------------------------------
void SoundManager::setVolume(float vol) {
    // Validation du volume (page 31-42 pour operateurs de comparaison)
    if (vol < 0.0f) {
        volume = 0.0f;
    }
    else if (vol > 100.0f) {
        volume = 100.0f;
    }
    else {
        volume = vol;
    }

    updateAllVolumes();
    cout << "Volume sonore defini a: " << volume << endl;
}

// ------------------------------------------------------------------
// Activation/desactivation du mode muet
// ------------------------------------------------------------------
void SoundManager::toggleMute() {
    muted = !muted;
    updateAllVolumes();

    if (muted) {
        cout << "Son desactive (mute)" << endl;
    }
    else {
        cout << "Son reactive (unmute)" << endl;
    }
}

// ------------------------------------------------------------------
// Definition du mode muet
// ------------------------------------------------------------------
void SoundManager::setMute(bool mute) {
    muted = mute;
    updateAllVolumes();
}

// ------------------------------------------------------------------
// Verification si un son est charge
// ------------------------------------------------------------------
bool SoundManager::isSoundLoaded(const string& name) const {
    // Utilisation de const_iterator car methode const (page 114-115)
    map<string, sf::Sound>::const_iterator it = sounds.find(name);
    return it != sounds.end();
}

// ------------------------------------------------------------------
// Obtention du statut d'un son
// ------------------------------------------------------------------
sf::Sound::Status SoundManager::getSoundStatus(const string& name) const {
    map<string, sf::Sound>::const_iterator it = sounds.find(name);

    if (it != sounds.end()) {
        return it->second.getStatus();
    }

    return sf::Sound::Stopped;
}