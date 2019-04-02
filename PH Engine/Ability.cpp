#include "Ability.h"

int EnemyAttackMissPtr = 0;
Ability::Ability()
{
	//std::cout << "ABILITY CLASS NOT SETUP CORRECTLY, USING DEFAULT CONSTRUCTOR." << std::endl;

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

bool Ability::Attack(Player * target)
{


	if (timeLeft <= 0.0f)
	{

		this->setTimeStore();
		float x = (target->getPositionV3().x - Wielder->getPositionV3().x);
		float z = (target->getPositionV3().z - Wielder->getPositionV3().z);

		if (sqrt((x*x) + (z*z)) <= Wielder->getRange()) {

			target->setHealth(target->getHealth() - Damage);
			//std::cout << "hit" << std::endl;
		}
		else {
			//std::cout << "attack missed" << std::endl;
		}
		return true;
	}
	else {
		//std::cout << "cooldown active" << std::endl;
	}
	return false;
}

Skillshot::Skillshot()
{
}

Skillshot::Skillshot(Player * wielder, float cooldown, float damage, float projspeed, float projdist, float projradius, Object* projobj) : Ability(wielder, cooldown, damage)
{
	projectileSpeed = projspeed;
	projectileDist = projdist;
	projectileRadius = projradius;
	projectileObject = projobj;
}

bool Skillshot::Attack(Player * target, float direction)
{
	if (timeLeft <= 0.0f) {

		projDirection = direction;

		this->Target = target;
		this->setTimeStore();
		this->lerping = true;
		projectileObject->setActive(true);

		float theta = glm::radians(direction);

		projectileObject->setOrientation(-projectileObject->getOrientation());
		projectileObject->setOrientation(direction + 255.0f);
		projTarget = glm::vec3(Wielder->getPositionV3().x + sin(theta) * projectileDist, Wielder->getPositionV3().y + 1.0f, Wielder->getPositionV3().z + cos(theta) * projectileDist);
		projStart = Wielder->getPositionV3() + glm::vec3(sin(theta), 1.0f, cos(theta));
		projectileObject->setPosition(projStart);

		return true;
	}

	return false;




}
glm::vec3 lerp(glm::vec3 start, glm::vec3 end, float t) {
	return (start + t * (end - start));
}
void Skillshot::update(float Dt)
{

	timeLeft = timeStore - glfwGetTime();
	if (timeLeft < 0.0f) {
		timeLeft = 0.0f;
	}

	if (lerping) {
		if (this->lerpParam < 1.000000f) {


			this->lerpParam += projectileSpeed * Dt;



			projectileObject->setPosition(lerp(projStart, projTarget, lerpParam));
			if (this->lerpParam >= 1.0f) {

				lerping = false;

			}


			float x = (projectileObject->getPositionV3().x - Target->getPositionV3().x);
			float z = (projectileObject->getPositionV3().z - Target->getPositionV3().z);
			float rad1 = projectileRadius;
			float rad2 = Target->getRadius();
			float dist = rad1 + rad2;
			if (sqrt((x*x) + (z*z)) <= sqrt(dist * dist) && !hit) {

				Target->setHealth(Target->getHealth() - Damage);
				hit = true;
				lerping = false;
			}

		}



	}

	if (!lerping) {
		if (Target != nullptr && lerpParam >= 1.0f) {
			if (!hit && Target->ReturnSound == nullptr) {
				Target->Override = true;
				Target->ReturnSound = Target->EnemyAttackMissSounds[EnemyAttackMissPtr];
				EnemyAttackMissPtr++;
				if (EnemyAttackMissPtr > Target->EnemyAttackMissSounds.size() - 1) {
					EnemyAttackMissPtr = 0;
				}
			}
		}
		lerpParam = 0.0f;
		projectileObject->setActive(false);

		//projectileObject->setRotationY(glm::radians(-projDirection));
		hit = false;
	}


}