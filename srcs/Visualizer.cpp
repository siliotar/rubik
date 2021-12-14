#include "Visualizer.hpp"

Visualizer::Visualizer(int size): _size(size), _rotAngle(0.0f), _screenWidth(1366), \
_screenHeight(768), _freeMode(0), _solve(false), _shuffle(false), _speed(1.0f)
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

	_window = glfwCreateWindow(_screenWidth, _screenHeight, "scop", 0, 0);
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
	_idxs = new unsigned int[24 * _size * _size * _size];
	_setVertices();

	_vbo = _makeBuffer(GL_ARRAY_BUFFER, _vCount * sizeof(float) * 3, _vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	_ibo = _makeBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 24 * _size * _size * _size, _idxs);

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
				_vertices[x + y * incsize + z * incsize * incsize + 2] = -fsize / 2 + 1.0f * (z / 3);
			}
	for (int z = 0; z < _size * 24; z += 24)
		for (int y = 0; y < _size * 24; y += 24)
			for (int x = 0; x < _size * 24; x += 24)
			{
				int tx = x / 24;
				int ty = y / 24;
				int tz = z / 24;
				int idxs[8] = {
					tx + ty * incsize + tz * incsize * incsize,
					tx + 1 + ty * incsize + tz * incsize * incsize,
					tx + ty * incsize + (tz + 1) * incsize * incsize,
					tx + 1 + ty * incsize + (tz + 1) * incsize * incsize,
					tx + (ty + 1) * incsize + tz * incsize * incsize,
					tx + 1 + (ty + 1) * incsize + tz * incsize * incsize,
					tx + (ty + 1) * incsize + (tz + 1) * incsize * incsize,
					tx + 1 + (ty + 1) * incsize + (tz + 1) * incsize * incsize,
				};
				//	Down
				_idxs[x + y * _size + z * _size * _size] = idxs[0];
				_idxs[x + y * _size + z * _size * _size + 1] = idxs[1];
				_idxs[x + y * _size + z * _size * _size + 2] = idxs[2];
				_idxs[x + y * _size + z * _size * _size + 3] = idxs[3];

				//	Back
				_idxs[x + y * _size + z * _size * _size + 4] = idxs[0];
				_idxs[x + y * _size + z * _size * _size + 5] = idxs[1];
				_idxs[x + y * _size + z * _size * _size + 6] = idxs[4];
				_idxs[x + y * _size + z * _size * _size + 7] = idxs[5];

				//	Right
				_idxs[x + y * _size + z * _size * _size + 8] = idxs[1];
				_idxs[x + y * _size + z * _size * _size + 9] = idxs[3];
				_idxs[x + y * _size + z * _size * _size + 10] = idxs[5];
				_idxs[x + y * _size + z * _size * _size + 11] = idxs[7];

				//	Front
				_idxs[x + y * _size + z * _size * _size + 12] = idxs[2];
				_idxs[x + y * _size + z * _size * _size + 13] = idxs[3];
				_idxs[x + y * _size + z * _size * _size + 14] = idxs[6];
				_idxs[x + y * _size + z * _size * _size + 15] = idxs[7];

				//	Left
				_idxs[x + y * _size + z * _size * _size + 16] = idxs[0];
				_idxs[x + y * _size + z * _size * _size + 17] = idxs[2];
				_idxs[x + y * _size + z * _size * _size + 18] = idxs[4];
				_idxs[x + y * _size + z * _size * _size + 19] = idxs[6];

				//	Up
				_idxs[x + y * _size + z * _size * _size + 20] = idxs[4];
				_idxs[x + y * _size + z * _size * _size + 21] = idxs[5];
				_idxs[x + y * _size + z * _size * _size + 22] = idxs[6];
				_idxs[x + y * _size + z * _size * _size + 23] = idxs[7];
			}
}

void	Visualizer::_setLocations()
{
	_model = glGetUniformLocation(_shader, "model");
	_view = glGetUniformLocation(_shader, "view");
	_projection = glGetUniformLocation(_shader, "projection");
	_color = glGetUniformLocation(_shader, "color");
	_rotmat = glGetUniformLocation(_shader, "rotmat");
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

Color	Visualizer::_getColor(int x, int y, int z, int i)
{
	Shape	*s = _cube->getShapes()[x + y * _size + z * _size * _size];
	switch (i)
	{
	case 0:
		return s->_down;
	case 1:
		return s->_back;
	case 2:
		return s->_right;
	case 3:
		return s->_front;
	case 4:
		return s->_left;
	default:
		return s->_up;
	}
}

glm::vec3	Visualizer::_getrgbColor(int x, int y, int z, int i)
{
	Color	c = _getColor(x, y, z, i);
	switch (c)
	{
	case Yellow:
		return glm::vec3(1.0f, 1.0f, 0.2f);
	case Blue:
		return glm::vec3(0.2f, 0.3f, 0.8f);
	case Red:
		return glm::vec3(0.8f, 0.2f, 0.3f);
	case Green:
		return glm::vec3(0.2f, 0.8f, 0.3f);
	case Orange:
		return glm::vec3(1.0f, 0.55f, 0.0f);
	case White:
		return glm::vec3(0.9f, 0.9f, 0.9f);
	default:
		return glm::vec3(0.1f, 0.1f, 0.1f);
	}
}

void	Visualizer::_drawScene()
{
	glBindVertexArray(_vao);
	glUseProgram(_shader);

	glm::mat4	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -7.0f));
	glm::mat4	proj = glm::perspective(glm::radians(45.0f), (float)_screenWidth / _screenHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(_model, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(model));
	glUniformMatrix4fv(_view, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(view));
	glUniformMatrix4fv(_projection, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(proj));

	if (_commands->fullSize() > 0)
		_rotAngle += _speed * M_PI * _deltaTime;
	if (_rotAngle >= M_PI_2)
	{
		_rotAngle = 0.0f;
		if (_commands->fullSize() > 0)
			_cube->exec(_commands->popFront());
	}
	if (!_freeMode && _commands->fullSize() == 0)
	{
		_commands->clear();
		_freeMode = true;
	}
	if (_freeMode && _solve && _commands->fullSize() == 0)
	{
		if (static_cast<Cube3*>(_cube))
			*_commands = Cube3(*static_cast<Cube3*>(_cube)).solve();
		else
			*_commands = Cube(*_cube).solve();
		_solve = false;
		_freeMode = false;
	}
	if (_freeMode && _shuffle && _commands->fullSize() == 0)
	{
		std::string	shuf;
		if (static_cast<Cube3*>(_cube))
			shuf = (Cube3(*static_cast<Cube3*>(_cube))).shuffle(20);
		else
			shuf = Cube(*_cube).shuffle(20);
		_commands->pushLine(shuf);
		_shuffle = false;
		_freeMode = false;
	}
	for (int z = 0; z < _size * 24; z += 24)
		for (int y = 0; y < _size * 24; y += 24)
			for (int x = 0; x < _size * 24; x += 24)
			{
				GLintptr offset = x + y * _size + z * _size * _size;
				offset *= sizeof(unsigned int);
				glm::mat4	rotmat = glm::mat3(1.0f);
				if (_commands->fullSize() > 0)
				{
					if ((*_commands)[0] == "R" && x == (_size - 1) * 24)
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(1.0f, 0.0f, 0.0f));
					else if ((*_commands)[0] == "R'" && x == (_size - 1) * 24)
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(1.0f, 0.0f, 0.0f));
					else if ((*_commands)[0] == "L" && x == 0)
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(1.0f, 0.0f, 0.0f));
					else if ((*_commands)[0] == "L'" && x == 0)
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(1.0f, 0.0f, 0.0f));
					else if ((*_commands)[0] == "U" && y == (_size - 1) * 24)
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
					else if ((*_commands)[0] == "U'" && y == (_size - 1) * 24)
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
					else if ((*_commands)[0] == "D" && y == 0)
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
					else if ((*_commands)[0] == "D'" && y == 0)
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
					else if ((*_commands)[0] == "F" && z == (_size - 1) * 24)
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					else if ((*_commands)[0] == "F'" && z == (_size - 1) * 24)
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					else if ((*_commands)[0] == "B" && z == 0)
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					else if ((*_commands)[0] == "B'" && z == 0)
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					else if ((*_commands)[0] == "x")
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(1.0f, 0.0f, 0.0f));
					else if ((*_commands)[0] == "x'")
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(1.0f, 0.0f, 0.0f));
					else if ((*_commands)[0] == "y")
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
					else if ((*_commands)[0] == "y'")
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
					else if ((*_commands)[0] == "z")
						rotmat = glm::rotate(rotmat, -_rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					else if ((*_commands)[0] == "z'")
						rotmat = glm::rotate(rotmat, _rotAngle, glm::vec3(0.0f, 0.0f, 1.0f));
				}

				glUniformMatrix3fv(_rotmat, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(glm::mat3(rotmat)));
				for (int i = 0; i < 6; ++i)
				{
					glm::vec3	color = _getrgbColor(x / 24, y / 24, z / 24, i);
					glUniform3f(_color, color.r, color.g, color.b);
					glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (GLvoid*)(offset + 4 * i * sizeof(unsigned int)));
				}
			}
}

void	Visualizer::_processInput()
{
	static bool keyPressed = false;
	static int key;
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, 1);
	if (_freeMode && !keyPressed)
	{
		std::string	command = "";
		if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS)
		{
			command = "R";
			keyPressed = true;
			key = GLFW_KEY_R;
		}
		else if (glfwGetKey(_window, GLFW_KEY_L) == GLFW_PRESS)
		{
			command = "L";
			keyPressed = true;
			key = GLFW_KEY_L;
		}
		else if (glfwGetKey(_window, GLFW_KEY_U) == GLFW_PRESS)
		{
			command = "U";
			keyPressed = true;
			key = GLFW_KEY_U;
		}
		else if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			command = "D";
			keyPressed = true;
			key = GLFW_KEY_D;
		}
		else if (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS)
		{
			command = "F";
			keyPressed = true;
			key = GLFW_KEY_F;
		}
		else if (glfwGetKey(_window, GLFW_KEY_B) == GLFW_PRESS)
		{
			command = "B";
			keyPressed = true;
			key = GLFW_KEY_B;
		}
		else if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
				_shuffle = true;
			else
				_solve = true;
			keyPressed = true;
			key = GLFW_KEY_S;
		}
		if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
			command += "'";
		if (command.size() > 0 && command[0] != '\'')
			_commands->push(command, false);
	}
	if (glfwGetKey(_window, key) == GLFW_RELEASE)
		keyPressed = false;
	if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
		_speed += _deltaTime;
	if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		_speed -= _deltaTime;
	if (_speed < 0.5f)
		_speed = 0.5f;
	else if (_speed > 16.0f)
		_speed = 16.0f;
}

void	Visualizer::_checkResize()
{
	int	w, h;

	w = _screenWidth;
	h = _screenHeight;
	glfwGetWindowSize(_window, &_screenWidth, &_screenHeight);
	if (w != _screenWidth || h != _screenHeight)
	{
		glfwGetFramebufferSize(_window, &w, &h);
		glViewport(0, 0, w, h);
	}
}

void	Visualizer::visualize(Cube *cube, Commands &commands)
{
	_cube = cube;
	_commands = &commands;
	while (!glfwWindowShouldClose(_window))
	{
		_checkResize();
		_calculateDeltaTime();
		glClearColor(0.52f, 0.52f, 0.52f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_processInput();

		_drawScene();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}
