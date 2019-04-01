#pragma once
#include "Object.h"


//forward declare
class Ability;
class Skillshot;



class Player : public Object {

public:
	Player();
	Player(Mesh *tempmesh, Texture *temptext, glm::mat4 temptrans, Material *tempmat, int temphealth, float temprange, Object * Aim);
	float getRange();
	void setHealth(float newhealth);
	void setAttack(Ability* abil);
	void setFirstAbility(Skillshot* abil);
	void setSecondAbility(Skillshot* abil);

	bool BaseAttack(Player *otherplayer);
	bool skillshotAttack(Player *otherplayer, float directionangle);
	float getHealth();

	void update(float Dt);
	void startRoll(float tempdistance);
	void lerpForRoll(float Dt);
	void SwapSkillShot();
	Object * getPointer() {
		return Pointer;
	}
	bool Pressed2 = false;
	bool Pressed1 = false;
	
private:
	float Health;
	float MeleeRange;
	glm::vec3 rollTarget;
	glm::vec3 rollStart;
	Object * Pointer;
	float rollLerp = 0;
	bool p_isRolling = false;
	Ability *Melee;
	Skillshot *FirstAbility;
	Skillshot *SecondAbility;

	Skillshot *AbilPointer;
	float baseAttackTime = 0;


};