#include "Ability.h"

Ability::Ability()
{
	std::cout << "ABILITY CLASS NOT SETUP CORRECTLY, USING DEFAULT CONSTRUCTOR." << std::endl;

}

Ability::Ability(Player * wielder, float cooldown, float damage)
{
	Wielder = wielder; 
	Cooldown = cooldown;
	Damage = damage;
}

float Ability::getCooldown()
{
	return Cooldown;
}

float Ability::getDamage()
{
	return Damage;
}

float Ability::getTimeLeft()
{
	return timeLeft;
}



void Ability::setCooldown(float cooldown)
{
	Cooldown = cooldown;
}

void Ability::setDamage(float damage)
{
	Damage = damage;
}

void Ability::setTimeStore()
{
	timeStore = Cooldown + glfwGetTime();
}

void Ability::update()
{
	
	timeLeft = timeStore - glfwGetTime();
	if (timeLeft < 0.0f) {
		timeLeft = 0.0f;
	}
}

void Ability::Attack(Player * target)
{


	if (timeLeft <= 0.0f)
	{

		this->setTimeStore();
		float x = (target->getPositionV3().x - Wielder->getPositionV3().x);
		float z = (target->getPositionV3().z - Wielder->getPositionV3().z);
		
		if (sqrt((x*x) + (z*z)) <= Wielder->getRange()) {
			
			target->setHealth(target->getHealth() - Damage);
			std::cout << "hit" << std::endl;
		}
		else {
			std::cout << "attack missed" << std::endl;
		}
	}
	else {
		std::cout << "cooldown active" << std::endl;
	}
}

Skillshot::Skillshot()
{
}

Skillshot::Skillshot(Player * wielder, float cooldown, float damage, float projspeed, float projdist, float projradius, Object* projobj): Ability(wielder, cooldown, damage)
{
	projectileSpeed = projspeed;
	projectileDist = projdist;
	projectileRadius = projradius;
	projectileObject = projobj;
}

void Skillshot::Attack(Player * target)
{
	if (timeLeft <= 0.0f) {

		this->Target = target;
		this->setTimeStore();
		this->lerping = true;
		projectileObject->setActive(true);

		float theta = glm::radians(Wielder->getOrientation());
		projTarget = glm::vec3(sin(theta) * projectileDist, 0, cos(theta) * projectileDist);
		projectileObject->setPosition(Wielder->getPositionV3() + glm::vec3(sin(theta) * 1, 0, cos(theta) * 1));

	}




}
void Skillshot::update()
{

	timeLeft = timeStore - glfwGetTime();
	if (timeLeft < 0.0f) {
		timeLeft = 0.0f;
	}

	if (lerping == true) {
		if (this->lerpParam < 1.000000f) {

			
			this->lerpParam += projectileSpeed;

			

			projectileObject->setPosition(glm::lerp(projectileObject->getPositionV3(), projTarget, lerpParam));
			if (this->lerpParam >= 0.4f) {

				lerping = false;
			
			}


			float x = (Target->getPositionV3().x - projectileObject->getPositionV3().x);
			float z = (Target->getPositionV3().z - projectileObject->getPositionV3().z);
			if (sqrt((x*x) + (z*z)) <= projectileRadius && !hit) {
				
				Target->setHealth(Target->getHealth() - Damage);
				hit = true;
				lerping = false;
			}
			
		}
		
		
		
	}
	

	if (!lerping){
		lerpParam = 0.0f;
		projectileObject->setActive(false);
		hit = false;
	}


}