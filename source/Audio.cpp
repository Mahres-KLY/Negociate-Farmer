#include "Audio.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Audio::Audio() {
}

Audio::~Audio() {
    music.stop();
}

bool Audio::loadMusic(const string& filePath) {
    if (!music.openFromFile(filePath)) {
        cerr << "Erreur : impossible de charger la musique : " << filePath << endl;
        return false;
    }
    return true;
}

void Audio::playMusic(bool loop) {
    music.play();
    music.stop();
}


void Audio::stopMusic() { music.stop(); }

void Audio::setVolume(float volume) {
    if (volume < 0.f) volume = 0.f;
    if (volume > 100.f) volume = 100.f;
    music.setVolume(volume);
}
