# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/12 11:45:05 by mhidani           #+#    #+#              #
#    Updated: 2026/04/16 10:58:44 by mhidani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= PmergeMe
SINCE		= 2026.04.12
AUTHOR		= mhidani
LOCAL		= 42SP
VERSION		= 1.0.0v

TIMESTAMP	= $(shell date +%Y%m%d_%H%M%S)

INC_DIR		= includes
TPL_DIR		= templates
SRC_DIR		= src
OBJ_DIR		= obj

SRC_FLS		= PmergeMe.cpp
MAIN		= main.cpp

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FLS))

SRC_OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC_FLS:.cpp=.o))
MAIN_OBJ	= $(OBJ_DIR)/$(MAIN:.cpp=.o)
OBJS		= $(SRC_OBJS) $(MAIN_OBJ)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g
CXXINCS		= -I$(INC_DIR) -I$(TPL_DIR)

VALGRIND	= valgrind
VGDLOG		= valgrind_$(TIMESTAMP).log
VGDFLAGS	= --leak-check=full --track-origins=yes --show-leak-kinds=all \
			  --log-file=$(VGDLOG)

MKD			= mkdir
MKDFLAGS	= --parents
RM			= rm
RMFLAGS		= --force --recursive
ARGS		= 

define check_created
	if [ -f $(1) ]; then \
		echo "🟢 $(1): is created"; \
	else \
		echo "🔴 $(1): doesn't created"; \
	fi
endef

define remove_dir_exists
	if [ -d $(1) ]; then \
		$(RM) $(RMFLAGS) $(1); \
		echo "🟢 $(1): is cleaned"; \
	else \
		echo "🟠 $(1): doesn't exists and not cleaned"; \
	fi
endef

define remove_file_exists
	if [ -f $(1) ]; then \
		$(RM) $(RMFLAGS) $(1); \
		echo "🟢 $(1): is cleaned"; \
	else \
		echo "🟠 $(1): doesn't exists and not cleaned"; \
	fi 
endef

all: banner $(NAME)

clean:
	@$(call remove_dir_exists, $(OBJ_DIR))

clean_logs:
	@$(RM) $(RMFLAGS) valgrind_*.log
	@echo "🟧 valgrind logs is cleaned"

fclean: clean
	@$(call remove_file_exists, $(NAME))

re: fclean all

banner:
	@echo "🛸 $(LOCAL) - [CPP-09 Exercise 02]"
	@echo "PmergeMe"
	@echo "$(NAME) $(VERSION)"
	@echo "$(AUTHOR) $(SINCE)"
	@echo 

run: banner $(NAME)
	@$(VALGRIND) $(VGDFLAGS) ./$(NAME) $(ARGS)
	@$(call check_created, $(VGDLOG))

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) $(CXXINCS) -o $@
	@echo "🔷 $(NAME): The executable is ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKD) $(MKDFLAGS) $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CXXINCS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
	@$(MKD) $(MKDFLAGS) $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CXXINCS) -c $< -o $@

.PHONY: clean clean_logs fclean all re run banner
