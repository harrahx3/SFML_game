#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include <vector>
#include <string>
#include <fstream>

sf::View setVue (Vector2f const& position, Vector2f const& dimensionsEcran);
sf::Text drawScore (sf::Vector2f const& position, Vector2f const& dimensionEcran, Text& texte, int const& score);
sf::Vector2f placerObjet (sf::Vector2f const& position, std::string path);


template <typename T>   /// Template permettant de creer un tableau d'objet avec les données du fichier path
std::vector <T> creerObjets (std::string path, int nbDonnees)   ///nbDonnees est le nombre de chiffres necessaire au constructeur de l'objet
{
    std::vector <T> objets;

    std::ifstream Fichier (path.c_str());    ///ouverture du fichier
    if (Fichier)    ///test de l'ouverture du fichier
    {
        std::string nba;

        while (getline(Fichier,nba))    ///tant qu'on n'est pas à la fin, on lit le fichier ligne par ligne
        {
            int tab [nbDonnees];
            while (nba == "")
            {
                if (!getline(Fichier,nba))   /// !! chaque ligne doit contenir un int !!
                {
                 Fichier.close();
                 return objets;
                }
            }   ///convertir un string en int
            tab[0]=atoi(nba.c_str());       /// Tableau contenant tous les parametres

            for (int i=1; i<nbDonnees; i++)     /// Si il faut plus d'une valeur, on continu à lire
            {
                do
                {
                    if (!getline(Fichier,nba))   /// !! chaque ligne doit contenir un int !!
                        break;
                }
                while (nba == "");      ///convertir un string en in
                tab[i]=atoi(nba.c_str());       /// Tableau contenant tous les parametres
            }
            T objet (tab);
            objets.push_back(objet);
        }
    }
    else
    {
        cout<<"erreur fichier "<<path<<endl;
    }
    Fichier.close();

    return objets;
}

template <typename T>   /// Template permettant de creer un tableau d'objet avec les données du fichier path
void enregistrer(std::vector <T> objets, std::string path, int nbDonnees)   ///nbDonnees est le nombre de chiffres necessaire au constructeur de l'objet
{
    std::ofstream Fichier (path.c_str(), ios::app);    ///ouverture du fichier
    if (Fichier)    ///test de l'ouverture du fichier
    {
        for (unsigned i=0; i<objets.size(); i++)
        {
            int tab [nbDonnees];
            objets[i].creerTableau(tab);
            for (int j=0; j<nbDonnees; j++)
            {
                Fichier<<tab[j]<<std::endl;
            }
            Fichier<<std::endl;
        }
    }
    else
    {
        cout<<"erreur fichier "<<path<<endl;
    }
    Fichier.close();
}

#endif // FONCTIONS_H_INCLUDED
