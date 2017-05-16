#pragma once
#include "Header.h"

void p2moving(Player &p2,int &hisIdentify,vector <Bullet> &bulletsvector2p,Bullet &bullet)
{
	if (hisIdentify == 1)
	{
		bulletsvector2p.push_back(bullet);
	}
}