#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED


/**class Item
{
public :

protected :

};**/

class Mur
{
public :
    Mur (sf::Vector2f position, sf::Vector2f point2, sf::Color couleur = sf::Color::Yellow);
    Mur (int tab [4], sf::Color couleur = sf::Color::Yellow);
    sf::RectangleShape getM_mur ();
    void creerTableau(int tab[]);
private :
    sf::RectangleShape m_mur;
};

class Point
{
public :
    Point (sf::Vector2f position, int rayon=7, sf::Color couleur=sf::Color::Red);
    Point (int tab [], int rayon=7, sf::Color couleur=sf::Color::Red);
    void creerTableau(int tab[]);
    sf::CircleShape getM_point ();
    void disparaitre();
private :
    sf::CircleShape m_point;
};

class Perso
{
public:
    Perso (std::string path,sf::Vector2f dimensions,int longeurAnimation,sf::Vector2f position,int speed);
    void animer();
    sf::Sprite getM_sprite();
    sf::Vector2f getM_dimensions();
    virtual void deplacer()=0;
    bool collision (Mur& mur);
    bool collision (Perso& mechant);
    bool collision (Point& point);

protected :
    sf::Vector2f m_dimensions;
    sf::Vector2f m_animation;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    int m_longeurAnimation;
    sf::Clock m_timer;
    enum m_direction {Bas,Gauche,Droite,Haut};
    int m_speed;
    sf::Sound m_soundPoint;
    sf::SoundBuffer m_bufferPoint;
};

class Mechant : public Perso
{
public :
    Mechant (sf::Vector2f position, sf::Vector2f point2, int speed = 2, std::string path = "mechant.png", sf::Vector2f dimensions = sf::Vector2f(64,64), int longeurAnimation = 3);
    Mechant (int tab [4], int speed = 2, std::string path = "mechant.png", sf::Vector2f dimensions = sf::Vector2f(64,64), int longeurAnimation = 3);
    void creerTableau(int tab[]);
    void deplacer ();
    bool collision (Mur& mur);
    void inverser ();

private :
    sf::Vector2f m_point1;
    sf::Vector2f m_point2;
};

class Mario : public Perso
{
public :
    Mario (sf::Vector2f spawnPoint=sf::Vector2f(50,50),std::string path="spritesheet-mario2.png",sf::Vector2f dimensions=sf::Vector2f(50,68),int longeurAnimation=4,int speed=3);
    void deplacer();
    bool collision (Mur& mur);
    void bloquer(Mur& mur);
    bool collision(Mechant& mechant);

private :
    sf::Vector2f m_spawnPoint;
    sf::Sound m_soundPerdu;
    sf::SoundBuffer m_bufferPerdu;


};

#endif // PERSO_H_INCLUDED
