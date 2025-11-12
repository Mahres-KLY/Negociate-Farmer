<<==============================    FARM'S WAR    ==============================>>

CONTEXTE HISTORIQUE:
Aurore était autrefoit une terre riche pour ses récoltes. Mais depuis que deux grandes familles sont arrivés pour ce territoire, un conflit qui dura pendant des années est né.
Les deux grandes familles se disputent le contrôle de la ferme entière, chacun affirmant en être le véritable propriétaire. Ce qui devait être une simple querelle de voisinage s’est transformé en tension permanente : menaces, sabotages, rumeurs…
Un simple passant, à l'apparance d'un voyageur, arrive par hasard dans ce chaos. Rapidement, il se retrouve impliqué malgré lui. 
Le sort de ce territoire et des deux familles se retrouvent soudainement entre ses mains car seul ses choix auront un impact sur la fin de ce conflit..


TYPE DE JEU:
En 2 dimensions -> Vue de dessus
Jeu à choix inspiré de The Secret Of Monkey Island, Assassin's Creed Valhalla,..
3 Fins différentes - Domination d'une des deux familles sur l'autre et donc la ferme entiere
                   - Partage équitable entre les deux familles, ce qui n'a aucun impact sur la situation
                   - Domination du joueur sur les 2 familles et donc de la ferme entière

MECHANIQUES:
Le joueur peut Avancer(Z), Reculer(S), Aller à Droite(D), Aller à Gauche(Q), Interagir(E) et faire des Choix(Num1, Num2 ou Num3)

OUTILS DE DEVELOPPEMENT:
VISUAL STUDIO 2022 (C++)
SFML 3.0.2 https://www.sfml-dev.org/download/sfml/3.0.2/
TILEMAP (assets Tiny Town) https://kenney.nl/assets/tiny-town

PROPRIETE & INSTALLATION DES FICHIERS POUR SFML 3.0.2:
Copie des fichiers sfml- se trouvant dans le fichier bin de l'installation de SFML 3.0.2 vers x64 -> Release, du projet

Propriétés de configuration -> Général -> Norme de langage C++ = Norme ISO C++ 17 (/std:c++17)
C/C++ -> Général-> Autres répertoires Include = C:\SFML-3.0.2\include;$(ProjectDir)\include;%(AdditionalIncludeDirectories)
      -> Processeur -> Définition de préproprecesseur = _DEBUG;_CONSOLE;%(PreprocessorDefinitions)
      -> Langage -> Norme de langage C++ = Norme ISO C++ 17 (/std:c++17)
      -> Toutes les options -> Autres répertoires Include = C:\SFML-3.0.2\include;$(ProjectDir)\include;%(AdditionalIncludeDirectories)
                            -> Définition de préproprecesseur = _DEBUG;_CONSOLE;%(PreprocessorDefinitions)
Editeur de liens -> Général -> Répertoires de bibliothèques supplémentaires = C:\SFML-3.0.2\lib
                 -> entrée -> Dépendances supplémentaires = sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;%(AdditionalDependencies)
                 -> Toutes les options -> Dépendances supplémentaires = sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;%(AdditionalDependencies)
                                       -> Répertoires de bibliothèques supplémentaires = C:\SFML-3.0.2\lib

PARTIES CODE:
Syncronisation entre les différentes fenêtres: main.cpp
Page de lancement : Start.cpp + Start.hpp
Fenetre de jeu : Gameplay.cpp + Gameplay.hpp

Autres: World.cpp/.hpp , MapLoader.cpp/.hpp , Player.cpp/.hpp , Audio.cpp/hpp


Start.hpp:
Classe(s) utilisée(s): Start
En accès PRIVATE: Texture -> l'image en fond de l'image d'accuille & unique_ptr<Sprite> pour la dimension en 2D
En accès PUBLIC: RenderWindow -> le rendu de la fenêtre 
                 Font -> la Police du boutton de lancement (arial)
                 RectangleShape -> la forme du boutton (rectangle comme le nom l'indique)
                 unique_ptr<Text> -> Position du Texte "Play" dans le boutton





MapLoader.hpp:
Classe(s) utilisée(s) : MapLoader
En accès PRIVATE : vector<Texture> m_tilesets -> contient toutes les textures utilisées pour afficher la carte (le "tileset/calque" = planche d’images pour le sol, les murs, etc.).
                   VertexArray m_vertices -> tableau de sommets graphiques utilisé par SFML pour dessiner la carte sous forme de tuiles (meilleures performances qu’un sprite par tuile).

En accès PUBLIC : bool load(const string& tmxFile, const string& tilesetPath) -> charge la map (.tmx) et les images associées (tilesets/calques).
                  void draw(RenderTarget& target, RenderStates states) const override -> Elle affiche le contenu du VertexArray. C'est une méthode de dessin appelée par SFML 3.0.2 lorsqu’on fait window.draw(m_map);




                  
Gameplay.hpp:
enum class Clan : Sert à identifier à quel camp/famille appartient un personnage du jeu: NONE = aucun clan
                                                                                         FAMILLE_A, FAMILLE_B = deux familles opposées

struct Choice : Représente un choix de dialogue possible pour le joueur : string text -> texte du choix
                                                                          Clan affecte -> à quel clan cela profite ou nuit
                                                                          int points -> effet sur la réputation du joueur

struct Dialogue : Représente un Un dialogue complet : speaker -> nom de la personne qui parle
                                                      text -> texte affiché
                                                      vector<Choice> choices -> liste des choix possibles  
                                                      isEndDialogue -> indique si c’est la fin du dialogue      

struct NPC : Représente un PNJ : RectangleShape shape -> sa représentation visuelle
                                 string name/id -> nom et identifiant unique
                                 bool isMainNPC, isBoss, hasBeenTalkedTo -> drapeaux logiques pour le comportement  
                                 Clan clan -> à quelle famille il appartient
                                 vector<Dialogue> dialogues -> ce qu’il peut dire
                                 int currentDialogueIndex -> indique à quel dialogue on est rendu
                                 Constructeur -> initialise la forme, la couleur et la position selon son rôle

Classe(s) utilisée(s) : Gameplay
En accès PRIVATE : RenderWindow* m_window -> pointeur vers la fenêtre principale du jeu
                   Player m_player -> le joueur contrôlable
                   MapLoader m_map -> la carte affichée
                   vector<NPC> m_npcs -> la liste des PNJ
                   Font m_font -> police utilisée pour le texte
                   Text m_promptText, m_dialogueText -> textes d’affichage (messages, dialogues)
                   vector<Text> m_choiceTexts -> les textes des choix dans les dialogues
                   RectangleShape m_dialogueBox / m_choiceBoxes -> zones de fond pour les dialogues et choix
                   bool inDialogue, inMiniGame -> indiquent l’état du jeu
                   NPC* currentNPC -> pointeur vers le PNJ actuellement en interaction
                   int selectedChoice -> index du choix sélectionné
                   map<string, bool> npcsTalkedTo -> enregistre avec quels PNJ on a déjà parlé
                   int pointsFamilleA, pointsFamilleB -> score / réputation selon les clans
                   *****
                   Méthodes privées (logique interne) : initializeNPCs() -> crée les PNJ
                                                        loadDialogues() -> charge les dialogues depuis un fichier
                                                        canTalkToBoss() -> vérifie si le boss est accessible
                                                        startDialogue() / endDialogue() -> ouvrent ou ferment un dialogue
                                                        handleDialogueInput() / selectChoice() -> gèrent les entrées clavier
                                                        checkGameEnd() -> vérifie si la partie est finie
                                                        renderDialogue() -> affiche la boîte de dialogue

En accès PUBLIC : Gameplay(RenderWindow* window) -> constructeur, initialise la scène
                  void run() -> boucle principale du gameplay
                  void handleInput() -> gestion des touches
                  void update() -> mise à jour logique (positions, états)
                  void render() -> affichage des éléments du jeu






World.hpp:
Classe(s) utilisée(s) : World
En accès PRIVATE : vector<Texture> m_tilesets -> textures des tuiles
                   vector<Sprite> tiles -> chaque tuile à afficher
                   unsigned tileSize = 16 -> taille des tuiles (px)

En accès PUBLIC : World() -> constructeur
                  bool load(const string& texturePath, unsigned widthInTiles, unsigned heightInTiles) -> charge une carte selon une texture et une taille
                  void render(RenderWindow& window) -> dessine le monde dans la fenêtre





Player.hpp:
Classe(s) utilisée(s) : Player
En accès PRIVATE : Texture texture -> image du joueur
                   Sprite sprite -> image affichée à l’écran
                   float speed -> vitesse de déplacement

En accès PUBLIC : Player() -> constructeur, charge la texture et initialise le sprite
                  void handleInput(float deltaTime) -> lit les touches du clavier et déplace le joueur
                  void update(float deltaTime) -> met à jour la position ou les animations
                  void draw(RenderWindow& window) -> affiche le joueur à l’écran
                  void move(Vector2f dir) -> déplace le sprite selon une direction donnée
                  Vector2f getPosition() const -> renvoie la position du joueur
                  FloatRect getBounds() const -> renvoie la boîte de collision du joueur





Audio.hpp:
Classe(s) utilisée(s) : Audio
En accès PUBLIC : Audio() / ~Audio() -> constructeur / destructeur
                  bool loadMusic(const string& filePath) -> charge un fichier audio
                  void playMusic(bool loop = true) -> lance la lecture (en boucle ou non)
                  void stopMusic() -> arrête la musique
                  void setVolume(float volume) -> règle le volume

En accès PRIVATE : Music music -> objet SFML qui représente le flux audio





CONTRAINTES:
**Jeu en cours de developpement**
Pas de page narrative
Pas de cinématiques entre les dialogues





Messages d'erreurs non résolu ou imcompris:
'localtime': This function or variable may be unsafe. Consider using localtime_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details = > Log.hpp (????)
'sf::Text::Text' : aucune fonction surchargée n’a pu convertir tous les types d’arguments = > memory (????)
'sf::Text' : aucun constructeur par défaut approprié disponible = > EndScreen.cpp & Gameplay.cpp
