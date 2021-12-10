#include "Visualizer.hpp"

Visualizer::Visualizer(int size): _size(size)
{
	if (!glfwInit())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

#ifdef __linux__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_window = glfwCreateWindow(1366, 768, "scop", 0, 0);
	if (!_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(_window);

	glfwSwapInterval(1);

#ifndef _WIN32
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
#else
	if (glewInit() != GLEW_OK)
#endif
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	_vCount = (_size + 1) * (_size + 1) * (_size + 1);

	_vertices = new float[_vCount * 3];
	_idxs = new unsigned int[6 * 6 * _size * _size * _size];
	_setVertices();

	_vbo = _makeBuffer(GL_ARRAY_BUFFER, _vCount * sizeof(float) * 3, _vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	_ibo = _makeBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 8 * _size * _size * _size, _idxs);

	_createShader("res/shaders/VertexBasic.shader", "res/shaders/FragmentBasic.shader");

	glUseProgram(_shader);

	_setLocations();

	glEnable(GL_DEPTH_TEST);
}

void	Visualizer::_setVertices()
{
	float	fsize = _size;
	int		incsize = _size + 1;
	for (int z = 0; z <= _size * 3; z += 3)
		for (int y = 0; y <= _size * 3; y += 3)
			for (int x = 0; x <= _size * 3; x += 3)
			{
				_vertices[x + y * incsize + z * incsize * incsize] = -fsize / 2 + 1.0f * (x / 3);
				_vertices[x + y * incsize + z * incsize * incsize + 1] = -fsize / 2 + 1.0f * (y / 3);
				_vertices[x + y * incsize + z * incsize * incsize + 2] = fsize / 2 - 1.0f * (z / 3);
			}
	for (int z = 0; z < _size * 36; z += 36)
		for (int y = 0; y < _size * 36; y += 36)
			for (int x = 0; x < _size * 36; x += 36)
			{
				int tx = x / 36;
				int ty = y / 36;
				int tz = z / 36;
				_idxs[x + y * _size + z * _size * _size] = tx + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 1] = tx + 1 + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 2] = tx + (ty + 1) * incsize + tz * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 3] = tx + 1 + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 4] = tx + (ty + 1) * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 5] = tx + 1 + (ty + 1) * incsize + tz * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 6] = tx + 1 + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 7] = tx + 1 + (ty + 1) * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 8] = tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 9] = tx + 1 + (ty + 1) * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 10] = tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 11] = tx + 1 + ty * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 12] = tx + 1 + ty * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 13] = tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 14] = tx + (ty + 1) * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 15] = tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 16] = tx + (ty + 1) * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 17] = tx + ty * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 18] = tx + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 19] = tx + ty * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 20] = tx + (ty + 1) * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 21] = tx + ty * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 22] = tx + (ty + 1) * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 23] = tx + (ty + 1) * incsize + tz * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 24] = tx + (ty + 1) * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 25] = tx + 1 + (ty + 1) * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 26] = tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 27] = tx + 1 + (ty + 1) * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 28] = tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 29] = tx + (ty + 1) * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 30] = tx + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 31] = tx + 1 + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 32] = tx + 1 + ty * incsize + (tz + 1) * incsize * incsize;

				_idxs[x + y * _size + z * _size * _size + 33] = tx + 1 + ty * incsize + tz * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 34] = tx + 1 + ty * incsize + (tz + 1) * incsize * incsize;
				_idxs[x + y * _size + z * _size * _size + 35] = tx + ty * incsize + (tz + 1) * incsize * incsize;
				std::cout << x + y * _size + z * _size * _size + 35 << std::endl;
			}
}

void	Visualizer::_setLocations()
{
	// addLocation(scop->objectShader, &scop->locations.color, "u_Color");
	// addLocation(scop->objectShader, &scop->locations.tempTexture, "u_SimpleColor");
	// addLocation(scop->objectShader, &scop->locations.lightPos, "u_lightPos");
	// addLocation(scop->objectShader, &scop->locations.lightColor, "u_lightColor");
	// addLocation(scop->objectShader, &scop->locations.perspective, "perspective");
	// addLocation(scop->objectShader, &scop->locations.view, "view");
	// addLocation(scop->objectShader, &scop->locations.rotmat, "rotmat");
	// addLocation(scop->objectShader, &scop->locations.texTrans, "u_texTrans");
}

unsigned int	Visualizer::_makeBuffer(unsigned int type, unsigned int size, void* data)
{
	unsigned int	buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(type, buffer);
	glBufferData(type, size, data, GL_STATIC_DRAW);
	return buffer;
}

Visualizer::~Visualizer()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ibo);
	glDeleteProgram(_shader);
	glfwDestroyWindow(_window);
	glfwTerminate();
	delete[] _vertices;
	delete[] _idxs;
}

std::string	Visualizer::_parseShader(const std::string &filepath)
{
	std::string	ret;

	ret = readFile(filepath);
	if (ret.size() < 12)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
#ifdef __linux__
	ret[9] = '3';
	ret[10] = '3';
	ret[11] = '0';
#else
	ret[9] = '4';
	ret[10] = '1';
	ret[11] = '0';
#endif
	return ret;
}

unsigned int	Visualizer::_compileShader(unsigned int type, const std::string &source)
{
	unsigned int	id = glCreateShader(type);
	const char	*src = source.c_str();
	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int	result = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int	length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char	message[512];
		glGetShaderInfoLog(id, length, &length, message);
		printf("Failed to compile shader\n%s\n", message);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

void	Visualizer::_createShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
	std::string	vertexShader = _parseShader(vertexShaderPath);

	std::string	fragmentShader = _parseShader(fragmentShaderPath);

	_shader = glCreateProgram();
	unsigned int	vs = _compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int	fs = _compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(_shader, vs);
	glAttachShader(_shader, fs);
	glLinkProgram(_shader);
	glValidateProgram(_shader);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void	Visualizer::_calculateDeltaTime()
{
	static float	lastFrame;
	float	currentFrame;

	currentFrame = glfwGetTime();
	_deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void	Visualizer::_drawScene()
{
	glBindVertexArray(_vao);
	glUseProgram(_shader);

	// glUniform4f(scop->locations.perspective, M_PI_4, (float)scop->screenWidth / scop->screenHeight, 0.1f, 100.0f);

	// t_vector3 tmp = scop->camera.position;
	// sumvec3(&tmp, scop->camera.front, -1.0f);
	// lookat(&scop->lookAt, scop->camera.position, tmp, scop->camera.up);
	// glUniformMatrix4fv(scop->locations.view, 1, GL_FALSE, (const GLfloat*)&scop->lookAt);
	// glUniformMatrix3fv(scop->locations.rotmat, 1, GL_FALSE, (const GLfloat*)&scop->rotmat);

	//	change by _size * _size * _size GL_TRIANGLE_STRIP
	glDrawElements(GL_TRIANGLES, 36 * _size * _size * _size, GL_UNSIGNED_INT, 0);
	// scop->texTrans += 0.1 * scop->texSign * scop->deltaTime;
	// if (scop->texTrans > 1.0f)
	// 	scop->texTrans = 1.0f;
	// if (scop->texTrans < 0.0f)
	// 	scop->texTrans = 0.0f;
	// scop->rotmat = muliplyMat3(scop->rotmat, getyrot(0.5f * M_PI));
	// scop->rotmat = muliplyMat3(getzrot(scop->rotation.z), muliplyMat3(getyrot(scop->rotation.y), \
	// 	muliplyMat3(getxrot(scop->rotation.x), scop->rotmat)));
	// scop->rotmat = muliplyMat3(scop->rotmat, getyrot(-0.5f * M_PI));
	// setVector3(&(scop->rotation), 0.0f, 0.0f, 0.0f);
}

void	Visualizer::visualize(Cube *cube, Commands &commands)
{
	(void)cube;
	(void)commands;
	while (!glfwWindowShouldClose(_window))
	{
		// checkResize(scop);
		_calculateDeltaTime();
		glClearColor(0.52f, 0.52f, 0.52f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// processInput(scop);

		_drawScene();

		// drawInterface(scop);

		// scop->frames++;

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}
