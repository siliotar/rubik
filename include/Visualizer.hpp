#pragma once

#ifndef _WIN32
# include <glad/glad.h>
#else
# include <GL/glew.h>
# include <GL/gl.h>
#endif
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Cube.hpp"
#include "Commands.hpp"
#include "utils.hpp"
#include "vec3.hpp"

class Visualizer
{
	private:
		int				_size;
		GLFWwindow		*_window;
		unsigned int	_vao;
		unsigned int	_vbo;
		unsigned int	_ibo;
		unsigned int	_shader;
		float			*_vertices;
		unsigned int	*_idxs;
		size_t			_vCount;
		float			_deltaTime;
		Visualizer(const Visualizer &other);
		Visualizer	&operator=(const Visualizer &other);
		unsigned int	_makeBuffer(unsigned int type, unsigned int size, void* data);
		void	_setVertices();
		void	_setLocations();
		std::string	_parseShader(const std::string &filepath);
		unsigned int	_compileShader(unsigned int type, const std::string &source);
		void	_createShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		void	_calculateDeltaTime();
		void	_drawScene();
	public:
		Visualizer(int size);
		~Visualizer();
		void	visualize(Cube *cube, Commands &commands);
};
