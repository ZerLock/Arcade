##
## EPITECH PROJECT, 2023
## cpp-epitech-template
## File description:
## Makefile
##

CXX				=	g++

SRC_DIR			=	src

CORE_DIR		=	$(SRC_DIR)/core

LIBS_DIR		=	$(SRC_DIR)/libs

GAMES_DIR		=	$(SRC_DIR)/games

DL_OUT			=	./lib

##############################
# Core
##############################
NAME			=	arcade

CORE_SRC		=	$(CORE_DIR)/Core.cpp \
					$(CORE_DIR)/Context.cpp \
					$(CORE_DIR)/DLLoader.cpp \
					$(CORE_DIR)/Error.cpp \
					$(GAMES_DIR)/Menu.cpp

CORE_OBJ		=	$(CORE_SRC:%.cpp=%.o)

##############################
# Graphics
##############################

###
# SFML
###
SFML_NAME		=	$(DL_OUT)/arcade_sfml.so

SFML_SRC		=	$(LIBS_DIR)/Sfml.cpp

SFML_OBJ		=	$(SFML_SRC:%.cpp=%.o)

###
# SDL2
###
SDL_NAME		=	$(DL_OUT)/arcade_sdl2.so

SDL_SRC			=	$(LIBS_DIR)/Sdl.cpp

SDL_OBJ			=	$(SDL_SRC:%.cpp=%.o)

###
# NCurses
###
NCURSES_NAME	=	$(DL_OUT)/arcade_ncurses.so

NCURSES_SRC		=	$(LIBS_DIR)/Ncurses.cpp

NCURSES_OBJ		=	$(NCURSES_SRC:%.cpp=%.o)

##############################
# Games
##############################

###
# Snake
###
SNAKE_NAME		=	$(DL_OUT)/arcade_snake.so

SNAKE_SRC		=	$(GAMES_DIR)/Snake.cpp

SNAKE_OBJ		=	$(SNAKE_SRC:%.cpp=%.o)

###
# Nibbler
###
NIBBLER_NAME	=	$(DL_OUT)/arcade_nibbler.so

NIBBLER_SRC		=	$(GAMES_DIR)/Nibbler.cpp

NIBBLER_OBJ		=	$(NIBBLER_SRC:%.cpp=%.o)

###
# Pacman
###
PACMAN_NAME	=	$(DL_OUT)/arcade_pacman.so

PACMAN_SRC		=	$(GAMES_DIR)/Pacman.cpp

PACMAN_OBJ		=	$(PACMAN_SRC:%.cpp=%.o)

##############################
# Tests & Flags
##############################
TESTS 			=	$(filter-out src/main.cpp , $(wildcard src/**/*.cpp))	\
					$(wildcard tests/*.cpp)


CXXFLAGS		=	-std=c++20 \
					-fno-gnu-unique \
					-Wall \
					-Wextra \
					-I./include \
					-I./include/types \
					-I./include/core \
					-I./include/libs \
					-I./include/games \
					-g3 \
					-ldl \

LIBFLAGS		=	-std=c++20 -shared -fPIC -I./include -I./include/games -I./include/libs -I./include/core

##############################
# Rules
##############################
.PHONY: all
all:	graphicals games core

$(NAME):	$(CORE_OBJ)
	$(CXX) -o $(NAME) src/main.cpp $(CORE_OBJ) $(CXXFLAGS)

.PHONY: core
core:	$(NAME)

.PHONY: graphicals
graphicals:	$(SFML_OBJ)
	$(CXX) -o $(SFML_NAME) $(SFML_SRC) $(LIBFLAGS) -lsfml-window -lsfml-graphics -lsfml-system
	$(CXX) -o $(NCURSES_NAME) $(NCURSES_SRC) $(LIBFLAGS) -lncurses
	$(CXX) -o $(SDL_NAME) $(SDL_SRC) $(LIBFLAGS) -lSDL2 -lSDL2_ttf -lSDL2_image

.PHONY: games
# games:	$(SNAKE_OBJ) $(NIBBLER_OBJ)
games:	$(SNAKE_OBJ)
	$(CXX) -o $(SNAKE_NAME) $(SNAKE_SRC) $(LIBFLAGS)
	$(CXX) -o $(PACMAN_NAME) $(PACMAN_SRC) $(LIBFLAGS)
#	$(CXX) -o $(NIBBLER_NAME) $(NIBBLER_OBJ) $(CXXFLAGS) $(LIBFLAGS)

.PHONY: clean
clean:
	rm -f $(CORE_OBJ) $(SNAKE_OBJ) $(NIBBLER_OBJ) $(SFML_OBJ) $(SDL_OBJ) $(NCURSES_OBJ)
	rm -f tests/*.o
	rm -rf *.gc*

.PHONY: fclean
fclean:	clean
	rm -f $(NAME)
	rm -f $(DL_OUT)/*.so
	rm -f unit_tests

.PHONY:	re
re:	fclean all

###
# Tests
###
.PHONY: unit_tests
unit_tests:	fclean $(NAME)
	$(CC) -o unit_tests $(TESTS) $(CXXFLAGS) --coverage -lcriterion

.PHONY: tests_run
tests_run:	unit_tests
	./unit_tests

.PHONY: coverage
coverage:	tests_run
	gcovr --exclude tests

###
# Documentation
###
.PHONY: docs
docs:
	doxygen

.PHONY: clean_docs
clean_docs:
	rm -rf doc/html/
