#include "Player.h"
#include "Ability.h"


Player::Player()
{
}
Player::Player(Mesh * tempmesh, Texture * temptext, glm::mat4 temptrans, Material * tempmat, int temphealth, float temprange) : Object(tempmesh, temptext, temptrans, tempmat)
{
	Health = temphealth;
	MeleeRange = temprange;
}


void Player::BaseAttack(Player * otherplayer)
{
	Melee->Attack(otherplayer);
}


glm::vec3 target;
float Player::getRange()
{
	return MeleeRange;
}
void Player::setHealth(float newhealth)
{
	Health = newhealth;
}
void Player::setAttack(Ability * abil)
{
	Melee = abil;
}
void Player::setAbility(Skillshot * abil)
{
	FirstAbility = abil;
}
void Player::skillshotAttack(Player * otherplayer, float directionangle)
{
	FirstAbility->Attack(otherplayer, directionangle);

}

float Player::getHealth()
{
	return Health;
}

void Player::update(float Dt)
{
	Melee->update();
	FirstAbility->update(Dt);
	lerpForRoll(Dt);
}

void Player::startRoll(float tempdistance)
{
	if (!p_isRolling) {
		float angle = glm::radians(this->getOrientation());
		float forx = this->getPositionV3().x + sin(angle) * tempdistance;
		float forz = this->getPositionV3().z + cos(angle) * tempdistance;

		this->rollTarget = glm::vec3(forx, this->getPositionV3().y, forz);
		this->rollStart = this->getPositionV3();
		p_isRolling = true;
	}
}

void Player::lerpForRoll(float Dt)
{
	if (p_isRolling) {
		if (rollLerp < 1) {
			rollLerp += 1 * Dt;
			glm::vec3 lerpedposition = glm::vec3(glm::lerp(this->rollStart, this->rollTarget, rollLerp));
			this->setPosition(lerpedposition);
		}
		else {
			p_isRolling = false;
			rollLerp = 0;
		}

	}
}
