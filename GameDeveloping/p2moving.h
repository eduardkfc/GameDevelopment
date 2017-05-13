#pragma once
#include "Header.h"

void p2moving(Player &p2,int &identify,vector <Bullet> &bulletsvector2p,Bullet &bullet)
{
	if (identify == 1)
	{
		bulletsvector2p.push_back(bullet);
	}
}