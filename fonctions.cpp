#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <ctime>
#include <fstream>

using namespace std;
using namespace sf;

View setVue (Vector2f const& position, Vector2f const& dimensionsEcran)
{
    View vue;
    vue.setCenter(position);
    vue.setSize(dimensionsEcran);
    return vue;
}

sf::Text drawScore (Vector2f const& position, Vector2f const& dimensionEcran, Text& texte, int const& score)
{
    texte.setPosition(position.x-(dimensionEcran.x/2-50),position.y-(dimensionEcran.y/2-50));
    /**if( texte.getPosition().x<10)
        texte.setPosition(10,texte.getPosition().y);
    if (texte.getPosition().y<10)
        texte.setPosition(texte.getPosition().x,10);**/
    ostringstream tt;      ///convertir un int en texte affichable
    tt << score;
    texte.setString(tt.str());
    return texte;
}

Vector2f placerObjet (Vector2f const& position, string path)
{
    ofstream Fichier (path.c_str(),ios::app);    ///ouverture du fichier
    if (Fichier)
    {
        Fichier<<endl<<position.x<<endl;
        Fichier<<position.y<<endl;
    }
    else
        cout<<"erreur fichier "<<path<<endl;
    return position;
}
