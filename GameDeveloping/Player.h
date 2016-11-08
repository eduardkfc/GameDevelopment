#pragma once
#include"Header.h"
using namespace sf;
class Player
{
private:
	float x, y, dx, dy, speed;
	int dir = 0;
	int dirdop = 0;
	String File;
	Image image;
	Texture texture;
	
	
public:
	Sprite sprite;
	Player(String F, int X, int Y)
	{
		speed =0.1;
		sprite.setOrigin(65 - 30, 93 - 30);
		File = F;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 112, 62, 91));
		texture.setSmooth(true);
		sprite.setPosition(x, y);
		
	}
	void moveSprite(float x, float y) { sprite.move(x, y); }
	Vector2f getSpritePos() { return sprite.getPosition(); }
	void setSpriteRotation(float rot) { sprite.setRotation(rot); }
	void setSpriteRect(int curframe) { sprite.setTextureRect(IntRect(62 * curframe, 8, 62, 91)); }
	float getSpriteRotation(float rot) { return sprite.getRotation(); }
	Vector2f getSpriteOrigin() { return sprite.getOrigin(); }
	float getSpeed(){ return speed; }
	
};