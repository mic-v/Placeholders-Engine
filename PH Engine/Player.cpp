#include "Player.h"
#include "Ability.h"


int AttackPtr = 0;

int NothingPtr = 0;
int DeathPtr = 0;

Player::Player()
{
}
Player::Player(Mesh * tempmesh, Texture * temptext, glm::mat4 temptrans, Material * tempmat, int temphealth, float temprange, Object* Aim) : Object(tempmesh, temptext, temptrans, tempmat)
{
	Health = temphealth;
	MeleeRange = temprange;
	Pointer = Aim;
}


bool Player::BaseAttack(Player * otherplayer)
{
	return Melee->Attack(otherplayer);
}



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
void Player::setFirstAbility(Skillshot * abil)
{
	FirstAbility = abil;
	AbilPointer = FirstAbility;
}
void Player::setSecondAbility(Skillshot * abil)
{
	SecondAbility = abil;

}
bool Player::skillshotAttack(Player * otherplayer, float directionangle)
{
	if (AbilPointer->Attack(otherplayer, directionangle)) {
		ReturnSound = AttackSounds[AttackPtr];
		AttackPtr++;
		if (AttackPtr > AttackSounds.size() - 1) {
			AttackPtr = 0;
		}
		return true;
	}
	return false;
}

float Player::getHealth()
{
	return Health;
}

void Player::update(float Dt)
{
	Melee->update();
	FirstAbility->update(Dt);
	SecondAbility->update(Dt);
	lerpForRoll(Dt);
	SoundPos = FMOD_VECTOR{ this->getPositionV3().x, this->getPositionV3().y, this->getPositionV3().z };
	this->AudioTimer += Dt;

	if (this->AudioTimer >= 30.0f) {
		this->AudioTimer = 0;
		if (ReturnSound == nullptr) {
			ReturnSound = NothingSounds[NothingPtr];
			NothingPtr++;
			if (NothingPtr > NothingSounds.size() - 1) {
				NothingPtr = 0;
			}
		}
	}

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
			glm::vec3 originalpos = this->getPositionV3();
			glm::vec3 lerpedposition = glm::vec3(glm::lerp(this->rollStart, this->rollTarget, rollLerp));
			this->setPosition(lerpedposition);
			if (this->checkCollisions()) {
				this->setPosition(originalpos);
			}

		}
		else {
			p_isRolling = false;
			rollLerp = 0;
		}

	}
}

void Player::SwapSkillShot()
{

	if (AbilPointer == FirstAbility) {
		AbilPointer = SecondAbility;
	}
	else {
		AbilPointer = FirstAbility;
	}
}
