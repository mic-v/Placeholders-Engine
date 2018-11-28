#include "Player.h"

Player::Player(std::string _HeroName, GLuint _HeroStrength, GLuint _HeroAgility, GLuint _HeroHealth, glm::vec3 _SpawnPosition)
{
	_Hero = _HeroName;
	_Strength = _HeroStrength;
	_Agility = _HeroAgility;
	_MaxHealth = _HeroHealth;
	_Health = _MaxHealth;
	cameraTransformPlayer = glm::translate(glm::vec3(_SpawnPosition));
	_Movement = _SpawnPosition;

}

bool Player::attackCollision(glm::vec3 _pos1, glm::vec3 _pos2)
{
	glm::vec3 Distance, point1, point2;
	float radius = 0.5f;
	float radius2 = 0.0f;
	Distance.x = _pos2.x - _pos1.x;
	Distance.y = _pos2.y - _pos1.y;
	Distance.z = _pos2.z - _pos1.z;
	
	/*point1.x = _pos1.x + 5.0f;
	point1.y = 1.0f;
	point1.z = _pos1.z + 5.0f;
	point2.x = _pos2.x + 5.0f;
	point2.y = 1.0f;
	point2.z = _pos2.z + 5.0f;*/

	//radius1.DistanceBetweenObj(point1, point2);

	float radii = (radius + radius2);
	

	if ((Distance.x * Distance.x) + (Distance.y + Distance.y) <= radii * radii) {
		//printf("Colliding");
		return true;
	}
return false;
}
//#include "Math/Vector3.h"
glm::vec3 Player::checkLocations(Player &p1, Player &p2)
{
	glm::vec3 cross;

	glm::vec3 v1 = p1.getMovement();
	glm::vec3 v2 = p2.getMovement();

	return glm::vec3(((v1.y * v2.z) - (v1.z*v2.y)), ((v1.z*v2.x) - (v1.x*v2.z)), ((v1.x*v2.y) - (v1.y*v2.x)));
}
	

GLuint Player::getStrength()
{
	
	return _Strength;
}

GLuint Player::getHealth()
{
	return _Health;
}

GLuint Player::getAgility()
{
	return _Agility;
}

bool Player::checkCooldown(float cooldown)
{
	if(_Time != 0){
		if (cooldown <= (glfwGetTime() - getTime())) {
			return true;
		}
		
	}
	return false;
}

glm::vec3 Player::getMovement()
{
	return _Movement;
}

void Player::setMovement(glm::vec3 _currentPos)
{
	cameraTransformPlayer = glm::translate(glm::vec3(_currentPos));
	_Movement = _currentPos;

}

void Player::setHealth(GLuint _currentHealth)
{
	_Health =_currentHealth;
}

GLuint Player::getMaxHealth()
{
	return _MaxHealth;
}

bool Player::checkAbility(bool _Ability, GLuint _cooldownNumber)
{
	if (_cooldownNumber = 0) {
		return true;
	}
	else {
		return false;
	}
}

float Player::getTime()
{
	return _Time;
}

void Player::setTime()
{
	_Time = glfwGetTime();
}




