# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/12 11:45:05 by mhidani           #+#    #+#              #
#    Updated: 2026/04/20 15:43:44 by mhidani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= RPN
SINCE		= 2026.04.12
AUTHOR		= mhidani
LOCAL		= 42SP
VERSION		= 1.0.0v

INC_DIR		= includes
TPL_DIR		= templates
SRC_DIR		= src
OBJ_DIR		= obj

SRC_FLS		= RPN.cpp
MAIN		= main.cpp

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FLS))

SRC_OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC_FLS:.cpp=.o))
MAIN_OBJ	= $(OBJ_DIR)/$(MAIN:.cpp=.o)
OBJS		= $(SRC_OBJS) $(MAIN_OBJ)

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
CXXINCS		= -I$(INC_DIR) -I$(TPL_DIR)

VALGRIND	= valgrind
VGDFLAGS	= --leak-check=full --track-origins=yes --show-leak-kinds=all
VGDFLGLG	= --log-file=

MKD			= mkdir
MKDFLAGS	= --parents
RM			= rm
RMFLAGS		= --force --recursive

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

define run_test
	$(eval CURRENT_LOG := valgrind_test$(strip $(1))_$(shell date +%Y%m%d_%H%M%S).log)
	@echo "🚩 Test $(1)"
	@echo "🔻 input> $(2)"
	@echo -n "🔺 output> "
	@$(VALGRIND) $(VGDFLAGS) $(VGDFLGLG)$(CURRENT_LOG) ./$(NAME) "$(2)" || true
	@echo "🔹 expected> $(3)"
	@$(call check_created,$(CURRENT_LOG))
	@echo ""
endef

all: banner $(NAME)

clean:
	@$(call remove_dir_exists, $(OBJ_DIR))

clean_logs:
	@$(RM) $(RMFLAGS) valgrind_*.log
	@echo "🟧 valgrind logs is cleaned"

fclean: clean_logs clean
	@$(call remove_file_exists, $(NAME))

re: fclean all

banner:
	@echo "🛸 $(LOCAL) - [CPP-09 Exercise 01]"
	@echo "Reverse Polish Notation"
	@echo "$(NAME) $(VERSION)"
	@echo "$(AUTHOR) $(SINCE)"
	@echo 

run: banner $(NAME)
	@$(VALGRIND) $(VGDFLAGS) ./$(NAME) $(ARGS)
	@$(call check_created, $(VGDLOG))

test: banner $(NAME)
	@echo "🚩 Running the tests"
	@echo
	@$(call run_test,1,8 9 * 9 - 9 - 9 - 4 - 1 +,42)
	@$(call run_test,2,7 7 * 7 -,42)
	@$(call run_test,3,1 2 * 2 / 2 * 2 4 - +,0)
	@$(call run_test,4,(1 + 1),Error: invalid input.)
	@$(call run_test,5,10 1 +,Error: invalid input.)
	@$(call run_test,6,-2 1 +,Error: invalid input.)
	@$(call run_test,7,0 1 +,Error: malformed expression.)
	@$(call run_test,8,9 0 /,Error: division by zero is invalid.)
	@$(call run_test,9,,Error: no operation was reported.)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) $(CXXINCS) -o $@
	@echo "🔷 $(NAME): The executable is ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKD) $(MKDFLAGS) $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CXXINCS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
	@$(MKD) $(MKDFLAGS) $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CXXINCS) -c $< -o $@

.PHONY: clean clean_logs fclean all re run test banner
