#include "EndScreen.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

EndScreen::EndScreen(RenderWindow* window)
    : m_window(window), m_fadeAlpha(0.f), m_isClosing(false) {

    // Chargement de la police
    if (!m_font.openFromFile("assets/fonts/arial.ttf")) {
        cerr << "Erreur : impossible de charger la police pour l'écran de fin !" << endl;
    }

    // Fond semi-transparent
    m_background.setSize(Vector2f(1280.f, 720.f));
    m_background.setFillColor(Color(0, 0, 0, 220));

    // Boîte du titre
    m_titleBox.setSize(Vector2f(1000.f, 150.f));
    m_titleBox.setPosition(Vector2f(140.f, 100.f));
    m_titleBox.setOutlineThickness(3.f);

    // Texte du titre
    m_titleText.setFont(m_font);
    m_titleText.setCharacterSize(60);
    m_titleText.setStyle(sf::Text::Bold);

    // Texte de description
    m_descriptionText.setFont(m_font);
    m_descriptionText.setCharacterSize(24);
    m_descriptionText.setFillColor(Color::White);
    m_descriptionText.setPosition(Vector2f(200.f, 320.f));

    // Texte des scores
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(28);
    m_scoreText.setFillColor(Color(200, 200, 200));
    m_scoreText.setStyle(sf::Text::Bold);

    // Instructions
    m_instructionText.setFont(m_font);
    m_instructionText.setCharacterSize(20);
    m_instructionText.setFillColor(Color(150, 150, 150));
    m_instructionText.setString("Appuie sur ENTREE pour quitter");
    m_instructionText.setPosition(Vector2f(450.f, 630.f));
}

void EndScreen::setEnding(EndingType type, int pointsA, int pointsB) {
    m_endingType = type;
    m_pointsA = pointsA;
    m_pointsB = pointsB;

    setupTexts();
}

void EndScreen::setupTexts() {
    // Configuration du titre
    string title = getEndingTitle(m_endingType);
    m_titleText.setString(title);

    Color endingColor = getEndingColor(m_endingType);
    m_titleText.setFillColor(endingColor);
    m_titleBox.setFillColor(Color(endingColor.r / 4, endingColor.g / 4, endingColor.b / 4, 200));
    m_titleBox.setOutlineColor(endingColor);

    // Centrer le titre dans la boîte
    FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setPosition(
        Vector2f(640.f - titleBounds.size.x / 2.f,
            150.f)
    );

    // Configuration de la description
    string description = getEndingDescription(m_endingType);
    m_descriptionText.setString(description);

    // Configuration des scores
    string scoreString = "=== SCORES FINAUX ===\n\n";
    scoreString += "Famille Albert (Bleu) : " + to_string(m_pointsA) + " points\n";
    scoreString += "Famille Beatrice (Vert) : " + to_string(m_pointsB) + " points\n\n";

    int diff = abs(m_pointsA - m_pointsB);
    if (diff > 0) {
        scoreString += "Difference : " + to_string(diff) + " points";
    }
    else {
        scoreString += "Parfait equilibre !";
    }

    m_scoreText.setString(scoreString);
    m_scoreText.setPosition(Vector2f(350.f, 450.f));
}

string EndScreen::getEndingTitle(EndingType type) {
    switch (type) {
    case EndingType::FAMILLE_A_WIN:
        return "VICTOIRE DE LA FAMILLE ALBERT !";
    case EndingType::FAMILLE_B_WIN:
        return "VICTOIRE DE LA FAMILLE BEATRICE !";
    case EndingType::PARTAGE_EQUITABLE:
        return "PAIX ET PROSPERITE !";
    case EndingType::PLAYER_TAKEOVER:
        return "NOUVELLE ERE !";
    default:
        return "FIN";
    }
}

string EndScreen::getEndingDescription(EndingType type) {
    switch (type) {
    case EndingType::FAMILLE_A_WIN:
        return "Grace a tes choix, la Famille Albert a pris le controle total de la ferme.\n"
            "Maitre Albert reorganise les terres selon sa vision.\n"
            "La Famille Beatrice accepte sa defaite et quitte les lieux.\n\n"
            "La ferme prospere sous un commandement unique,\n"
            "mais certains regrettent la diversite d'autrefois...";

    case EndingType::FAMILLE_B_WIN:
        return "Tes decisions ont permis a la Famille Beatrice de triompher !\n"
            "Maitresse Beatrice prend les renes et instaure de nouvelles regles.\n"
            "La Famille Albert se retire, deçue mais respectueuse.\n\n"
            "Une nouvelle ere commence sous la banniere verte,\n"
            "portant espoir et changement pour la ferme.";

    case EndingType::PARTAGE_EQUITABLE:
        return "Ta sagesse a permis de reconcilier les deux familles !\n"
            "Albert et Beatrice acceptent de partager equitablement la ferme.\n"
            "Les terres sont divisees avec justice et respect mutuel.\n\n"
            "Les deux clans travaillent desormais cote a cote,\n"
            "construisant ensemble un avenir prospere pour tous.";

    case EndingType::PLAYER_TAKEOVER:
        return "Ton intervention a bouleverse l'ordre etabli !\n"
            "Ni Albert ni Beatrice n'ont su convaincre...\n"
            "Les fermiers se tournent vers toi comme nouveau leader.\n\n"
            "Tu prends le controle de la ferme entiere,\n"
            "unifiant les deux familles sous ta direction.";

    default:
        return "Merci d'avoir joue !";
    }
}

Color EndScreen::getEndingColor(EndingType type) {
    switch (type) {
    case EndingType::FAMILLE_A_WIN:
        return Color(100, 150, 255);  // Bleu
    case EndingType::FAMILLE_B_WIN:
        return Color(100, 255, 100);  // Vert
    case EndingType::PARTAGE_EQUITABLE:
        return Color(255, 215, 0);    // Or (paix)
    case EndingType::PLAYER_TAKEOVER:
        return Color(200, 100, 255);  // Violet (pouvoir)
    default:
        return Color::White;
    }
}

void EndScreen::run() {
    m_animationClock.restart();

    while (m_window->isOpen() && !m_isClosing) {
        handleInput();
        render();
    }
}

void EndScreen::handleInput() {
    while (auto event = m_window->pollEvent()) {
        if (event->is<Event::Closed>()) {
            m_window->close();
            m_isClosing = true;
        }
        else if (event->is<Event::KeyPressed>()) {
            auto keyEvent = event->getIf<Event::KeyPressed>();
            if (keyEvent->code == Keyboard::Key::Enter ||
                keyEvent->code == Keyboard::Key::Escape) {
                m_isClosing = true;
                m_window->close();
            }
        }
    }
}

void EndScreen::render() {
    m_window->clear(Color(20, 20, 30));

    // Animation de fade-in
    float elapsed = m_animationClock.getElapsedTime().asSeconds();
    if (m_fadeAlpha < 255.f) {
        m_fadeAlpha = min(255.f, elapsed * 200.f);
    }

    // Fond
    Color bgColor = m_background.getFillColor();
    bgColor.a = static_cast<uint8_t>(m_fadeAlpha * 0.86f);
    m_background.setFillColor(bgColor);
    m_window->draw(m_background);

    // Boîte titre avec animation
    if (elapsed > 0.5f) {
        Color boxColor = m_titleBox.getFillColor();
        boxColor.a = static_cast<uint8_t>(min(200.f, (elapsed - 0.5f) * 300.f));
        m_titleBox.setFillColor(boxColor);

        Color outlineColor = m_titleBox.getOutlineColor();
        outlineColor.a = static_cast<uint8_t>(min(255.f, (elapsed - 0.5f) * 400.f));
        m_titleBox.setOutlineColor(outlineColor);

        m_window->draw(m_titleBox);
    }

    // Titre avec animation
    if (elapsed > 0.8f) {
        Color titleColor = m_titleText.getFillColor();
        titleColor.a = static_cast<uint8_t>(min(255.f, (elapsed - 0.8f) * 400.f));
        m_titleText.setFillColor(titleColor);
        m_window->draw(m_titleText);
    }

    // Description avec animation
    if (elapsed > 1.2f) {
        Color descColor = m_descriptionText.getFillColor();
        descColor.a = static_cast<uint8_t>(min(255.f, (elapsed - 1.2f) * 300.f));
        m_descriptionText.setFillColor(descColor);
        m_window->draw(m_descriptionText);
    }

    // Scores avec animation
    if (elapsed > 1.6f) {
        Color scoreColor = m_scoreText.getFillColor();
        scoreColor.a = static_cast<uint8_t>(min(255.f, (elapsed - 1.6f) * 300.f));
        m_scoreText.setFillColor(scoreColor);
        m_window->draw(m_scoreText);
    }

    // Instructions clignotantes
    if (elapsed > 2.0f) {
        float blink = sin(elapsed * 3.f) * 0.5f + 0.5f;
        Color instrColor = m_instructionText.getFillColor();
        instrColor.a = static_cast<uint8_t>(150.f * blink);
        m_instructionText.setFillColor(instrColor);
        m_window->draw(m_instructionText);
    }

    m_window->display();
}
