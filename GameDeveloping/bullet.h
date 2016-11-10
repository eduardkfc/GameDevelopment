#pragma once
#include "Header.h"
class Bullet 
{
private:
	float x,y,speed,bulletrot,velocity_x,velocity_y;
	Vector2f direction;
	String File;
	Image image;
	Texture texture;
public:
	Sprite sprite;
	Bullet(String F, int X, int Y,Vector2f origin,Vector2f mousepos)
	{
		speed = 40;
		File = F;
		texture.loadFromFile(File);
		sprite.setTexture(texture);
		x = X; y = Y;
		texture.setSmooth(true);
		sprite.setPosition(x, y);
		bulletrot = (atan2(mousepos.y - sprite.getPosition().y, mousepos.x - sprite.getPosition().x) * 180 / 3.14159265)-4;
		sprite.setOrigin(origin.x-80,origin.y-75);
		sprite.setRotation(bulletrot);
		
	}
	void update()
	{
		velocity_x = cos(bulletrot/180* 3.14159265)*speed;
		velocity_y = sin(bulletrot / 180 * 3.14159265)*speed;
		sprite.move(velocity_x, velocity_y);
	}
	Vector2f getBulletSprPos() { return sprite.getPosition(); }

};