#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include<string>
#include<sstream>
#include "Perso.h"

using namespace sf;
using namespace std;

Mur::Mur(Vector2f position, Vector2f point2, Color couleur)
{
    m_mur.setSize(Vector2f(abs(point2.x-position.x),abs(point2.y-position.y)));
    if (point2.x < position.x)
        position.x = point2.x;
    if (point2.y < position.y)
        position.y = point2.y;
    m_mur.setPosition(position);
    m_mur.setFillColor(couleur);
}
Mur::Mur (int tab [4], Color couleur ) : Mur(Vector2f(tab[0], tab[1]), Vector2f(tab[2], tab[3]), couleur)
{

}
void Mur::creerTableau(int tab[])
{
    tab[0] = m_mur.getPosition().x;
    tab[1] = m_mur.getPosition().y;
    tab[2] = m_mur.getSize().x+tab[0];
    tab[3] = m_mur.getSize().y+tab[1];
}

RectangleShape Mur::getM_mur ()
{
    return m_mur;
}


Point::Point(Vector2f position, int rayon, Color couleur)
{
    m_point.setRadius(rayon);
    m_point.setPosition(position);
    m_point.setFillColor(couleur);
}

Point::Point(int tab[2], int rayon, Color couleur) : Point(Vector2f(tab[0],tab[1]), rayon, couleur)
{

}

void Point::creerTableau(int tab[2])
{
    tab[0] = m_point.getPosition().x;
    tab[1] = m_point.getPosition().y;
}

CircleShape Point::getM_point()
{
    return m_point;
}

void Point::disparaitre()
{
    m_point.setFillColor(Color(34,177,76));
}


Perso::Perso(std::string path,Vector2f dimensions,int longeurAnimation,Vector2f position,int speed)
{
    if (!m_texture.loadFromFile(path))       //charger la feuille de sprite de mario
        std::cout<<"erreur chargement personnage \n";
    else
        m_sprite.setTexture(m_texture);

    m_dimensions=dimensions;
    m_longeurAnimation=longeurAnimation;
    m_timer.restart();
    m_animation.x=0;
    m_animation.y=Droite;
    m_sprite.setPosition(position);
    m_speed=speed;
    if (!m_bufferPoint.loadFromFile("sonsMario/piece.wav"))
        cout<<"error chargement son"<<endl;
    m_soundPoint.setBuffer(m_bufferPoint);
    m_soundPoint.setVolume(50);
}

void Perso::animer()
{
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(IntRect(m_animation.x*m_dimensions.x,m_animation.y*m_dimensions.y,m_dimensions.x,m_dimensions.y));   //decouper la feuille de sprite pour l'animation

    if ((m_timer.getElapsedTime().asMilliseconds()>=100) )
    {
        m_timer.restart();
        m_animation.x++;
        if (m_animation.x==m_longeurAnimation)
            m_animation.x=0;
    }
    if (m_sprite.getPosition().x<0)
        m_sprite.setPosition(0,m_sprite.getPosition().y);
    if (m_sprite.getPosition().y<0)
        m_sprite.setPosition(m_sprite.getPosition().x,0);
}

Sprite Perso::getM_sprite()
{
    return m_sprite;
}

Vector2f Perso::getM_dimensions()
{
    return m_dimensions;
}

bool Perso::collision(Perso& mechant)
{
    if ((std::abs((m_sprite.getPosition().x+m_dimensions.x/2)-(mechant.getM_sprite().getPosition().x+mechant.getM_dimensions().x/2))) < (m_dimensions.x/2+mechant.getM_dimensions().x/2))
        if ((std::abs((m_sprite.getPosition().y+m_dimensions.y/2)-(mechant.getM_sprite().getPosition().y+mechant.getM_dimensions().y/2))) < (m_dimensions.y/2+mechant.getM_dimensions().y/2))
        {
            return true;
        }
    return false;
}

bool Perso::collision (Mur& mur)
{
    if ((std::abs((m_sprite.getPosition().x+m_dimensions.x/2)-(mur.getM_mur().getPosition().x+mur.getM_mur().getSize().x/2))) < (m_dimensions.x/2+mur.getM_mur().getSize().x/2))
        if ((std::abs((m_sprite.getPosition().y+m_dimensions.y/2)-(mur.getM_mur().getPosition().y+mur.getM_mur().getSize().y/2))) < (m_dimensions.y/2+mur.getM_mur().getSize().y/2))
        {
            ///std::cout<<"collision ! \n";
            return true;
        }
    return false;
}

bool Perso::collision (Point& point)
{
    if ((std::abs((m_sprite.getPosition().x+m_dimensions.x/2)-(point.getM_point().getPosition().x+point.getM_point().getRadius()))) < (m_dimensions.x/2+point.getM_point().getRadius()))
    {
        if ((std::abs((m_sprite.getPosition().y+m_dimensions.y/2)-(point.getM_point().getPosition().y+point.getM_point().getRadius()))) < (m_dimensions.y/2+point.getM_point().getRadius()))
            if (point.getM_point().getFillColor()!=Color(34,177,76))
            {
                std::cout<<"cercle pris ! \n";
                point.disparaitre();   ///si collision, effacer le cercle et +1 point
                m_soundPoint.play();
                return true;
            }
    }
    return false;
}


Mario::Mario(Vector2f spawnPoint,std::string path,Vector2f dimensions,int longeurAnimation,int speed) : Perso(path,dimensions,longeurAnimation,spawnPoint,speed)
{
    m_spawnPoint=spawnPoint;
    if (!m_bufferPerdu.loadFromFile("sonPerdu.wav"))
        cout<<"error chargement son"<<endl;
    m_soundPerdu.setBuffer(m_bufferPerdu);
    m_soundPerdu.setVolume(50);
}

void Mario::deplacer()
{
    if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        m_sprite.move(0,m_speed);
        m_animation.y=Bas;
        std::cout<<"( "<<m_sprite.getPosition().x<<" , "<<m_sprite.getPosition().y<<" )"<<std::endl;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        m_sprite.move(0,-m_speed);
        m_animation.y=Haut;
        std::cout<<"( "<<m_sprite.getPosition().x<<" , "<<m_sprite.getPosition().y<<" )"<<std::endl;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        m_sprite.move(m_speed,0);
        m_animation.y=Droite;
        std::cout<<"( "<<m_sprite.getPosition().x<<" , "<<m_sprite.getPosition().y<<" )"<<std::endl;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        m_sprite.move(-m_speed,0);
        m_animation.y=Gauche;
        std::cout<<"( "<<m_sprite.getPosition().x<<" , "<<m_sprite.getPosition().y<<" )"<<std::endl;
    }
    else
        m_animation.x=0;
    this->animer();
}

bool Mario::collision(Mur& mur)
{
    if( this->Perso::collision(mur))
    {
        this->bloquer(mur);
    }
    return this->Perso::collision(mur);
}

void Mario::bloquer(Mur& mur)
{
    if (m_sprite.getPosition().x < mur.getM_mur().getPosition().x)     ///pour empecher le personnagede traverser l'objet
        m_sprite.setPosition(mur.getM_mur().getPosition().x-m_dimensions.x,m_sprite.getPosition().y);
    if (m_sprite.getPosition().x+m_dimensions.x > mur.getM_mur().getPosition().x+mur.getM_mur().getSize().x)
        m_sprite.setPosition(mur.getM_mur().getPosition().x+mur.getM_mur().getSize().x,m_sprite.getPosition().y);
    if (m_sprite.getPosition().y < mur.getM_mur().getPosition().y)
        m_sprite.setPosition(m_sprite.getPosition().x,mur.getM_mur().getPosition().y-m_dimensions.y);
    if (m_sprite.getPosition().y +m_dimensions.y > mur.getM_mur().getPosition().y+mur.getM_mur().getSize().y)
        m_sprite.setPosition(m_sprite.getPosition().x,mur.getM_mur().getPosition().y+mur.getM_mur().getSize().y);
}

bool Mario::collision(Mechant& mechant)
{
    if (this->Perso::collision(mechant))
    {
        cout<<"perdu ! \n";
        m_sprite.setPosition(m_spawnPoint);
        m_soundPerdu.play();
    }
    return this->Perso::collision(mechant);
}

Mechant::Mechant (sf::Vector2f position, Vector2f point2, int speed, std::string path, Vector2f dimensions, int longeurAnimation) : Perso(path,dimensions,longeurAnimation,position,speed)
{
    if (position.x<point2.x||position.y<point2.y)
    {
        m_point1=position;
        m_point2=point2;
    }
    else
    {
        m_point1=point2;
        m_point2=position;
    }
    if (m_point1.x==m_point2.x)
        m_animation.y=Bas;
}

Mechant::Mechant (int tab [4], int speed, std::string path, Vector2f dimensions, int longeurAnimation ) : Mechant(Vector2f(tab[0], tab[1]), Vector2f(tab[2], tab[3]), speed, path, dimensions, longeurAnimation)
{

}

void Mechant::creerTableau(int tab[])
{
    tab[0] = m_point1.x;
    tab[1] = m_point1.y;
    tab[2] = m_point2.x;
    tab[3] = m_point2.y;
}

void Mechant::deplacer()
{
    if (m_point1.y==m_point2.y)
    {
        if (m_animation.y==Droite)
            m_sprite.move(m_speed,0);
        if (m_animation.y==Gauche)
            m_sprite.move(-m_speed,0);
        if (m_sprite.getPosition().x>m_point2.x)
            m_animation.y=Gauche;
        if (m_sprite.getPosition().x<m_point1.x)
            m_animation.y=Droite;
    }
    else if (m_point1.x==m_point2.x)
    {
        if (m_animation.y==Bas)
            m_sprite.move(0,m_speed);
        if (m_animation.y==Haut)
            m_sprite.move(0,-m_speed);
        if (m_sprite.getPosition().y>m_point2.y)
            m_animation.y=Haut;
        if (m_sprite.getPosition().y<m_point1.y)
            m_animation.y=Bas;
    }
    this->animer();
}

bool Mechant::collision(Mur& mur)
{
    if( this->Perso::collision(mur))
    {
        this->inverser();
    }
    return this->Perso::collision(mur);
}

void Mechant::inverser()
{
    if (m_animation.y==Bas)
        m_animation.y=Haut;
    else if (m_animation.y==Haut)
        m_animation.y=Bas;
    else if (m_animation.y==Droite)
        m_animation.y=Gauche;
    else if (m_animation.y==Gauche)
        m_animation.y=Droite;
}
