#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

enum class EndingType {
    FAMILLE_A_WIN,      // Famille Albert gagne
    FAMILLE_B_WIN,      // Famille Béatrice gagne
    PARTAGE_EQUITABLE,  // Partage équitable
    PLAYER_TAKEOVER     // Le joueur prend le contrôle
};

class EndScreen {
private:
    RenderWindow* m_window;
    Font m_font;
    Text m_titleText;
    Text m_descriptionText;
    Text m_scoreText;
    Text m_instructionText;
    RectangleShape m_background;
    RectangleShape m_titleBox;

    EndingType m_endingType;
    int m_pointsA;
    int m_pointsB;

    Clock m_animationClock;
    float m_fadeAlpha;
    bool m_isClosing;

public:
    EndScreen(RenderWindow* window);
    void setEnding(EndingType type, int pointsA, int pointsB);
    void run();
    void render();
    void handleInput();

private:
    void setupTexts();
    string getEndingTitle(EndingType type);
    string getEndingDescription(EndingType type);
    Color getEndingColor(EndingType type);
};