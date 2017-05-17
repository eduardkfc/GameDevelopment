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
	Texture ddIco, ssIco, ddCD,ssCD;
	Sprite ddIcon, ssIcon,ddCooldown,ssCooldown;
	Text workDD, workSS;
public:
	void init(int X, int Y, int W, int H)
	{
		ddIco.loadFromFile("images/doubledamage.jpg");
		ssIco.loadFromFile("images/superspeed.jpg");
		ddCD.loadFromFile("images/damagecd.jpg");
		ssCD.loadFromFile("images/speedcd.jpg");
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
		ddCooldown.setTexture(ddCD);
		ssCooldown.setTexture(ssCD);
		Healthtext.setFont(font);
		workDD.setFont(font);
		workSS.setFont(font);
		workDD.setOutlineThickness(1);
		workSS.setOutlineThickness(1);
		workDD.setOutlineColor(Color::Black);
		workSS.setOutlineColor(Color::Black);
	}
	void draw(int stat, RenderWindow &window, Player &p1)
	{
		current = stat;
		size.x = (current*maxW) / max;
		rect.setSize(size);
		rect.setPosition(p1.getSpritePos().x-45, p1.getSpritePos().y-90);
		rectBack.setPosition(p1.getSpritePos().x-45, p1.getSpritePos().y-90);
		convertHP = to_string(current);
		if (p1.getDDcooldown() == true) { convertDD = to_string(float(7.0 - float(p1.getDDtime())/1000)); }
		else convertDD = to_string(float(5.0 - float(p1.getDDtime())/1000));
		convertDD.erase(3);
		if (p1.getSScooldown() == true) { convertSS = to_string(float(4.0 - float(p1.getSpeedtime())/1000)); }
		else convertSS = to_string(float(2.0 - float(p1.getSpeedtime())/1000));
		convertSS.erase(3);
		workDD.setString(convertDD);
		workSS.setString(convertSS);
		Healthtext.setString(convertHP);
		Healthtext.setPosition(p1.getSpritePos().x -5 , p1.getSpritePos().y - 90);
		ddIcon.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 90);
		ddCooldown.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 90);
		ssIcon.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 180);
		ssCooldown.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 180);
		workDD.setPosition(p1.getSpritePos().x + 515, p1.getSpritePos().y + 110);
		workSS.setPosition(p1.getSpritePos().x + 515, p1.getSpritePos().y + 200);
		
		if (current < 70) { Healthtext.setFillColor(Color::Black); }
		if (current < 30) { Healthtext.setFillColor(Color::Red); }
		window.draw(rectBack);
		window.draw(rect);
		window.draw(Healthtext);
		if (p1.getDDcooldown() == true) { window.draw(ddCooldown); window.draw(workDD); }
		if (p1.getDDcooldown() == false) window.draw(ddIcon);
		if (p1.getSScooldown() == true) { window.draw(ssCooldown); window.draw(workSS); }
		if (p1.getSScooldown() == false) window.draw(ssIcon);
		if (p1.getActiveDD() == true) { window.draw(workDD); }
		if (p1.getActiveSS() == true) { window.draw(workSS); }
	}
};