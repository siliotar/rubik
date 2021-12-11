#pragma once

#ifndef _WIN32
# include <glad/glad.h>
#else
# include <GL/glew.h>
# include <GL/gl.h>
#endif
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Cube.hpp"
#include "Cube3.hpp"
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
		unsigned int	_model;
		unsigned int	_view;
		unsigned int	_projection;
		unsigned int	_color;
		float			*_vertices;
		unsigned int	*_idxs;
		size_t			_vCount;
		float			_deltaTime;
		Cube			*_cube;
		Commands		*_commands;
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
		Color	_getColor(int x, int y, int z, int i);
		glm::vec3	_getrgbColor(int x, int y, int z, int i);
	public:
		Visualizer(int size);
		~Visualizer();
		void	visualize(Cube *cube, Commands &commands);
};
