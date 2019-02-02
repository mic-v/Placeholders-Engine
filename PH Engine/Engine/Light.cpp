#include "Light.h"

int Light::totalLights = 0;

//Shader you want to use, position of light, ambient color, diffuse color, specular color
Light::Light(glm::vec4 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _spec)
	/*LightShader(temp), Position(_position), Ambient(_ambient), Diffuse(_diffuse), Specular(_spec)*/
{
	Position = _position;
	Ambient = _ambient;
	Diffuse = _diffuse;
	Specular = _spec;
	SpecularExponent = 1000.0f;
	ConstantAttenuation = 0.0f;
	LinearAttenuation = 0.1f;
	QuadraticAttenuation = 0.01f;



	stuff.LightPosition = Position;
	stuff.LightAmbient = Ambient;
	stuff.LightDiffuse = Diffuse;
	stuff.LightSpecular = Specular;
	stuff.LightSpecularExponent = SpecularExponent;
	stuff.Attenuation_Constant = ConstantAttenuation;
	stuff.Attenuation_Linear = LinearAttenuation;
	stuff.Attenuation_Quadratic = QuadraticAttenuation;
	thisLight = totalLights;
	totalLights++;
}



//SENDING INFO TO SHADERS
void Light::LoadLight(Shader *LightShader) {
	
	
	LightShader->sendUniformInt("uTex", uTex);
	GLuint location = LightShader->getUniformLocation("pointLights["+ std::to_string(thisLight) +"]");
	//glUniform1i(location, stuff);

	LightShader->sendUniformVec4("pointLights[" + std::to_string(thisLight) + "].LightPosition", Position);
	//rgb value of the light(doesnt scale so values can be low)
	LightShader->sendUniformVec3("pointLights[" + std::to_string(thisLight) + "].LightAmbient", Ambient);
	//rgb value of light reflection
	LightShader->sendUniformVec3("pointLights[" + std::to_string(thisLight) + "].LightDiffuse", Diffuse);
	//rgb value of LightShaderine, applied least liberally so values LightShaderould be higher
	LightShader->sendUniformVec3("pointLights[" + std::to_string(thisLight) + "].LightSpecular", Specular);
	LightShader->sendUniformFloat("pointLights[" + std::to_string(thisLight) + "].LightSpecularExponent", SpecularExponent);
	LightShader->sendUniformFloat("pointLights[" + std::to_string(thisLight) + "].Attenuation_Constant", ConstantAttenuation);
	LightShader->sendUniformFloat("pointLights[" + std::to_string(thisLight) + "].Attenuation_Linear", LinearAttenuation);
	LightShader->sendUniformFloat("pointLights[" + std::to_string(thisLight) + "].Attenuation_Quadratic", QuadraticAttenuation);
	
}



//SETTERS
void Light::setuTex(int temp) {
	uTex = temp;
}
void Light::setPosition(glm::vec4 temp) {
	Position = temp;
	stuff.LightPosition = Position;
}
void Light::setAmbient(glm::vec3 temp) {
	Ambient = temp;
}
void Light::setDiffuse(glm::vec3 temp) {
	Diffuse = temp;
}
void Light::setSpecular(glm::vec3 temp) {
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
glm::vec4 Light::getPosition() {
	return Position;
}
glm::vec3 Light::getAmbient() {
	return Ambient;
}
glm::vec3 Light::getDiffuse() {
	return Diffuse;
}
glm::vec3 Light::getSpecular() {
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