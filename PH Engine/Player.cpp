#include "Player.h"
#include "Ability.h"


Player::Player()
{
}
Player::Player(Mesh * tempmesh, Texture * temptext, glm::mat4 temptrans, Material * tempmat, int temphealth, float temprange) : Object(tempmesh, temptext, temptrans, tempmat)
{
	Health = temphealth;
	Range = temprange;
}


void Player::BaseAttack(Player * otherplayer)
{
	Melee->Attack(otherplayer);
}


glm::vec3 target;
float Player::getRange()
{
	return Range;
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
void Player::skillshotAttack(Player * otherplayer)
{
	FirstAbility->Attack(otherplayer);

}

float Player::getHealth()
{
	return Health;
}

void Player::update()
{
	Melee->update();
	FirstAbility->update();
}
