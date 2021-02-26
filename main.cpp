#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <ctime>
#include <fstream>
#include "Perso.h"
#include "Perso.cpp"
#include "fonctions.cpp"
#include "fonctions.h"

using namespace sf;
using namespace std;

int main()
{
    /// Load a music to play
    sf::Music music;
    if (!music.openFromFile("musicMario.ogg"))
        cout<<"erreur music"<<endl;
    music.setLoop(true);

    bool creation = false;
    bool creationMur = false;
    bool creationMechant = false;
    string create;
    cin>>create;
    if (create=="1")
        creation=true;
    Vector2f coordonnees;
    srand(time(0));
    /// int exemple = rand () %2   ;
    int const largeurEcran (800);
    int const hauteurEcran (600);
    Vector2f const dimensionsEcran (600,400);
    unsigned score(0);
    Text texte;
    Font fonte;
    Color couleurFond (34,177,76);
    ///unsigned  maxi =1000;    ///dimension de la zone de jeu (100*maxi+100) pour aleatoire
    Vector2f spawnPoint (100,100); ///point où apparait Mario
    enum types {point, mur, mechant};
    types type = point;

    if (!fonte.loadFromFile("Fipps-Regular.otf"))       ///charger la fonte
        std::cout<<"erreur chargement fonte \n";
    else
        texte.setFont(fonte);
    texte.setString("0");
    texte.setPosition(0,0);
    texte.setColor(Color::Black);

    Mario mario (spawnPoint); ///creer mario

    RenderWindow app(VideoMode(largeurEcran,hauteurEcran),"Mario Game");    ///creer la fenetre
    app.setFramerateLimit(60);

    vector <Point> points = creerObjets <Point> ("savePoints.txt",2);
    vector <Mur> murs = creerObjets <Mur> ("saveMurs.txt",4);        ///creer les objets
    vector <Mechant> mechants = creerObjets <Mechant> ("saveMechants.txt",4);
    vector <Point> pointsCrees;
    vector <Mur> mursCrees;
    vector <Mechant> mechantsCrees;

    music.play();    /// Play the music

    /**if (Keyboard::isKeyPressed(Keyboard::A))    ///Creation aleatoire
    {
        int nb;
        int nbs;
        std::vector <Mechant> mechants;     ///creer les méchants
        for (int i=0; i<2; i++)
        {
            nb =(rand()%maxi)+100;
            nbs =(rand()%maxi)+100;
            Mechant mechant (Vector2f(nb,(rand()%maxi)+100),Vector2f(nb,(rand()%maxi)+100),3);
            mechants.push_back(mechant);
            nb =(rand()%maxi)+100;
            nbs =(rand()%maxi)+100;
            Mechant mechant2 (Vector2f((rand()%maxi)+100,nb),Vector2f((rand()%maxi)+100,nb));
            mechants.push_back(mechant2);
        }

        std::vector <Mur> murs;  ///creer les murs
        for (int i=0; i<5; i++)
        {
            Mur mur (Vector2f((rand()%500)+200,50),Vector2f((rand()%maxi)+100,(rand()%maxi)+100));
            murs.push_back(mur);
            Mur mur2 (Vector2f(50,(rand()%500)+200),Vector2f((rand()%maxi)+100,(rand()%maxi)+100));
            murs.push_back(mur2);
        }

        std::vector <Point> points;  ///creer les points
        for (int i=0; i<20; i++)
        {
            Point point (Vector2f((rand()%maxi)+100,(rand()%maxi)+100));
            points.push_back(point);
        }
    }**/

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type==Event::Closed || (event.type==Event::KeyPressed && event.key.code==Keyboard::Space))
            {
                if (creation)
                {
                    enregistrer <Point> (pointsCrees,"savePoints.txt",2);   ///enregistrer tous les objets crées
                    enregistrer <Mechant> (mechantsCrees,"saveMechants.txt",4);
                    enregistrer <Mur> (mursCrees,"saveMurs.txt",4);
                }
                app.close();       ///fermer la fenetre si on clique sur la croix ou si on appuie sur la bare espace
            }
            if (creation)
            {
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::P)
                {
                    pointsCrees.push_back(Point(mario.getM_sprite().getPosition()));
                    ///points.push_back(placerObjet(mario.getM_sprite().getPosition(),"savePoints.txt"));
                }
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::W)
                {
                    ///coordonnees = placerObjet(mario.getM_sprite().getPosition(),"saveMurs.txt");
                    coordonnees = mario.getM_sprite().getPosition();
                    creationMur = true;
                }
                if (event.type==Event::KeyReleased && event.key.code==Keyboard::W)
                {
                    ///murs.push_back(Mur(coordonnees, placerObjet(mario.getM_sprite().getPosition(),"saveMurs.txt")));
                    mursCrees.push_back(Mur(coordonnees, mario.getM_sprite().getPosition()));
                    creationMur = false;
                }
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::M)
                {
                    ///coordonnees = placerObjet(mario.getM_sprite().getPosition(),"saveMechants.txt");
                    coordonnees = mario.getM_sprite().getPosition();
                    creationMechant = true;
                }
                if (event.type==Event::KeyReleased && event.key.code==Keyboard::M)
                {
                    ///mechants.push_back(Mechant(coordonnees, placerObjet(mario.getM_sprite().getPosition(),"saveMechants.txt")));
                    mechantsCrees.push_back(Mechant(coordonnees, mario.getM_sprite().getPosition()));
                    creationMechant = false;
                }
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::A)
                {
                    if(Keyboard::isKeyPressed(Keyboard::P))
                        if (pointsCrees.size()>0)
                            pointsCrees.pop_back();
                    /**    if(Keyboard::isKeyPressed(Keyboard::M))

                            if(Keyboard::isKeyPressed(Keyboard::W))**/
                }
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::Numpad4)
                {
                    switch (type)
                    {
                    case point :
                        type = mechant;
                        break;
                    case mur :
                        type = point;
                        break;
                    case mechant :
                        type = mur;
                        break;
                    }
                }
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::Numpad6)
                {
                    switch (type)
                    {
                    case point :
                        type = mur;
                        break;
                    case mur :
                        type = mechant;
                        break;
                    case mechant :
                        type = point;
                        break;
                    }
                }
            }
        }
        if (creation)
        {
            if (creationMur)
            {
                Mur murCreer (coordonnees, mario.getM_sprite().getPosition());
                app.draw(murCreer.getM_mur());
            }
            if (creationMechant)
            {
                Mur mechantCreer (coordonnees, Vector2f (mario.getM_sprite().getPosition().x-5, mario.getM_sprite().getPosition().y-5),Color::Red);
                app.draw(mechantCreer.getM_mur());
            }
            for (std::vector<Point>::iterator it=pointsCrees.begin(); it!=pointsCrees.end(); ++it)     ///iterateur pour agir sur tous
            {
                app.draw(it->getM_point());      ///on dessine tous les points
            }
            for (std::vector<Mur>::iterator it=mursCrees.begin(); it!=mursCrees.end(); ++it)     ///iterateur pour agir sur tous
            {
                app.draw(it->getM_mur());      ///on dessine tous les points
            }
            for (std::vector<Mechant>::iterator it=mechantsCrees.begin(); it!=mechantsCrees.end(); ++it)     ///iterateur pour agir sur tous
            {
                it->deplacer();
                app.draw(it->getM_sprite());      ///on dessine tous les points
            }
        }

        for (std::vector<Mur>::iterator it=murs.begin(); it!=murs.end(); ++it)     ///iterateur pour agir sur tous
        {
            app.draw(it->getM_mur());      ///on dessine tous les murs
            if (!creation)
                mario.collision(*it);       ///et on gere les collisisions
        }
        for (std::vector<Point>::iterator it=points.begin(); it!=points.end(); ++it)     ///iterateur pour agir sur tous
        {
            app.draw(it->getM_point());      ///on dessine tous les points
            if (!creation)
                if (mario.Perso::collision(*it))
                    score++;    ///et on gere les collisisions
        }

        for (std::vector<Mechant>::iterator it=mechants.begin(); it!=mechants.end(); ++it)      ///iterateur pour agir sur tous
        {
            it->deplacer();
            app.draw(it->getM_sprite());        ///on deplace et dessine chaque méchants
            if (!creation)
            {
                mario.collision(*it);       ///on test la collision avec un méchant

                for (std::vector<Mur>::iterator ite=murs.begin(); ite!=murs.end(); ++ite)     ///iterateur pour agir sur tous
                {
                    it->collision(*ite);    /// collisions Mechant/Mur
                }
            }
        }

        mario.deplacer();
        app.draw(mario.getM_sprite());      ///on deplace et dessine mario

        app.setView(app.getDefaultView());
        texte.setPosition(20,20);
        app.draw (texte);

       /// app.draw(drawScore(mario.getM_sprite().getPosition(), dimensionsEcran, texte, score));  ///on affiche le score

        View vue = setVue(Vector2f(mario.getM_sprite().getPosition().x+mario.getM_dimensions().x/2,
                                   mario.getM_sprite().getPosition().y+mario.getM_dimensions().y/2), dimensionsEcran);    ///on centre la vue sur mario
        View miniMapView = setVue(Vector2f(500,500), Vector2f(1000,1000));    ///on centre la vue sur mario
        miniMapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
        vue.setViewport(sf::FloatRect(0, 0, 1, 1));
        app.setView(miniMapView);
        app.draw(mario.getM_sprite());

        app.setView(vue);
        app.draw(mario.getM_sprite());
        app.display();      ///on raffraichie l'image
        app.clear(couleurFond);
        /**app.setView(setVue(Vector2f(mario.getM_sprite().getPosition().x+mario.getM_dimensions().x/2,
                                   mario.getM_sprite().getPosition().y+mario.getM_dimensions().y/2), dimensionsEcran));    ///on centre la vue sur mario
        app.display();      ///on raffraichie l'image
        app.clear(couleurFond);**/
    }

    return 0;
}
