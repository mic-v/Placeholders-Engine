#pragma once
#include "Object.h"


//forward declare
class Ability;
class Skillshot;

class Player : public Object {

public:
	Player();
	Player(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans, Material *tempmat, int temphealth, float temprange);
	float getRange();
	void setHealth(float newhealth);
	void setAttack(Ability* abil);
	void setAbility(Skillshot* abil);

	void BaseAttack(Player *otherplayer);
	void skillshotAttack(Player *otherplayer);
	float getHealth();

	void update();
private:
	float Health;
	float Range;
	float skillshotRange;

	Ability *Melee;
	Skillshot *FirstAbility;
	float baseAttackTime = 0;


};