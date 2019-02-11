#pragma once
#include "Object.h"
#include <btBulletDynamicsCommon.h>


class Player : public Object {

public:
	Player();
	Player(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans, int temphealth, float temprange) : Object(tempmesh, temptext, temptrans) {
		Health = temphealth;
		Range = temprange;
	}

	void BaseAttack(Player *otherplayer);
	void skillshotAttack(Player *otherplayer, Object *skillshotMesh, float t, bool check);
	float getHealth();
private:
	float Health;
	float Range;
	float skillshotRange;
	btVector3 player;
	btVector3 skillshot;
	float baseAttackTime = 0;


};