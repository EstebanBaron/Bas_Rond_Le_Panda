#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Personnage.h"
#include "Aliments.h"
#include "Vie.h"
#include "Piece.h"
#include "Bouton.h"


//variables
sf::Texture map;
sf::Sprite sprite_map;
sf::Texture gameOver;
sf::Sprite sprite_gameOver;
sf::Texture menu;
sf::Sprite sprite_menu;
sf::Texture textureStore;
sf::Sprite sprite_store;
sf::Texture textureCredits;
sf::Sprite sprite_credits;
sf::Texture debutJeu;
sf::Sprite sprite_debutJeu;
sf::Texture imageBD1;
sf::Sprite sprite_imageBD1;
sf::Texture imageBD2;
sf::Sprite sprite_imageBD2;
sf::Texture imageBD3;
sf::Sprite sprite_imageBD3;
sf::Texture imageBD4;
sf::Sprite sprite_imageBD4;
float const largeurFenetre = 700;
float const longueurFenetre = 690;
Personnage *perso(0);
Aliments *pointeurAliment1(0);
Aliments *pointeurAliment2(0);
Aliments *pointeurAliment3(0);
Aliments *pointeurAliment4(0);
Vie *pointeurVie1(0);
Vie *pointeurVie2(0);
Vie *pointeurVie3(0);
Piece *piece(0);
int TailleAlimentX = 111;
int TailleAlimentY = 55;
int TailleDepasseY = 112;
int depasseBolDessous = 100;
sf::Text textScore;
int score = 0;
sf::Text textGold;
int gold = 0;
int nombreVies;
int tailleXBoutonGameOver = 162; //taille x et y des boutons du game over
int tailleYBoutonGameOver = 54;
int tailleXBoutonMainMenu = 278; //taille x et y des boutons du main menu
int tailleYBoutonMainMenu = 92;
int menuPrincipal = 3;
int menuStore = 0;
int menuCredits = 0;
int menuDebutJeu = 1;
int menuBD1 = 0;
int menuBD2 = 0;
int menuBD3 = 0;
int menuBD4 = 0;
int playMusic = 1;
sf::Vector2i positionSouris;
int TailleSeparationBoutonMainMenu = 25;
const sf::Color couleurText(sf::Color::Black);
int tempsDepart = 0;
int tempsFinal = 40;
int attenteBD = 10;


//fonctions
bool collisionBol(Aliments* pointeurAliment1, Personnage* perso);
bool collisionSol(Aliments* pointeurAliment1);
bool estVivant();
bool clicSurLesPetitsBouton(Bouton& bouton,sf::RenderWindow& fenetre);
bool clicSurLesBoutonsDuMenu(Bouton& bouton,sf::RenderWindow& fenetre);
void chargementImage(sf::RenderWindow& fenetre, sf::Sprite& sprite, sf::Texture& texture, std::string nom);
void chargementFont(sf::Font& font, sf::Text& text, std::string nom);
void chargementMusic(sf::Music& music, std::string nom);
void chargementSound(sf::SoundBuffer& sound, std::string nom);
void changementPosition(Aliments* pointeurAliment1, Aliments* pointeurAliment2, Aliments* pointeurAliment3, Aliments* pointeurAliment4);

int main()
{
    //cacher console
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    //initialisation des objets
    sf::RenderWindow fenetrePrincipal;
    perso = new Personnage();
    piece = new Piece();

    //parametrage de la fenetre
    fenetrePrincipal.create(sf::VideoMode(largeurFenetre,longueurFenetre), "Bas-Rond Le Panda", sf::Style::Close);
    fenetrePrincipal.setPosition(sf::Vector2i(325,2));
    fenetrePrincipal.setFramerateLimit(60);

    //Charger la map
    chargementImage(fenetrePrincipal, sprite_map, map, "images/map.png");

    //initialisation des pointeurs
    srand(time(NULL));

    pointeurAliment1 = new Aliments(rand() % ((3 - 1) + 1) + 1);
    pointeurAliment2 = new Aliments(rand() % ((6 - 4) + 1) + 4);
    pointeurAliment3 = new Aliments(rand() % ((9 - 7) + 1) + 7);
    pointeurAliment4 = new Aliments(rand() % ((12 - 10) + 1) + 10);

    pointeurVie1 = new Vie(1);
    pointeurVie2 = new Vie(2);
    pointeurVie3 = new Vie(3);

    //chargement des golds
    sf::Font fontGold;
    chargementFont(fontGold, textGold, "polices/police.ttf");
    textGold.setFillColor(couleurText);

    //music
    sf::Music musicJeu;
    chargementMusic(musicJeu, "musiques/MusicJeu.ogg");

    sf::Music musicMenu;
    chargementMusic(musicMenu, "musiques/MusicMenu.ogg");

    //sound
    sf::SoundBuffer clickBuffer;
    chargementSound(clickBuffer, "musiques/click.ogg");
    sf::Sound click;
    click.setBuffer(clickBuffer);
    click.play();

    //boucle d'ouverture fenetre
    while(fenetrePrincipal.isOpen())
    {
        sf::Event event;
        //Tests des evenements
        while(fenetrePrincipal.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                delete perso;
                delete pointeurAliment1;
                delete pointeurAliment2;
                delete pointeurAliment3;
                delete pointeurAliment4;
                delete pointeurVie1;
                delete pointeurVie2;
                delete pointeurVie3;
                perso = 0;
                pointeurAliment1 = 0;
                pointeurAliment2 = 0;
                pointeurAliment3 = 0;
                pointeurAliment4 = 0;
                pointeurVie1 = 0;
                pointeurVie2 = 0;
                pointeurVie3 = 0;
                fenetrePrincipal.close();
            }
        }

        //Affichage du titre du jeu
        if(menuDebutJeu == 1)
        {
            //music
            musicJeu.stop();
            click.stop();

            //chargement du fond
            chargementImage(fenetrePrincipal, sprite_debutJeu, debutJeu, "images/fondDebut.png");

            //temps que reste l'image
            ++tempsDepart;
            if(tempsDepart == tempsFinal)
            {
                menuDebutJeu = 0;
                tempsDepart = 0;
                menuBD1 = 1;
            }
        }

        //BD compos� de 4 images pour expliquer l'histoire
        if(menuBD1 == 1)
        {
            //chargement du fond
            chargementImage(fenetrePrincipal, sprite_imageBD1, imageBD1, "images/imageBD1.png");
            fenetrePrincipal.draw(sprite_imageBD1);

            //creation de mes deux boutons
            Bouton next(tailleXBoutonGameOver/5,longueurFenetre-1.3*tailleYBoutonGameOver,"images/next.png");
            fenetrePrincipal.draw(next.getSpriteBouton());
            Bouton skip(3.1*tailleXBoutonGameOver,longueurFenetre-1.3*tailleYBoutonGameOver,"images/skip.png");
            fenetrePrincipal.draw(skip.getSpriteBouton());

            if(tempsDepart == attenteBD)
            {
                //detecter le clic souris
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //bouton next
                    if(clicSurLesPetitsBouton(next, fenetrePrincipal))
                    {
                        tempsDepart = 0;
                        menuBD1 = 0;
                        menuBD2 = 1;
                    }
                    //bouton skip
                    if(clicSurLesPetitsBouton(skip, fenetrePrincipal))
                    {
                        click.play();
                        menuBD1 = 0;
                        menuPrincipal = 1;
                    }
                }
            }
            else
                ++tempsDepart;
        }
        if(menuBD2 == 1)
        {
            //chargement du fond
            chargementImage(fenetrePrincipal, sprite_imageBD2, imageBD2, "images/imageBD2.png");
            fenetrePrincipal.draw(sprite_imageBD2);

            //creation de mes deux boutons
            Bouton next(tailleXBoutonGameOver/5,longueurFenetre-1.3*tailleYBoutonGameOver,"images/next.png");
            fenetrePrincipal.draw(next.getSpriteBouton());
            Bouton skip(3.1*tailleXBoutonGameOver,longueurFenetre-1.3*tailleYBoutonGameOver,"images/skip.png");
            fenetrePrincipal.draw(skip.getSpriteBouton());

            if(tempsDepart == attenteBD)
            {
                //detection du clic
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //bouton next
                    if(clicSurLesPetitsBouton(next, fenetrePrincipal))
                    {
                        tempsDepart = 0;
                        menuBD2 = 0;
                        menuBD3 = 1;
                    }
                    //bouton skip
                    if(clicSurLesPetitsBouton(skip, fenetrePrincipal))
                    {
                        click.play();
                        menuBD2 = 0;
                        menuPrincipal = 1;
                    }
                }
            }
            else
                ++tempsDepart;
        }
        if(menuBD3 == 1)
        {
            //chargement du fond
            chargementImage(fenetrePrincipal, sprite_imageBD3, imageBD3, "images/imageBD3.png");
            fenetrePrincipal.draw(sprite_imageBD3);

            //creation de mes deux boutons
            Bouton next(tailleXBoutonGameOver/5,longueurFenetre-1.3*tailleYBoutonGameOver,"images/next.png");
            fenetrePrincipal.draw(next.getSpriteBouton());
            Bouton skip(3.1*tailleXBoutonGameOver,longueurFenetre-1.3*tailleYBoutonGameOver,"images/skip.png");
            fenetrePrincipal.draw(skip.getSpriteBouton());

            if(tempsDepart == attenteBD)
            {
                //detection du clic
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //bouton next
                    if(clicSurLesPetitsBouton(next, fenetrePrincipal))
                    {
                        tempsDepart = 0;
                        menuBD3 = 0;
                        menuBD4 = 1;
                    }
                    //bouton skip
                    if(clicSurLesPetitsBouton(skip, fenetrePrincipal))
                    {
                        click.play();
                        menuBD3 = 0;
                        menuPrincipal = 1;
                    }
                }
            }
            else
                ++tempsDepart;
        }
        if(menuBD4 == 1)
        {
            //initialisation de variables
            positionSouris = sf::Mouse::getPosition(fenetrePrincipal);

            //chargement du fond
            chargementImage(fenetrePrincipal, sprite_imageBD4, imageBD4, "images/imageBD4.png");
            fenetrePrincipal.draw(sprite_imageBD4);

            //creation du bouton
            Bouton skip(3.1*tailleXBoutonGameOver,longueurFenetre-1.3*tailleYBoutonGameOver,"images/skip.png");
            fenetrePrincipal.draw(skip.getSpriteBouton());

            //detection du clic
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //bouton skip
                if(clicSurLesPetitsBouton(skip, fenetrePrincipal))
                {
                    click.play();
                    menuBD4 = 0;
                    menuPrincipal = 1;
                }
            }
        }

        //Gold (sprite + conditions)
        textGold.setString(std::to_string(gold));
        if (gold < 10)
        {
            int sizePolice0_9 = 45;
            int positionX = 655;
            int positionY = -5;
            textGold.setCharacterSize(sizePolice0_9);
            textGold.setPosition(sf::Vector2f(positionX, positionY));
        }
        else if (gold > 9 && gold < 100)
        {
            int sizePolice10_99 = 40;
            int positionX = 647;
            int positionY = -2;
            textGold.setCharacterSize(sizePolice10_99);
            textGold.setPosition(sf::Vector2f(positionX,positionY));
        }
        else if (gold > 99 && gold < 1000)
        {
            int sizePolice100_999 = 31;
            int positionX = 644;
            int positionY = 5;
            textGold.setCharacterSize(sizePolice100_999);
            textGold.setPosition(sf::Vector2f(positionX,positionY));
        }
        else
        {
            int sizePolice1000 = 24;
            int positionX = 644;
            int positionY = 11;
            textGold.setCharacterSize(sizePolice1000);
            textGold.setPosition(sf::Vector2f(positionX,positionY));
        }

        //Menu principal
        if(menuPrincipal == 1)
        {
            //initialisation de variables
            positionSouris = sf::Mouse::getPosition(fenetrePrincipal);

            //Image du menu
            chargementImage(fenetrePrincipal, sprite_menu, menu, "images/menuPrincipal.png");

            //Boutons
            Bouton play((largeurFenetre/2) - (tailleXBoutonMainMenu/2.0), (longueurFenetre/3) - TailleSeparationBoutonMainMenu ,"images/play.png");
            Bouton store((largeurFenetre/2) - (tailleXBoutonMainMenu/2.0), (longueurFenetre/2) - TailleSeparationBoutonMainMenu ,"images/store.png");
            Bouton credits((largeurFenetre/2) - (tailleXBoutonMainMenu/2.0), (2*(longueurFenetre/3)) - TailleSeparationBoutonMainMenu ,"images/credits.png");

            //affichage des �l�ments
            fenetrePrincipal.draw(sprite_menu);
            fenetrePrincipal.draw(play.getSpriteBouton());
            fenetrePrincipal.draw(store.getSpriteBouton());
            fenetrePrincipal.draw(credits.getSpriteBouton());

            //Detection du clique sur les boutons
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //bouton play
                if(clicSurLesBoutonsDuMenu(play, fenetrePrincipal))
                {
                    click.play();
                    nombreVies = 3;
                    menuPrincipal = 0;
                    musicMenu.stop();
                    musicJeu.play();
                    musicJeu.setLoop(true);
                }
                //bouton store
                if(clicSurLesBoutonsDuMenu(store, fenetrePrincipal))
                {
                    click.play();
                    menuStore = 1;
                }
                //bouton credits
                if(clicSurLesBoutonsDuMenu(credits, fenetrePrincipal))
                {
                    click.play();
                    menuCredits = 1;
                }
            }
            //menu store
            if(menuStore == 1)
            {
                //chargement du fond
                chargementImage(fenetrePrincipal, sprite_store, textureStore, "images/store_menu.png");

                fenetrePrincipal.draw(sprite_store);
                fenetrePrincipal.draw(textGold);
                fenetrePrincipal.draw(piece->getSpritePiece());
                Bouton mainMenu(tailleXBoutonGameOver/5,longueurFenetre-1.3*tailleYBoutonGameOver,"images/mainMenu.png");
                fenetrePrincipal.draw(mainMenu.getSpriteBouton());
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(clicSurLesPetitsBouton(mainMenu, fenetrePrincipal))
                    {
                        menuStore = 0;
                    }
                }
            }
            //Menu credits
            if(menuCredits == 1)
            {
                //chargement du fond
                chargementImage(fenetrePrincipal, sprite_credits, textureCredits, "images/credits_menu.png");
                fenetrePrincipal.draw(sprite_credits);

                Bouton mainMenu(tailleXBoutonGameOver/5,longueurFenetre-1.3*tailleYBoutonGameOver,"images/mainMenu.png");
                fenetrePrincipal.draw(mainMenu.getSpriteBouton());

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(clicSurLesPetitsBouton(mainMenu, fenetrePrincipal))
                    {
                        menuCredits = 0;
                    }
                }
            }
        }

        //Jeux
        if(estVivant())
        {
            //music
            playMusic = 1;

            //Score
            sf::Font fontScore;
            chargementFont(fontScore, textScore, "polices/police.ttf");
            textScore.setString(std::to_string(score));
            textScore.setCharacterSize(40);
            textScore.setFillColor(couleurText);
            textScore.setPosition(sf::Vector2f((700/2),0));

            //deplacement objets
            perso->deplacement();
            pointeurAliment1->deplacement();
            pointeurAliment2->deplacement();
            pointeurAliment3->deplacement();
            pointeurAliment4->deplacement();

            //collisions Bol
            if(collisionBol(pointeurAliment1,perso))
            {
                if(pointeurAliment1->getTexture() == "images/poisson_pourri.png")
                {
                    nombreVies = 0;
                }
                else if(pointeurAliment1->getTexture() == "images/sushis.png")
                {
                    score += 1;
                    gold += 2;
                }
                else
                {
                    score += 1;
                    gold += 3;
                }
                delete pointeurAliment1;
                pointeurAliment1 = 0;
                pointeurAliment1 = new Aliments(rand() % ((3 - 1) + 1) + 1);
                changementPosition(pointeurAliment1, pointeurAliment2, pointeurAliment3, pointeurAliment4);
            }
            if(collisionBol(pointeurAliment2,perso))
            {
                if(pointeurAliment2->getTexture() == "images/soupe.png")
                {
                    score += 1;
                    gold += 1;
                }
                else if(pointeurAliment2->getTexture() == "images/sushis.png")
                {
                    score += 1;
                    gold += 2;
                }
                else
                {
                    score += 1;
                    gold += 3;
                }
                delete pointeurAliment2;
                pointeurAliment2 = 0;
                pointeurAliment2 = new Aliments(rand() % ((6 - 4) + 1) + 4);
                changementPosition(pointeurAliment2, pointeurAliment1, pointeurAliment3, pointeurAliment4);
            }
            if(collisionBol(pointeurAliment3,perso))
            {
                if(pointeurAliment3->getTexture() == "images/poisson_pourri.png")
                {
                    nombreVies = 0;
                }
                else if(pointeurAliment3->getTexture() == "images/soupe.png")
                {
                    score += 1;
                    gold += 1;
                }
                else
                {
                    score += 1;
                    gold += 3;
                }
                delete pointeurAliment3;
                pointeurAliment3 = 0;
                pointeurAliment3 = new Aliments(rand() % ((9 - 7) + 1) + 7);
                changementPosition(pointeurAliment3, pointeurAliment1, pointeurAliment2, pointeurAliment4);
            }
            if(collisionBol(pointeurAliment4,perso))
            {
                if(pointeurAliment4->getTexture() == "images/poisson_pourri.png")
                {
                    nombreVies = 0;
                }
                else if(pointeurAliment4->getTexture() == "images/soupe.png")
                {
                    score += 1;
                    gold += 1;
                }
                else
                {
                    score += 1;
                    gold += 2;
                }
                delete pointeurAliment4;
                pointeurAliment4 = 0;
                pointeurAliment4 = new Aliments(rand() % ((12 - 10) + 1) + 10);
                changementPosition(pointeurAliment4, pointeurAliment1, pointeurAliment2, pointeurAliment3);
            }

            //Affichage des objets
            fenetrePrincipal.draw(sprite_map);
            fenetrePrincipal.draw(textScore);
            fenetrePrincipal.draw(textGold);
            fenetrePrincipal.draw(piece->getSpritePiece());

            if(collisionSol(pointeurAliment4))
            {
                if(!(pointeurAliment4->getTexture() == "images/poisson_pourri.png"))
                {
                    nombreVies -= 1;
                }
                delete pointeurAliment4;
                pointeurAliment4 = 0;
                pointeurAliment4 = new Aliments(rand() % ((12 - 10) + 1) + 10);
                changementPosition(pointeurAliment4, pointeurAliment1, pointeurAliment2, pointeurAliment3);
            }

            if(collisionSol(pointeurAliment3))
            {
                if(!(pointeurAliment3->getTexture() == "images/poisson_pourri.png"))
                {
                    nombreVies -= 1;
                }
                delete pointeurAliment3;
                pointeurAliment3 = 0;
                pointeurAliment3 = new Aliments(rand() % ((9 - 7) + 1) + 7);
                changementPosition(pointeurAliment3, pointeurAliment1, pointeurAliment2, pointeurAliment4);
            }
            if(nombreVies>=3)
                fenetrePrincipal.draw(pointeurVie3->getSpriteVie());

            if(collisionSol(pointeurAliment2))
            {
                nombreVies -= 1;
                delete pointeurAliment2;
                pointeurAliment2 = 0;
                pointeurAliment2 = new Aliments(rand() % ((6 - 4) + 1) + 4);
                changementPosition(pointeurAliment2, pointeurAliment1, pointeurAliment3, pointeurAliment4);
            }
            if(nombreVies>=2)
                fenetrePrincipal.draw(pointeurVie2->getSpriteVie());

            if(collisionSol(pointeurAliment1))
            {
                if(!(pointeurAliment1->getTexture() == "images/poisson_pourri.png"))
                {
                    nombreVies -= 1;
                }
                delete pointeurAliment1;
                pointeurAliment1 = 0;
                pointeurAliment1 = new Aliments(rand() % ((3 - 1) + 1) + 1);
                changementPosition(pointeurAliment1, pointeurAliment2, pointeurAliment3, pointeurAliment4);
            }
            if(nombreVies >= 1)
                fenetrePrincipal.draw(pointeurVie1->getSpriteVie());

            fenetrePrincipal.draw(perso->getSpritePerso());
            fenetrePrincipal.draw(pointeurAliment1->getSpriteAliments());
            fenetrePrincipal.draw(pointeurAliment2->getSpriteAliments());
            fenetrePrincipal.draw(pointeurAliment3->getSpriteAliments());
            fenetrePrincipal.draw(pointeurAliment4->getSpriteAliments());
        }
        //game Over
        else if(nombreVies < 1 && menuPrincipal == 0)
        {
            //initailisation de variables + reglage musiques
            positionSouris = sf::Mouse::getPosition(fenetrePrincipal);
            musicJeu.stop();
            if(playMusic == 1)
            {
                musicMenu.play();
                musicMenu.setLoop(true);
                playMusic = 0;
            }

            //chargement de l'image game over
            chargementImage(fenetrePrincipal, sprite_gameOver, gameOver, "images/gameOver.png");

            //chargement des boutons du game over
            Bouton mainMenu(tailleXBoutonGameOver/5,longueurFenetre-1.3*tailleYBoutonGameOver,"images/mainMenu.png");
            fenetrePrincipal.draw(mainMenu.getSpriteBouton());
            Bouton restart(3.1*tailleXBoutonGameOver,longueurFenetre-1.3*tailleYBoutonGameOver,"images/restart.png");
            fenetrePrincipal.draw(restart.getSpriteBouton());


            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(clicSurLesPetitsBouton(restart, fenetrePrincipal))
                {
                    delete perso;
                    delete pointeurAliment1;
                    delete pointeurAliment2;
                    delete pointeurAliment3;
                    delete pointeurAliment4;
                    perso = new Personnage();
                    pointeurAliment1 = new Aliments(rand() % ((3 - 1) + 1) + 1);
                    changementPosition(pointeurAliment1, pointeurAliment2, pointeurAliment3, pointeurAliment4);
                    pointeurAliment2 = new Aliments(rand() % ((6 - 4) + 1) + 4);
                    changementPosition(pointeurAliment2, pointeurAliment1, pointeurAliment3, pointeurAliment4);
                    pointeurAliment3 = new Aliments(rand() % ((9 - 7) + 1) + 7);
                    changementPosition(pointeurAliment3, pointeurAliment1, pointeurAliment2, pointeurAliment4);
                    pointeurAliment4 = new Aliments(rand() % ((12 - 10) + 1) + 10);
                    changementPosition(pointeurAliment4, pointeurAliment1, pointeurAliment2, pointeurAliment3);
                    score = 0;
                    nombreVies = 3;
                    click.play();
                    musicMenu.stop();
                    musicJeu.play();
                    musicJeu.setLoop(true);
                }
                else if(clicSurLesPetitsBouton(mainMenu, fenetrePrincipal))
                {
                    delete perso;
                    delete pointeurAliment1;
                    delete pointeurAliment2;
                    delete pointeurAliment3;
                    delete pointeurAliment4;
                    perso = new Personnage();
                    pointeurAliment1 = new Aliments(rand() % ((3 - 1) + 1) + 1);
                    changementPosition(pointeurAliment1, pointeurAliment2, pointeurAliment3, pointeurAliment4);
                    pointeurAliment2 = new Aliments(rand() % ((6 - 4) + 1) + 4);
                    changementPosition(pointeurAliment2, pointeurAliment1, pointeurAliment3, pointeurAliment4);
                    pointeurAliment3 = new Aliments(rand() % ((9 - 7) + 1) + 7);
                    changementPosition(pointeurAliment3, pointeurAliment1, pointeurAliment2, pointeurAliment4);
                    pointeurAliment4 = new Aliments(rand() % ((12 - 10) + 1) + 10);
                    changementPosition(pointeurAliment4, pointeurAliment1, pointeurAliment2, pointeurAliment3);
                    score = 0;
                    menuPrincipal = 1;
                    click.play();
                }
            }
        }
        fenetrePrincipal.display();
        fenetrePrincipal.clear();
    }

    return 0;
}

bool collisionBol(Aliments* pointeurAliment1, Personnage* perso)
{
    return ((((pointeurAliment1->getSpriteAliments().getPosition().y + TailleAlimentY) >= (perso->getSpritePerso().getPosition().y + perso->getDepasseBol())) && (pointeurAliment1->getSpriteAliments().getPosition().y + TailleAlimentY) <= (perso->getSpritePerso().getPosition().y + depasseBolDessous)) && ((((pointeurAliment1->getSpriteAliments().getPosition().x) >= (perso->getSpritePerso().getPosition().x + perso->getDepasseCoudes())) && ((pointeurAliment1->getSpriteAliments().getPosition().x) <= (perso->getSpritePerso().getPosition().x + perso->getSizePerso().x - perso->getDepasseCoudes()))) || ((pointeurAliment1->getSpriteAliments().getPosition().x + TailleAlimentX) <= (perso->getSpritePerso().getPosition().x + perso->getSizePerso().x - perso->getDepasseCoudes()) && ((pointeurAliment1->getSpriteAliments().getPosition().x + TailleAlimentX) >= (perso->getSpritePerso().getPosition().x + perso->getDepasseCoudes())))));
}

bool collisionSol(Aliments* pointeurAliment1)
{
    return pointeurAliment1->getSpriteAliments().getPosition().y >= (longueurFenetre + TailleDepasseY);
}

bool estVivant()
{
    return nombreVies > 0;
}

bool clicSurLesPetitsBouton(Bouton& bouton,sf::RenderWindow& fenetre)
{
    positionSouris = sf::Mouse::getPosition(fenetre);
    return (((positionSouris.y >= bouton.getSpriteBouton().getPosition().y) && (positionSouris.y <= bouton.getSpriteBouton().getPosition().y + tailleYBoutonGameOver)) && ((positionSouris.x >= bouton.getSpriteBouton().getPosition().x) && (positionSouris.x <= bouton.getSpriteBouton().getPosition().x + tailleXBoutonGameOver)));
}

bool clicSurLesBoutonsDuMenu(Bouton& bouton,sf::RenderWindow& fenetre)
{
    positionSouris = sf::Mouse::getPosition(fenetre);
    return (((positionSouris.y >= bouton.getSpriteBouton().getPosition().y) && (positionSouris.y <= bouton.getSpriteBouton().getPosition().y + tailleYBoutonMainMenu)) && ((positionSouris.x >= bouton.getSpriteBouton().getPosition().x) && (positionSouris.x <= bouton.getSpriteBouton().getPosition().x + tailleXBoutonMainMenu)));
}

void chargementImage(sf::RenderWindow& fenetre, sf::Sprite& sprite, sf::Texture& texture, std::string nom)
{
    if(!texture.loadFromFile(nom))
    {
        std::cout << "Erreur chargement " << nom << std::endl;
    }
    sprite.setTexture(texture);
    fenetre.draw(sprite);
}

void chargementFont(sf::Font& font, sf::Text& text, std::string nom)
{
    if(!font.loadFromFile(nom))
    {
        std::cout << "erreur de chargement" << nom << std::endl;
    }
    text.setFont(font);
}

void chargementMusic(sf::Music& music, std::string nom)
{
    if(!music.openFromFile(nom))
    {
        std::cout << "erreur de chargement de " << nom << std::endl;
    }
    music.play();
    music.setLoop(true);
}

void chargementSound(sf::SoundBuffer& sound, std::string nom)
{
    if(!sound.loadFromFile(nom))
    {
        std::cout << "erreur de chargement de " << nom << std::endl;
    }
}

void changementPosition(Aliments* pointeurAliment1, Aliments* pointeurAliment2, Aliments* pointeurAliment3, Aliments* pointeurAliment4)
{
    if(((pointeurAliment2->getSpriteAliments().getPosition().y >= pointeurAliment1->getSpriteAliments().getPosition().y - 300) && (pointeurAliment2->getSpriteAliments().getPosition().y <= pointeurAliment1->getSpriteAliments().getPosition().y + 300)) || ((pointeurAliment3->getSpriteAliments().getPosition().y >= pointeurAliment1->getSpriteAliments().getPosition().y - 300) && (pointeurAliment3->getSpriteAliments().getPosition().y <= pointeurAliment1->getSpriteAliments().getPosition().y + 300)) || ((pointeurAliment4->getSpriteAliments().getPosition().y >= pointeurAliment1->getSpriteAliments().getPosition().y - 300) && (pointeurAliment4->getSpriteAliments().getPosition().y <= pointeurAliment1->getSpriteAliments().getPosition().y + 300)))
    {
       pointeurAliment1->getSpriteAliments().setPosition(pointeurAliment1->getSpriteAliments().getPosition().x, pointeurAliment1->getSpriteAliments().getPosition().y - 300);
    }
}
