#include "Game.h"

Game* Game::instance_ = nullptr;

float toRadii(float degrees)
{
	return degrees * (PI / 180.0f);
}

unsigned int loadTexture2(char const * path)
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


Game::Game()
{
}

Game::~Game()
{
}

Game & Game::instance()
{
	// TODO: insert return statement here
	if (instance_ == nullptr)
	{
		instance_ = new Game();
		return *instance_;
	}
	else
	{
		return *instance_;
	}
}

void Game::startUp()
{
	window_ = new Window("Plaho", 1280, 720);

	Shader program("./Shaders/passthrough.vs","Shaders/passthrough.fs");
	Shader ourShader("Shaders/4.2.texture.vs", "Shaders/4.2.texture.fs");
	sh = program;
	sh2 = new Shader("Shaders/4.2.texture.vs", "Shaders/4.2.texture.fs");
	//monkey.loadFromFile("./Contents/Monkey.obj");
	cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));
	cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);

	camera = new Camera(vec3(0.f, 0.f, 3.0f));

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	std::string my_str = "Contents/container2.png";
	diffuseMap = loadTexture2(my_str.c_str());
	std::string my_str2 = "Contents/container2_specular.png";
	specularMap = loadTexture2(my_str2.c_str());

	sh2->use();
	sh2->setInt("texture1", 0);
	sh2->setInt("texture2", 1);
}

void Game::shutDown()
{
	delete window_;
}

void Game::update()
{
	while (true)
	{
		window_->clear();
		if (window_->isKeyPressed(GLFW_KEY_ESCAPE))
			break;

		//		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE1);

		sh2->use();

		cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));
		cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);

		sh2->setMat4("uView", camera->getLookMatrix3());
		sh2->setMat4("uProj", cameraProjection);
		sh2->setMat4("uModel", mat4::translation(vec3(0.0f, 0.0f, 0.0f)));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//sh.setMat4("uView", camera->getLookMatrix3());
		//sh.setMat4("uProj", cameraProjection);
		//sh.setMat4("uModel", monkeyTransform);

		//sh.use();
		//sh.setMat4("uView", camera->getLookMatrix3());
		//sh.setMat4("uProj", cameraProjection);
		//sh.setMat4("uModel", cameraTransform);

		//glBindVertexArray(monkey.VAO);
		//glDrawArrays(GL_TRIANGLES, 0, monkey.getNumVertices());
		//glBindVertexArray(0);
		std::cout << " test" << std::endl;
		camera->processMouseMovement(1280.f / 2.0f, 720.f / 2.0f);

		window_->update();

		render();
	}
}

void Game::render()
{
	window_->poll();
}
