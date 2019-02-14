#pragma once
#include "Player.h"


class Ability {
public:

	Ability();

	Ability(Player* wielder, float cooldown, float damage);
		 

	float getCooldown();
	float getDamage();
	float getTimeLeft();

	void setCooldown(float cooldown);
	void setDamage(float damage);
	void setTimeStore();

	virtual void update();

	virtual void Attack(Player* target);

protected:

	float Cooldown;
	float Damage;
	float timeStore = 0;
	float timeLeft = 0;

	Player* Wielder = nullptr;
	Player* Target = nullptr;



};


class Skillshot : public Ability {
public:

	Skillshot();

	Skillshot(Player* wielder, float cooldown, float damage, float projspeed, float projdist, float projradius, Object* projobj);

	void Attack(Player* target);

	void update();

private:



	Object* projectileObject;
	float lerpParam = 0;
	float projectileSpeed;
	glm::vec3 projTarget = glm::vec3(0);
	//how far the projecile goes, will be dynamic
	float projectileDist;
	float projectileRadius;
	bool hit = false;
	bool lerping = false;


};