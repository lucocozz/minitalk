# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/26 03:46:20 by lucocozz          #+#    #+#              #
#    Updated: 2021/06/26 23:10:37 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME=	client
SERVER_NAME=	server

CLIENT_SRCS=	client.c

SERVER_SRCS=	server.c

UTILS_SRCS=		ft_putnbr.c			ft_putstr.c			ft_strlen.c			\
				ft_atoi.c			ft_bzero.c			exit_error.c		\
				ft_isnumber.c

UTILS_OBJS = $(UTILS_SRCS:%.c=$(OBJS_DIR)/%.o)
CLIENT_OBJS = $(CLIENT_SRCS:%.c=$(OBJS_DIR)/%.o)
SERVER_OBJS = $(SERVER_SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(CLIENT_OBJS:%.o=%.d) $(SERVER_OBJS:%.o=%.d)	\
	$(UTILS_OBJS:%.o=%.d)

SRCS_DIR = sources
OBJS_DIR = .objs
INCLUDES_DIR = includes $(LIBS:%=lib%/includes) $(LIBS:%=lib%)

LIBS =

MAKE = make
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -MMD -Wall -Wextra -Werror
CXXFLAGS = $(INCLUDES_DIR:%=-I %)
ifeq ($(DEBUG), on)
	CXXFLAGS += -g3 -fsanitize=address
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%)

vpath %.c	$(addprefix $(SRCS_DIR), /. /utils)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(CLIENT_NAME)
	$(MAKE) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) $(UTILS_OBJS) | $(LIBS:%=lib%.a)
	$(CC) $(CXXFLAGS) $^ -o $(CLIENT_NAME) $(LDFLAGS)

$(SERVER_NAME): $(SERVER_OBJS) $(UTILS_OBJS) | $(LIBS:%=lib%.a)
	$(CC) $(CXXFLAGS) $^ -o $(SERVER_NAME) $(LDFLAGS)

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	$(RM) $(OBJS_DIR)/debug*
	touch $@

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)	\
	$(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a)

re: fclean all

.PHONY: all clean fclean re
