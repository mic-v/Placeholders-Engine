#include "Player.h"

Player::Player()
{
}

void Player::BaseAttack(Player * otherplayer)
{
	float x = (otherplayer->getPositionV3().x - this->getPositionV3().x);
	float z = (otherplayer->getPositionV3().z - this->getPositionV3().z);
	if (glfwGetTime() >= baseAttackTime + 5.0f) {
		if (sqrt((x*x) + (z*z)) <= Range) {
			baseAttackTime = glfwGetTime();
			otherplayer->Health -= 5;
			std::cout << "hit" << std::endl;
		}
	}
	else {
		std::cout << "not hit" << std::endl;
	}
}

float Player::getHealth()
{
	return Health;
}
