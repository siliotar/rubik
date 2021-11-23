NAME = name

SRCDIR = srcs/

OBJDIR = .obj/

DEPDIR = .dep/

INCLUDEDIR = include/

FLAGS = -Wall -Werror -Wextra -std=c++98

SOURCEFILES =	main.cpp Cube.cpp Shape.cpp

SOURCE = $(addprefix $(SRCDIR), $(SOURCEFILES))

OBJ = $(addprefix $(OBJDIR), $(SOURCEFILES:.cpp=.o))

DEP = $(addprefix $(DEPDIR), $(SOURCEFILES:.cpp=.d))

all: $(NAME)

$(DEPDIR)%.d: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	clang++ -MT $(<:$(SRCDIR)%.cpp=$(OBJDIR)%.o) -MM $< > $@ -I $(INCLUDEDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	clang++ $(FLAGS) -c $< -o $@ -I $(INCLUDEDIR)

$(NAME): $(DEP) $(OBJ)
	clang++  $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all

-include $(DEP)