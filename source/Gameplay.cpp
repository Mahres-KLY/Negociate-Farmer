#include "Gameplay.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Gameplay::Gameplay(RenderWindow* window) : m_window(window) {
    m_player = Player();

    // Chargement de la map TMX
    if (!m_map.load("assets/World/MapFarmers.tmx", "assets/environments/tilemap_packed.png")) {
        cout << "Erreur : impossible de charger la map !" << endl;
    }

    // Initialisation des NPCs
    initializeNPCs();

    // Chargement des dialogues
    loadDialogues();

    // Police
    if (!m_font.openFromFile("assets/fonts/arial.ttf")) {
        cerr << "Erreur chargement police !" << endl;
    }

    // Texte de prompt (près du joueur)
    m_promptText = Text(m_font);
    m_promptText.setCharacterSize(18);
    m_promptText.setFillColor(Color::White);
    m_promptText.setString("");

    // Boîte de dialogue
    m_dialogueBox.setSize(Vector2f(1000.f, 200.f));
    m_dialogueBox.setPosition(Vector2f(140.f, 480.f));
    m_dialogueBox.setFillColor(Color(0, 0, 0, 200));
    m_dialogueBox.setOutlineColor(Color::White);
    m_dialogueBox.setOutlineThickness(2.f);

    // Texte de dialogue
    m_dialogueText = Text(m_font);
    m_dialogueText.setCharacterSize(20);
    m_dialogueText.setFillColor(Color::White);

    // Textes de choix (max 3 choix)
    for (int i = 0; i < 3; ++i) {
        Text choiceText(m_font);
        choiceText.setCharacterSize(18);
        choiceText.setFillColor(Color::White);
        m_choiceTexts.push_back(choiceText);

        RectangleShape choiceBox;
        choiceBox.setSize(Vector2f(960.f, 50.f));
        choiceBox.setFillColor(Color(50, 50, 50, 200));
        choiceBox.setOutlineColor(Color::White);
        choiceBox.setOutlineThickness(1.f);
        m_choiceBoxes.push_back(choiceBox);
    }
}

void Gameplay::initializeNPCs() {
    // PNJ principal (Voyageur neutre)
    m_npcs.emplace_back(Vector2f(640, 360), "Voyageur", "voyageur", Clan::NONE, true, false);

    // Famille A (Bleu) - 2 fermiers + 1 boss
    m_npcs.emplace_back(Vector2f(300, 200), "Jean le Fermier", "fermier_a1", Clan::FAMILLE_A);
    m_npcs.emplace_back(Vector2f(400, 250), "Marie la Fermière", "fermiere_a1", Clan::FAMILLE_A);
    m_npcs.emplace_back(Vector2f(200, 150), "Maître Albert", "boss_a", Clan::FAMILLE_A, false, true);

    // Famille B (Vert) - 2 fermiers + 1 boss
    m_npcs.emplace_back(Vector2f(900, 200), "Pierre le Fermier", "fermier_b1", Clan::FAMILLE_B);
    m_npcs.emplace_back(Vector2f(800, 250), "Sophie la Fermière", "fermiere_b1", Clan::FAMILLE_B);
    m_npcs.emplace_back(Vector2f(1000, 150), "Maîtresse Béatrice", "boss_b", Clan::FAMILLE_B, false, true);
}

void Gameplay::loadDialogues() {
    // VOYAGEUR (introduction sans choix)
    Dialogue intro;
    intro.speaker = "Voyageur";
    intro.text = "Bienvenue, jeune voyageur. Cette ferme est déchirée par deux familles rivales depuis des années. \nLa Famille Albert à l'ouest (bleu) et la Famille Béatrice à l'est (vert) se disputent le contrôle total. \nVa leur parler et trouve une solution. Bonne chance !";
    intro.isEndDialogue = true;
    m_npcs[0].dialogues.push_back(intro);

    // FERMIER A1 - Jean
    Dialogue jeanD1;
    jeanD1.speaker = "Jean";
    jeanD1.text = "Ah, un nouveau venu ! Écoute, notre famille travaille ces terres depuis des générations. \nCes vauriens de l'est veulent tout nous prendre !";
    jeanD1.choices = {
        {"Vous avez raison, ils semblent injustes.", Clan::FAMILLE_A, 1},
        {"Peut-être pouvez-vous partager ?", Clan::NONE, 0},
        {"Les terres devraient revenir aux plus forts.", Clan::FAMILLE_B, -1}
    };
    m_npcs[1].dialogues.push_back(jeanD1);

    // FERMIÈRE A1 - Marie
    Dialogue marieD1;
    marieD1.speaker = "Marie";
    marieD1.text = "Notre Maître Albert est un homme juste. Si seulement cette Béatrice pouvait l'admettre... \nQue penses-tu de tout ça ?";
    marieD1.choices = {
        {"Albert mérite de diriger cette ferme.", Clan::FAMILLE_A, 1},
        {"Vous devriez trouver un compromis équitable.", Clan::NONE, 0},
        {"Béatrice semble plus compétente.", Clan::FAMILLE_B, -1}
    };
    m_npcs[2].dialogues.push_back(marieD1);

    // FERMIER B1 - Pierre
    Dialogue pierreD1;
    pierreD1.speaker = "Pierre";
    pierreD1.text = "Salut l'étranger ! Tu vois cette terre ? C'est nous qui la rendons fertile ! \nCette famille de l'ouest ne fait que se plaindre !";
    pierreD1.choices = {
        {"Vous avez l'air de travailleurs acharnés.", Clan::FAMILLE_B, 1},
        {"Chacun a sa part de mérite ici.", Clan::NONE, 0},
        {"La famille de l'ouest semble plus légitime.", Clan::FAMILLE_A, -1}
    };
    m_npcs[4].dialogues.push_back(pierreD1);

    // FERMIÈRE B1 - Sophie
    Dialogue sophieD1;
    sophieD1.speaker = "Sophie";
    sophieD1.text = "Notre Maîtresse Béatrice est la plus sage. Elle saurait gérer toute la ferme. \nQu'en dis-tu ?";
    sophieD1.choices = {
        {"Béatrice devrait diriger seule.", Clan::FAMILLE_B, 1},
        {"Une gestion partagée serait mieux.", Clan::NONE, 0},
        {"Albert est plus qualifié.", Clan::FAMILLE_A, -1}
    };
    m_npcs[5].dialogues.push_back(sophieD1);

    // BOSS A - Maître Albert
    Dialogue albertD1;
    albertD1.speaker = "Maître Albert";
    albertD1.text = "Alors, tu as parlé à mes gens. Que proposes-tu ? Cette ferme doit avoir un seul maître !";
    albertD1.choices = {
        {"Vous devez diriger seul, Maître Albert.", Clan::FAMILLE_A, 2},
        {"Partagez le territoire équitablement avec Béatrice.", Clan::NONE, 0},
        {"Je prendrai le contrôle pour pacifier les lieux.", Clan::NONE, 0}
    };
    m_npcs[3].dialogues.push_back(albertD1);

    // BOSS B - Maîtresse Béatrice
    Dialogue beatriceD1;
    beatriceD1.speaker = "Maîtresse Béatrice";
    beatriceD1.text = "Tu as interrogé mes fermiers. Alors, quelle est ta décision ? Cette terre mérite un vrai chef !";
    beatriceD1.choices = {
        {"Vous devez gouverner seule, Maîtresse.", Clan::FAMILLE_B, 2},
        {"Divisez les terres équitablement avec Albert.", Clan::NONE, 0},
        {"Je prendrai les commandes pour restaurer la paix.", Clan::NONE, 0}
    };
    m_npcs[6].dialogues.push_back(beatriceD1);
}

bool Gameplay::canTalkToBoss(const NPC& boss) {
    int farmersSpokenTo = 0;
    for (const auto& npc : m_npcs) {
        if (npc.clan == boss.clan && !npc.isBoss && !npc.isMainNPC) {
            if (npcsTalkedTo[npc.id]) {
                farmersSpokenTo++;
            }
        }
    }
    return farmersSpokenTo >= 2;
}

void Gameplay::startDialogue(NPC& npc) {
    if (npc.currentDialogueIndex >= npc.dialogues.size()) {
        return;
    }

    currentNPC = &npc;
    inDialogue = true;
    selectedChoice = 0;

    Dialogue& currentDialogue = npc.dialogues[npc.currentDialogueIndex];
    m_dialogueText.setString(currentDialogue.speaker + ": " + currentDialogue.text);
    m_dialogueText.setPosition(Vector2f(160.f, 500.f));

    if (currentDialogue.choices.empty() || currentDialogue.isEndDialogue) {
        // Dialogue informatif
    }
    else {
        for (size_t i = 0; i < currentDialogue.choices.size(); ++i) {
            m_choiceTexts[i].setString(to_string(i + 1) + ". " + currentDialogue.choices[i].text);
            m_choiceTexts[i].setPosition(Vector2f(180.f, 550.f + i * 60.f));

            m_choiceBoxes[i].setPosition(Vector2f(160.f, 545.f + i * 60.f));
            m_choiceBoxes[i].setOutlineColor(i == selectedChoice ? Color::Yellow : Color::White);
        }
    }
}

void Gameplay::handleDialogueInput() {
    if (!inDialogue || !currentNPC) return;

    Dialogue& currentDialogue = currentNPC->dialogues[currentNPC->currentDialogueIndex];

    if (currentDialogue.choices.empty() || currentDialogue.isEndDialogue) {
        if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
            endDialogue();
        }
        return;
    }

    static bool upPressed = false;
    static bool downPressed = false;

    if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
        if (!upPressed) {
            selectedChoice = (selectedChoice - 1 + currentDialogue.choices.size()) % currentDialogue.choices.size();
            upPressed = true;
        }
    }
    else {
        upPressed = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
        if (!downPressed) {
            selectedChoice = (selectedChoice + 1) % currentDialogue.choices.size();
            downPressed = true;
        }
    }
    else {
        downPressed = false;
    }

    static bool ePressed = false;
    if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
        if (!ePressed) {
            selectChoice(selectedChoice);
            ePressed = true;
        }
    }
    else {
        ePressed = false;
    }

    for (size_t i = 0; i < currentDialogue.choices.size(); ++i) {
        m_choiceBoxes[i].setOutlineColor(i == selectedChoice ? Color::Yellow : Color::White);
    }
}

void Gameplay::selectChoice(int choiceIndex) {
    if (!currentNPC) return;

    Dialogue& currentDialogue = currentNPC->dialogues[currentNPC->currentDialogueIndex];
    if (choiceIndex >= currentDialogue.choices.size()) return;

    Choice& choice = currentDialogue.choices[choiceIndex];

    if (choice.affecte == Clan::FAMILLE_A) {
        pointsFamilleA += choice.points;
    }
    else if (choice.affecte == Clan::FAMILLE_B) {
        pointsFamilleB += choice.points;
    }

    cout << "Choix fait ! Points A: " << pointsFamilleA << " | Points B: " << pointsFamilleB << endl;

    endDialogue();
}

void Gameplay::endDialogue() {
    if (!currentNPC) return;

    npcsTalkedTo[currentNPC->id] = true;
    currentNPC->hasBeenTalkedTo = true;
    currentNPC->currentDialogueIndex++;

    if (currentNPC->isBoss) {
        checkGameEnd();
    }

    inDialogue = false;
    currentNPC = nullptr;
}

void Gameplay::checkGameEnd() {
    bool bothBossesTalked = npcsTalkedTo["boss_a"] && npcsTalkedTo["boss_b"];

    if (!bothBossesTalked) return;

    // Déterminer le type de fin
    EndingType ending;
    if (pointsFamilleA > pointsFamilleB + 2) {
        ending = EndingType::FAMILLE_A_WIN;
    }
    else if (pointsFamilleB > pointsFamilleA + 2) {
        ending = EndingType::FAMILLE_B_WIN;
    }
    else if (abs(pointsFamilleA - pointsFamilleB) <= 2) {
        ending = EndingType::PARTAGE_EQUITABLE;
    }
    else {
        ending = EndingType::PLAYER_TAKEOVER;
    }

    cout << "\n========================================\n";
    cout << "FIN DU JEU !" << endl;
    cout << "Points Famille A: " << pointsFamilleA << endl;
    cout << "Points Famille B: " << pointsFamilleB << endl;
    cout << "========================================\n";

    // Afficher l'écran de fin
    gameEnded = true;
    EndScreen endScreen(m_window);
    endScreen.setEnding(ending, pointsFamilleA, pointsFamilleB);
    endScreen.run();
}

void Gameplay::run() {
    Clock clock;
    while (m_window->isOpen() && !gameEnded) {
        float deltaTime = clock.restart().asSeconds();
        handleInput();

        if (!inDialogue) {
            m_player.update(deltaTime);
        }

        update();
        render();
    }
}

void Gameplay::handleInput() {
    while (auto event = m_window->pollEvent()) {
        if (event->is<Event::Closed>())
            m_window->close();
    }

    if (inDialogue) {
        handleDialogueInput();
    }
}

void Gameplay::update() {
    if (inDialogue) return;

    bool nearNPC = false;
    for (auto& npc : m_npcs) {
        if (m_player.getBounds().findIntersection(npc.shape.getGlobalBounds()).has_value()) {
            nearNPC = true;

            if (npc.isBoss && !canTalkToBoss(npc)) {
                m_promptText.setString("Tu dois d'abord parler aux fermiers de cette famille !");
                m_promptText.setPosition(Vector2f(m_player.getPosition().x - 150, m_player.getPosition().y - 40));
                break;
            }

            if (npc.isMainNPC) {
                m_promptText.setString("Appuie sur E pour parler à " + npc.name);
            }
            else {
                m_promptText.setString("Appuie sur E pour parler avec " + npc.name);
            }
            m_promptText.setPosition(Vector2f(m_player.getPosition().x - 100, m_player.getPosition().y - 40));

            static bool ePressed = false;
            if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
                if (!ePressed) {
                    if (npc.isBoss && canTalkToBoss(npc)) {
                        startDialogue(npc);
                    }
                    else if (!npc.isBoss) {
                        startDialogue(npc);
                    }
                    ePressed = true;
                }
            }
            else {
                ePressed = false;
            }

            break;
        }
    }

    if (!nearNPC) {
        m_promptText.setString("");
    }
}

void Gameplay::render() {
    m_window->clear(Color(40, 40, 40));

    m_window->draw(m_map);

    for (auto& npc : m_npcs) {
        m_window->draw(npc.shape);
    }

    m_player.draw(*m_window);

    m_window->draw(m_promptText);

    if (inDialogue) {
        renderDialogue();
    }

    m_window->display();
}

void Gameplay::renderDialogue() {
    if (!currentNPC) return;

    m_window->draw(m_dialogueBox);
    m_window->draw(m_dialogueText);

    Dialogue& currentDialogue = currentNPC->dialogues[currentNPC->currentDialogueIndex];
    if (!currentDialogue.choices.empty() && !currentDialogue.isEndDialogue) {
        for (size_t i = 0; i < currentDialogue.choices.size(); ++i) {
            m_window->draw(m_choiceBoxes[i]);
            m_window->draw(m_choiceTexts[i]);
        }
    }
    else {
        Text continueText(m_font);
        continueText.setCharacterSize(16);
        continueText.setFillColor(Color(200, 200, 200));
        continueText.setString("Appuie sur E pour continuer...");
        continueText.setPosition(Vector2f(940.f, 650.f));
        m_window->draw(continueText);
    }
}
