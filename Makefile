NAME = rubik

UNAME_S = $(shell uname -s)

SRCDIR = srcs/

OBJDIR = .obj/

DEPDIR = .dep/

INCLUDEDIR = include/

FLAGS = -Wall -Werror -Wextra -std=c++98

SOURCEFILES =	main.cpp \
				utils.cpp \
				Cube.cpp \
				Shape.cpp \
				Cube3.cpp \
				vec3.cpp \
				mat3.cpp \
				Solver.cpp \
				Commands.cpp \
				Visualizer.cpp \

SOURCE = $(addprefix $(SRCDIR), $(SOURCEFILES)) libs/glad/src/glad.c

OBJ = $(addprefix $(OBJDIR), $(SOURCEFILES:.cpp=.o)) $(OBJDIR)glad.o

DEP = $(addprefix $(DEPDIR), $(SOURCEFILES:.cpp=.d)) $(DEPDIR)glad.d

INCLUDES = -I $(INCLUDEDIR) -I libs/glfw/include -I libs/glad/include -I libs/glm/glm

ifeq ($(UNAME_S),Darwin)
LIBS = -L ./libs/glfw/src/ -lglfw3 -lpthread -ldl -lm -L ./libs/
else
LIBS = -L ./libs/glfw/src/ -lglfw3 -lpthread -ldl -lm -lGL -lX11 -L ./libs/
endif

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	clang++ $(FLAGS) -c $< -o $@ $(INCLUDES) -MMD -MF $(DEPDIR)$*.d

$(OBJDIR)glad.o: libs/glad/src/glad.c
	mkdir -p $(dir $@)
	gcc -c $< -o .obj/glad.o $(INCLUDES) -MMD -MF $(DEPDIR)glad.d

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEPDIR):
	mkdir $(DEPDIR)

$(OBJ): | $(OBJDIR) $(DEPDIR)

$(NAME): $(OBJ)
	cd libs/glfw && cmake . && make --silent
	cd libs/glm && cmake . && make --silent
ifeq ($(UNAME_S),Darwin)
	clang++ $(OBJ) -o $(NAME) -framework Cocoa -framework OpenGL -framework QuartzCore -framework IOKit $(LIBS)
else
	clang++ $(OBJ) -o $(NAME) $(LIBS)
endif

clean:
	rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all

-include $(DEP)
