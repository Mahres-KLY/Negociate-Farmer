#pragma once

#include <SFML/Audio.hpp>
#include <string>

using namespace std;
using namespace sf;

class Audio {
public:
    Audio();
    ~Audio();

    bool loadMusic(const string& filePath);
    void playMusic(bool loop = true);
    void stopMusic();
    void setVolume(float volume);

private:
    Music music;
};
