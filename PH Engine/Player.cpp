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

void Player::skillshotAttack(Player * otherplayer, Object * skillshotMesh, float t, bool check)
{
	if (check == false) {
		player = btVector3(this->getPositionV3().x, this->getPositionV3().y, this->getPositionV3().z);
	}
	double angleBetweenPlayers = glm::normalizeDot(this->getPositionV3(), otherplayer->getPositionV3());
	std::cout << angleBetweenPlayers << std::endl;
	//btVector3 player = btVector3(this->getPositionV3().x, this->getPositionV3().y, this->getPositionV3().z);
	//btVector3 skillshot = btVector3(this->getPositionV3().x, this->getPositionV3().y, this->getPositionV3().z);
	skillshot = player;
	skillshot.setX(skillshot.getX() + 10.0f);

	btVector3 lp = lerp(btVector3(player), btVector3(skillshot), t);

		skillshotMesh->setPosition(glm::vec3(lp.x(), lp.y(), lp.z()));
	

	/*if (glfwGetTime() >= baseAttackTime + 5.0f) {
		if (sqrt((x*x) + (z*z)) <= Range) {
			baseAttackTime = glfwGetTime();
			otherplayer->Health -= 5;
			std::cout << "hit" << std::endl;
		}
	}
	else {
		std::cout << "not hit" << std::endl;
	}*/
}

float Player::getHealth()
{
	return Health;
}
