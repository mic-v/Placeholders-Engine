#include "Light.h"


//Shader you want to use, position of light, ambient color, diffuse color, specular color
Light::Light(Shader *temp, vec4 _position, vec3 _ambient, vec3 _diffuse, vec3 _spec)
	/*LightShader(temp), Position(_position), Ambient(_ambient), Diffuse(_diffuse), Specular(_spec)*/
{
	LightShader = *temp;
	Position = _position;
	Ambient = _ambient;
	Diffuse = _diffuse;
	Specular = _spec;
	SpecularExponent = 1000.0f;
	ConstantAttenuation = 0.0f;
	LinearAttenuation = 0.1f;
	QuadraticAttenuation = 0.01f;
}


//SENDING INFO TO SHADERS
void Light::LoadLight() {
	

	LightShader.sendUniformInt("uTex", uTex);
	LightShader.sendUniformVec4("LightPosition", Position);
	//rgb value of the light(doesnt scale so values can be low)
	LightShader.sendUniformVec3("LightAmbient", Ambient);
	//rgb value of light reflection
	LightShader.sendUniformVec3("LightDiffuse", Diffuse);
	//rgb value of LightShaderine, applied least liberally so values LightShaderould be higher
	LightShader.sendUniformVec3("LightSpecular", Specular);
	LightShader.sendUniformFloat("LightSpecularExponent", SpecularExponent);
	LightShader.sendUniformFloat("Attenuation_Constant", ConstantAttenuation);
	LightShader.sendUniformFloat("Attenuation_Linear", LinearAttenuation);
	LightShader.sendUniformFloat("Attenuation_Quadratic", QuadraticAttenuation);

}



//SETTERS
void Light::setuTex(int temp) {
	uTex = temp;
}
void Light::setPosition(vec4 temp) {
	Position = temp;
}
void Light::setAmbient(vec3 temp) {
	Ambient = temp;
}
void Light::setDiffuse(vec3 temp) {
	Diffuse = temp;
}
void Light::setSpecular(vec3 temp) {
	Specular = temp;
}
void Light::setExponent(float temp) {
	SpecularExponent = temp;
}
void Light::setConstant(float temp) {
	ConstantAttenuation = temp;
}
void Light::setLinear(float temp) {
	LinearAttenuation = temp;
}
void Light::setQuadratic(float temp) {
	QuadraticAttenuation = temp;
}


//GETTERS
int Light::getuTex() {
	return uTex;
}
vec4 Light::getPosition() {
	return Position;
}
vec3 Light::getAmbient() {
	return Ambient;
}
vec3 Light::getDiffuse() {
	return Diffuse;
}
vec3 Light::getSpecular() {
	return Specular;
}
float Light::getExponent() {
	return SpecularExponent;
}
float Light::getConstant() {
	return ConstantAttenuation;
}
float Light::getLinear() {
	return LinearAttenuation;
}
float Light::getQuadratic() {
	return QuadraticAttenuation;
}