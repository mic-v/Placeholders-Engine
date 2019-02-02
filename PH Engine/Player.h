#pragma once
#include "Object.h"


class Player : public Object {

public:
	Player();
	Player(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans, int temphealth, float temprange) : Object(tempmesh, temptext, temptrans) {
		Health = temphealth;
		Range = temprange;
	}

	void BaseAttack(Player *otherplayer);
	float getHealth();
private:
	float Health;
	float Range;

	float baseAttackTime = 0;


};