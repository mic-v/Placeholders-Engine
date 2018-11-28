#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Math/math.h"
#include <string>
#include <vector>
#include <iostream>
#include "Entity.h"



class Player : public Entity
{
public:
	Player() = default;
	Player(std::string _HeroName, GLuint _HeroStrength, GLuint _HeroAgility, GLuint _HeroHealth, glm::vec3 _SpawnPosition);
	~Player() = default;

	bool attackCollision(glm::vec3 _pos1, glm::vec3 _pos2);
                     
	glm::vec3 checkLocations(Player &p1, Player &p2);

	std::string _Hero;
	
	GLuint getStrength(), getAgility(), getHealth();

	bool checkCooldown(float cooldown);

	glm::vec3 getMovement();
	
	void setMovement(glm::vec3 _currentPos);

	void setHealth(GLuint _Health);

	GLuint getMaxHealth();
	
	bool checkAbility(bool _Ability, GLuint _cooldownNumber);

	glm::mat4 cameraTransformPlayer;

	float getTime();

	void setTime();

private:

	GLuint _Strength, _Agility, _Health, _MaxHealth;

	GLuint _Cooldown;

	double _Time;

	bool _AbilityActive;

	//float x = 7.0f, y = 1.0f, z = 0.5f;
	glm::vec3 _Movement;

};