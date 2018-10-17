#include <SFML/Graphics.hpp>

class MoveParticles
{
public:
    virtual void  moveTo(float x, float y)  = 0;
    virtual float getX()              const = 0;
    virtual float getY()              const = 0;
public:
    virtual ~MoveParticles() {};
};

class Player : public MoveParticles
{
public:
    Player(float PosX, float PosY) : mPosX(PosX), mPosY(PosY)
    { 
        texture.loadFromFile("resources/soldier1.png");
        sprite.setTexture(texture);
        sprite.setPosition(mPosX, mPosY);
    }
    virtual ~Player() {};
public:
    virtual float   getX() const override;
    virtual float   getY() const override;
    virtual void  moveTo(float x, float y) override;
    sf::Sprite sprite;
private:
    sf::Texture texture;
    float mPosX, mPosY;
};