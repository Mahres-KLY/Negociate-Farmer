#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "Player.hpp"
#include "MapLoader.hpp"
#include "EndScreen.hpp"

using namespace sf;
using namespace std;

// Énumération pour les familles
enum class Clan {
    NONE,
    FAMILLE_A,  // Famille de gauche
    FAMILLE_B   // Famille de droite
};

// Structure pour un choix de dialogue
struct Choice {
    string text;
    Clan affecte;  // Quelle famille est affectée par ce choix
    int points;    // Points donnés (+1 ou -1)
};

// Structure pour un dialogue
struct Dialogue {
    string speaker;
    string text;
    vector<Choice> choices;
    bool isEndDialogue = false;
};

struct NPC {
    RectangleShape shape;
    string name;
    string id;  // Identifiant unique
    bool isMainNPC = false;
    Clan clan;
    bool isBoss = false;
    bool hasBeenTalkedTo = false;
    vector<Dialogue> dialogues;
    int currentDialogueIndex = 0;

    NPC(Vector2f pos, string name, string id, Clan clan = Clan::NONE, bool main = false, bool boss = false) {
        shape.setSize(Vector2f(40, 60));
        shape.setPosition(pos);
        this->name = name;
        this->id = id;
        this->clan = clan;
        this->isMainNPC = main;
        this->isBoss = boss;

        // Couleur selon le type
        if (main) shape.setFillColor(Color::Yellow);
        else if (boss) shape.setFillColor(Color::Red);
        else if (clan == Clan::FAMILLE_A) shape.setFillColor(Color::Blue);
        else if (clan == Clan::FAMILLE_B) shape.setFillColor(Color::Green);
        else shape.setFillColor(Color::White);
    }
};

class Gameplay {
private:
    RenderWindow* m_window;
    Player m_player;
    MapLoader m_map;
    vector<NPC> m_npcs;
    Font m_font;

    // Utilisation de unique_ptr pour les Text (évite le problème de constructeur par défaut)
    unique_ptr<Text> m_promptText;
    unique_ptr<Text> m_dialogueText;
    vector<unique_ptr<Text>> m_choiceTexts;

    RectangleShape m_dialogueBox;
    vector<RectangleShape> m_choiceBoxes;

    // États du jeu
    bool inDialogue = false;
    bool inMiniGame = false;
    bool gameEnded = false;
    NPC* currentNPC = nullptr;
    int selectedChoice = 0;

    // Progression
    map<string, bool> npcsTalkedTo;
    int pointsFamilleA = 0;
    int pointsFamilleB = 0;

    // Méthodes privées
    void initializeNPCs();
    void loadDialogues();
    bool canTalkToBoss(const NPC& boss);
    void startDialogue(NPC& npc);
    void handleDialogueInput();
    void selectChoice(int choiceIndex);
    void endDialogue();
    void checkGameEnd();
    void renderDialogue();

public:
    Gameplay(RenderWindow* window);
    void run();
    void handleInput();
    void update();
    void render();
};
