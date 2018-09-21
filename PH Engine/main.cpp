#include <iostream>


#include "Engine/Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Engine/stb_image.h"

#include "Engine/Math/math.h"
#include "Engine/Shader.h"
#include "../External/glm/glm/glm.hpp"
#include "../External/glm/glm/gtc/matrix_transform.hpp"
#include "../External/glm/glm/gtx/rotate_vector.hpp"
#include "../External/glm/glm/gtc/type_ptr.hpp"

using namespace plaho;
using namespace graphics;

unsigned int loadTexture(const char *path);

int main()
{
	Window window("Plaho", 1280, 720);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	//Shader lightingShader("Shaders/1.colors.vs", "Shaders/1.colors.fs");
	//Shader lampShader("Shaders/1.lamp.vs", "Shaders/1.lamp.fs");
	//Shader lightingShader("1.colors.vs", "1.colors.fs");
	//Shader lampShader("1.lamp.vs", "1.lamp.fs");
	Shader ourShader("4.2.texture.vs", "4.2.texture.fs");

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	std::string my_str = "container2.png";
	unsigned int diffuseMap = loadTexture(my_str.c_str());
	std::string my_str2 = "container2_specular.png";
	unsigned int specularMap = loadTexture(my_str2.c_str());

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	// or set it via the texture class
	ourShader.setInt("texture2", 1);

	//float vertices[] = {
	//	// positions          // normals           // texture coords
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	//};

	//vec3 cubePositions[] = {
	//	vec3(0.0f,  0.0f,  0.0f),
	//	vec3(2.0f,  5.0f, -15.0f),
	//	vec3(-1.5f, -2.2f, -2.5f),
	//	vec3(-3.8f, -2.0f, -12.3f),
	//	vec3(2.4f, -0.4f, -3.5f),
	//	vec3(-1.7f,  3.0f, -7.5f),
	//	vec3(1.3f, -2.0f, -2.5f),
	//	vec3(1.5f,  2.0f, -2.5f),
	//	vec3(1.5f,  0.2f, -1.5f),
	//	vec3(-1.3f,  1.0f, -1.5f)
	//};
	//// positions of the point lights
	//vec3 pointLightPositions[] = {
	//	vec3(0.7f,  0.2f,  2.0f),
	//	vec3(2.3f, -3.3f, -4.0f),
	//	vec3(-4.0f,  2.0f, -12.0f),
	//	vec3(0.0f,  0.0f, -3.0f)
	//};

	//unsigned VBO, cubeVAO;
	//glGenVertexArrays(1, &cubeVAO);
	//glGenBuffers(1, &VBO);

	//glBindVertexArray(cubeVAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//unsigned int lightVAO;
	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);

	////glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//// load textures (we now use a utility function to keep the code more organized)
	//// -----------------------------------------------------------------------------
	//std::string my_str = "container2.png";
	//unsigned int diffuseMap = loadTexture(my_str.c_str());
	//std::string my_str2 = "container2_specular.png";
	//unsigned int specularMap = loadTexture(my_str2.c_str());

	//lightingShader.use();
	//lightingShader.setInt("material.diffuse", 0);
	//lightingShader.setInt("material.specular", 1);

	while (!window.closed())
	{
		window.clear();
		
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "PRESSED!" << std::endl;
		}
	//	//window.getMousePos();
	//	lightingShader.use();
	//	//lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	//	lightingShader.setFloat("material.shininess", 32.f);

	//	lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	//	lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	//	lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	//	lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	//	lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
	//	lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	//	lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	//	lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);

	//	lightingShader.setVec3("pointLights[0].ambient", 0.2f,0.2f,0.2f);
	//	lightingShader.setVec3("pointLights[1].ambient", 0.2f,0.2f,0.2f);
	//	lightingShader.setVec3("pointLights[2].ambient", 0.2f,0.2f,0.2f);
	//	lightingShader.setVec3("pointLights[3].ambient", 0.2f,0.2f,0.2f);

	//	lightingShader.setVec3("pointLights[0].diffuse", 0.5f,0.5f,0.5f);
	//	lightingShader.setVec3("pointLights[1].diffuse", 0.5f,0.5f,0.5f);
	//	lightingShader.setVec3("pointLights[2].diffuse", 0.5f,0.5f,0.5f);
	//	lightingShader.setVec3("pointLights[3].diffuse", 0.5f,0.5f,0.5f);

	//	lightingShader.setVec3("pointLights[0].specular", 1.0f,1.0f,1.0f);
	//	lightingShader.setVec3("pointLights[1].specular", 1.0f,1.0f,1.0f);
	//	lightingShader.setVec3("pointLights[2].specular", 1.0f,1.0f,1.0f);
	//	lightingShader.setVec3("pointLights[3].specular", 1.0f,1.0f,1.0f);

	//	lightingShader.setFloat("pointLights[0].constant", 1.0f);
	//	lightingShader.setFloat("pointLights[1].constant", 1.0f);
	//	lightingShader.setFloat("pointLights[2].constant", 1.0f);
	//	lightingShader.setFloat("pointLights[3].constant", 1.0f);

	//	lightingShader.setFloat("pointLights[0].linear", 0.09f);
	//	lightingShader.setFloat("pointLights[1].linear", 0.09f);
	//	lightingShader.setFloat("pointLights[2].linear", 0.09f);
	//	lightingShader.setFloat("pointLights[3].linear", 0.09f);

	//	lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
	//	lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
	//	lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
	//	lightingShader.setFloat("pointLights[3].quadratic", 0.032f);

	//	//lightingShader.setVec3("light.position", lightPos);
	//	////lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
	//	//lightingShader.setVec3("viewPos", camera.position);

	//	//lightingShader.setVec3("light.objectColour", 1.0f, 0.5f, 0.31f);
	//	//lightingShader.setVec3("light.lightColour", 1.0f, 1.0f, 1.0f);
	//	//lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	//	//lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	//	//lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


	//	//lightingShader.setFloat("light.constant", 1.0f);
	//	//lightingShader.setFloat("light.linear", 0.09f);
	//	//lightingShader.setFloat("light.quadratic", 0.032f);

	//	//glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.f);
	//	//glm::mat4 view = camera.getLookMatrix();

	//	//lightingShader.setMat4("projection", projection);
	//	//lightingShader.setMat4("view", view);
	//	//glm::perspective()
	///*	glm::mat4 model;*/
	//	//mat44 proj = mat44::perspective(45.f, 720 / 1280, 0.1f, 100.0f);
	//	mat44 model;
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, specularMap);
	//	glBindVertexArray(cubeVAO);
	//	for (unsigned int i = 0; i < 10; i++)
	//	{
	//		float angle = 20.0f * i;
	//		/*model = glm::translate(model, cubePositions[i]);*/
	//		/*model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));*/
	//		model = mat44::rotation(angle, vec3(1.0f, 0.3f, 0.5f));
	//		lightingShader.setMat4("model", model);

	//		glDrawArrays(GL_TRIANGLES, 0, 36);
	//	}
	//	lampShader.use();
	//	//lampShader.setMat4("projection", projection);
	//	//lampShader.setMat4("view", view);
	//	glBindVertexArray(lightVAO);
	//	for (unsigned int i = 0; i < 4; i++)
	//	{
	//		model = mat44();
	//		lampShader.setMat4("model", model);
	//		glDrawArrays(GL_TRIANGLES, 0, 36);
	//	}
				// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// render container
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.update();

		/*glDrawArrays(GL_ARRAY_BUFFER, 0, 6);*/
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	return 0;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}