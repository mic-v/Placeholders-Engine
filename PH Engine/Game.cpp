#include "Game.h"

/*
This is the Asssignment 1 Cube Loader stuff. I've been trying to load the monkey
*/

Game* Game::_instance = nullptr;

const float mesh[] = {
	// Vertices start here:
	-1.0f, 	-1.0f, 	-1.0f, 	 // triangle 1, Vertex 1
	-1.0f, 	-1.0f, 	 1.0f, 	 // triangle 1, Vertex 2
	-1.0f, 	 1.0f, 	 1.0f, 	 // triangle 1, Vertex 3
	1.0f, 	 1.0f, 	-1.0f, 	 // triangle 2, Vertex 1
	-1.0f, 	-1.0f, 	-1.0f, 	 // triangle 2, Vertex 2
	-1.0f, 	 1.0f, 	-1.0f, 	 // triangle 2, Vertex 3
	1.0f, 	-1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	-1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	-1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	-1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	 1.0f, 	-1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	 1.0f, 	 1.0f,
	-1.0f, 	 1.0f, 	 1.0f,
	1.0f, 	-1.0f, 	 1.0f,
	// Colors start here:
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

const char* vertexShaderSource =
"#version 330\n"
"layout(location = 0) in vec3 mesh_position;\n"
"layout(location = 1) in vec3 mesh_color;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_projection;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"	gl_Position = u_projection * u_view * u_model * vec4(mesh_position, 1.0);\n"
"	color = mesh_color;\n"
"}\n";

const char* fragmentShaderSource =
"#version 330\n"
"in vec3 color;\n"
"out vec4 pixelColor;\n"
"void main() { pixelColor = vec4(color, 1.0f); }\n";


float toRadii(float degrees)
{
	return degrees * (PI / 180.0f);
}

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


Game::Game()
{
}

Game::~Game()
{
}

/*
	This is the Singleton Pattern. Read more here:
	http://gameprogrammingpatterns.com/singleton.html
	Essentially, make sures there is only one instance of a certain class
	I wanted to practice it so I decided to use this pattern for Game. You don't have to follow thi
	for every class
*/
Game & Game::instance()
{
	// TODO: insert return statement here
	if (_instance == nullptr)
	{
		_instance = new Game();
		return *_instance;
	}
	else
	{
		return *_instance;
	}
}

void Game::startUp()
{
	_window = new Window("Plaho", 1280, 720);
	//camera = new Camera(vec3(0.f, 0.f, 3.0f));
	_camera = &_window->camera;
	cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));
	cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);
<<<<<<< HEAD
=======
	
	sh = Shader("Shaders/passthrough.vs", "Shaders/passthrough.fs");

	monkey = Mesh();
	monkey.loadFromFile("Contents/Monkey.obj");


	
>>>>>>> 9096ee947a7a11d461abc4abc75ceb50f361db4a

	//glGenVertexArrays(
	//	1,					// We only want to generate 1 VAO.
	//	&VAO);				// Address of the variable where OpenGL will output the new handle.
	//glBindVertexArray(VAO); // Binding will allow subsequent openGL calls to affect this VAO.

	//// Create Vertex Buffer Object (VBO) and send mesh to VRAM.
	//glGenBuffers(1, &VBO);
	//glBindBuffer(
	//	GL_ARRAY_BUFFER,	// The type of the buffer. Meshes use GL_ARRAY_BUFFER.
	//	VBO);				// The handle to the Vertex Buffer Object that we want bound.

	//// Since we bound the VBO, this glBufferData() will upload data to it.
	//glBufferData(
	//	GL_ARRAY_BUFFER,	// Same type as the glBindBuffer call.
	//	sizeof(mesh),		// The number of Bytes to upload (NOT the number of elements).
	//	mesh,				// A pointer to the start of the data to upload.
	//	GL_STATIC_DRAW);	// This usage hint allows openGL to place the data in the best place.
	//						// "Static" means we do not intend to update the mesh after uploading it.
	//						// "Draw" means we intend to use the buffer for drawing to the screen.

	//// Now we setup our Streams. Streams describe the data inside of a VBO.
	//// We will need two streams (one for each vertex attribute)
	//// Stream 0 -> Vertices		(Matches with 'in vec3 mesh_position' in our vertex shader)
	//// Stream 1 -> Colors		(Matches with 'in vec3 mesh_color' in our vertex shader)

	//// Enable the streams we want OpenGL to actually use.
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//// Describe to OpenGL where to find data for stream 0 (mesh_position).
	//glVertexAttribPointer(
	//	0,								// Stream ID
	//	3,								// Number of Elements (3 floats in a vertex -> vec3)
	//	GL_FLOAT,						// The type of our data (Same as our mesh array at the top of the file)
	//	GL_FALSE,						// NOT vector normalization. Should be false unless you KNOW you need this.
	//	0,								// Step in bytes to the next vertex. 0 = tightly packed with no gaps.
	//	reinterpret_cast<void*>(0));	// Where does the data start in the VBO? 0 = start of buffer data.

	//// Same as above except that Stream ID = 1 and the start of the data is after all the vertices.
	//// Size in bytes of vertex data = size of a float * 3 floats per vertex * 3 vertices per triangle * 12 triangles.
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(float) * 3 * 3 * 12));

	//// Temp variable to store the result of our "Did you compile?" queries.
	//int success = GL_FALSE;

	//// Load shaders and compile them into a single Program object...
	//// First, create the Program object handle.
	//shaderProgram = glCreateProgram();

	//// Create Vertex Shader...
	//vertShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(
	//	vertShader,				// Which shader is this for?
	//	1,						// We are only sending 1 string.
	//	&vertexShaderSource,	// Pointer to the string containing the Vertex Shader's source code.
	//	nullptr);				// We don't need to specify an explicit size, OpenGL will stop reading at the null character.

	//// Ask the drivers to compile the source code to Assembly code which the GPU can execute.
	//// (Similar to how we must compile our C++ source code to a .exe before we can run it)
	//glCompileShader(vertShader);

	//// Ask OpenGL if it compiled successfully.
	//glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	//if (success == GL_FALSE) { exit(EXIT_FAILURE); }; // We should log something instead... 

	//// Create Fragment Shader...
	//fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragShader, 1, &fragmentShaderSource, nullptr);
	//glCompileShader(fragShader);

	//glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	//if (success == GL_FALSE) { exit(EXIT_FAILURE); };

	//// Finish linking the two shaders together into the Program object.
	//glAttachShader(shaderProgram, vertShader);
	//glAttachShader(shaderProgram, fragShader);
	//glLinkProgram(shaderProgram);

	//// Ask if the link was successfull.
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (success == GL_FALSE) { exit(EXIT_FAILURE); };

	//// Cleanup our state. If we left our buffers bound, someone might accidentally modify them later.
	//// This is not technically required, but can help reduce obscure errors.
	//glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	//glBindVertexArray(GL_NONE);
}

void Game::shutDown()
{
	delete _window;
	delete _camera;
}

void Game::update()
{
	while (true)
	{
		if (_window->isKeyPressed(GLFW_KEY_ESCAPE))
			break;

		_window->clear();
		_window->update();


		cameraProjection = mat4::perspective(toRadii(45.f), (float)1280 / (float)720, 0.1f, 100.f);
		cameraTransform = mat4::translation(vec3(0.f, 0.f, 0.0f));

		//glUseProgram(shaderProgram);

		//// Ask for the handles identfying the uniform variables in our shader.
		//int modelLoc = glGetUniformLocation(shaderProgram, "u_model");
		//int viewLoc = glGetUniformLocation(shaderProgram, "u_view");
		//int projectionLoc = glGetUniformLocation(shaderProgram, "u_projection");

		//// Same as above, but remember that we must inverse the Camera matrix! (See lecture 3 slides) 
		////glUniformMatrix4fv(viewLoc, 1, false, &camera->getLookMatrix3().m[0][0]);
		//glUniformMatrix4fv(viewLoc, 1, false, &_camera->getLookMatrix().m[0][0]);
		//// Projection matrix is uploaded as-is.
		//glUniformMatrix4fv(projectionLoc, 1, false, &cameraProjection.m[0][0]);
		//// Send our newest MVP matrices to the Vertex Shader (respecting the handles we just found)...
		//glUniformMatrix4fv(
		//	modelLoc,							// Target Variable (u_model).
		//	1,									// We are only sending 1 matrix.
		//	false,								// We don't need to transpose because both OpenGL and MiniMath are column-major.
		//	&cameraTransform.m[0][0]); // The pointer to our actual matrix data (the float[16] in the mat4 class).


		//// Switch on our mesh by binding the VAO - it remembers the streams as a "view" into our VBO data.
		//glBindVertexArray(VAO);

		//// This is the actual 'render' call.
		//glDrawArrays(
		//	GL_TRIANGLES,	// The contents viewed by the VAO should be treated as regular triangles.
		//	0,				// Start at the begining of the mesh.
		//	12 * 3);		// Number of vertices to render = 12 triangles * 3 vertices per triangle.

		//// Revert the states we set during the function.
		//// This is not technically required, but can help reduce obscure errors.



		//camera->processMouseMovement(1280.f / 2.0f, 720.f / 2.0f);

		render();
	}
}

void Game::render()
{
	sh.use();
	sh.setMat4("model", cameraTransform);
	sh.setMat4("projection", cameraProjection);
	sh.setMat4("view", _camera->getLookMatrix());

	glBindVertexArray(monkey.VAO);
	glDrawArrays(GL_TRIANGLES, 0, monkey.getNumVertices());

	glBindVertexArray(0);
	glUseProgram(0);

	_window->poll();
}
