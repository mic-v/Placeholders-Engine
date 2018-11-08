#pragma once
#include "Shader.h"

//sh.sendUniformInt("uTex", 0);
//sh.sendUniformVec4("LightPosition", vec4(4.0f, 70.0f, 0, 1.0f));
////rgb value of the light(doesnt scale so values can be low)
//sh.sendUniformVec3("LightAmbient", vec3(0.95, 0.69, 0.25f));
////rgb value of light reflection
//sh.sendUniformVec3("LightDiffuse", vec3(0.7f, 0.5f, 0.2f));
////rgb value of shine, applied least liberally so values should be higher
//sh.sendUniformVec3("LightSpecular", vec3(0.95f, 0.69f, 0.25f));
//sh.sendUniformFloat("LightSpecularExponent", -5.0f);
//sh.sendUniformFloat("Attenuation_Constant", 0.0f);
//sh.sendUniformFloat("Attenuation_Linear", 0.1f);
//sh.sendUniformFloat("Attenuation_Quadratic", 0.01f);


class Light {
public:
	Light(){}
	Light(Shader *temp, vec4 pos, vec3 ambient, vec3 diffuse, vec3 spec);


	void LoadLight();

	void setuTex(int);
	//Sets light's position
	void setPosition(vec4);

	//Sets Light Ambient
	void setAmbient(vec3);

	//Sets Light Diffuse
	void setDiffuse(vec3);

	//Sets Light Specular
	void setSpecular(vec3);

	//Sets Specular Exponent
	void setExponent(float);

	//Sets Constant Attenuation
	void setConstant(float);

	//Sets Linear Attenuation
	void setLinear(float);

	//Sets Quadratic Attenuation
	void setQuadratic(float);

	//Sets uTex number(slot we want to use) DEFAULT = 0
	int getuTex();

	//Gets light's position
	vec4 getPosition();

	//Gets Light Ambient
	vec3 getAmbient();

	//Gets Light Diffuse
	vec3 getDiffuse();

	//Gets Light Specular
	vec3 getSpecular();

	//Gets Specular Exponent
	float getExponent();

	//Gets Constant Attenuation
	float getConstant();

	//Gets Linear Attenuation
	float getLinear();

	//Gets Quadratic Attenuation
	float getQuadratic();


private:
	Shader LightShader;
	int uTex = 0;
	vec4 Position;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float SpecularExponent;
	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;


};