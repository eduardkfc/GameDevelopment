#pragma once
#include "Header.h"
class HUD
{
private:
	RectangleShape rect;
	RectangleShape rectBack;
	Vector2f pos;
	Vector2f size;
	Font font;
	Text Healthtext;
	Color c;
	int maxW;
	int max, current;
	string convertHP, convertDD, convertSS;
	Texture ddIco, ssIco;
	Sprite ddIcon, ssIcon;
	Text workDD, workSS;
public:
	void init(int X, int Y, int W, int H)
	{
		ddIco.loadFromFile("images/doubledamage.jpg");
		ssIco.loadFromFile("images/superspeed.jpg");
		font.loadFromFile("font.ttf");
		c = Color::Green;
		max = 100;
		pos.x = X;
		pos.y = Y;
		maxW = W;
		size.y = H;
		size.x = W;
		rect.setPosition(X, Y);
		rect.setFillColor(c);
		Healthtext.setCharacterSize(15);
		rectBack.setPosition(X, Y);
		rectBack.setSize(size);
		rectBack.setOutlineThickness(2);
		rectBack.setOutlineColor(Color::Black);
		ddIcon.setTexture(ddIco);
		ssIcon.setTexture(ssIco);
		Healthtext.setFont(font);
		workDD.setFont(font);
		workSS.setFont(font);
		workDD.setOutlineThickness(1);
		workSS.setOutlineThickness(1);
		workDD.setOutlineColor(Color::Black);
		workSS.setOutlineColor(Color::Black);
	}
	void draw(int stat, RenderWindow &window, Player &p1,Clock &Speedtimer,Clock &DDtimer,bool &activeDD,bool &activeSpeed, int &ddtime,int &speedtime)
	{
		current = stat;
		size.x = (current*maxW) / max;
		rect.setSize(size);
		rect.setPosition(p1.getSpritePos().x-45, p1.getSpritePos().y-90);
		rectBack.setPosition(p1.getSpritePos().x-45, p1.getSpritePos().y-90);
		convertHP = to_string(current);
		convertDD = to_string(ddtime);
		convertSS = to_string(speedtime);
		workDD.setString(convertDD);
		workSS.setString(convertSS);
		Healthtext.setString(convertHP);
		Healthtext.setPosition(p1.getSpritePos().x -5 , p1.getSpritePos().y - 90);
		ddIcon.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 90);
		ssIcon.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 180);
		workDD.setPosition(p1.getSpritePos().x + 525, p1.getSpritePos().y + 110);
		workSS.setPosition(p1.getSpritePos().x + 525, p1.getSpritePos().y + 200);
		if (current < 70) { Healthtext.setFillColor(Color::Black); }
		if (current < 30) { Healthtext.setFillColor(Color::Red); }
		window.draw(rectBack);
		window.draw(rect);
		window.draw(Healthtext);
		window.draw(ddIcon);
		window.draw(ssIcon);
		if (activeDD == true) { window.draw(workDD); }
		if (activeSpeed == true) { window.draw(workSS); }
	}
};