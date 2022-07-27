# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 18:58:59 by gunkim            #+#    #+#              #
#    Updated: 2022/07/25 17:26:46 by gunkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := test

CXX         := c++
CXXFLAGS    := -g -Wall -Wextra -Werror -std=c++98

RM          := rm -rf

DIR_TESTOR  := testor
DIR_OBJ     := obj
DIR_INC     := vector

INCLUDE     := -I$(DIR_INC)

SRCS		:= main_lab.cpp

OBJS		:= $(addprefix $(DIR_OBJ)/, $(SRCS:.cpp=.o))
DEPS        := $(SRCS:.cpp=.d)

vpath %.c $(DIR_TESTOR)

.PHONY: all clean fclean re test

$(NAME) : $(DIR_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJS) -o $@

$(DIR_OBJ)/%.o : $(DIR_TESTOR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)

clean :
	$(RM) $(OBJS) $(DIR_OBJ) dep
	
fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY : dep

dep : $(DEPS)

%.d : $(DIR_SRC)/%.cpp
	$(CXX) $(INCLUDE) -MM $< | sed 's|^|$(DIR_OBJ)/|' | sed 's|$(DIR_OBJ)/  ||' >> dep

# DO NOT DELETE 
