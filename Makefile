#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ollevche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/12 19:03:20 by ollevche          #+#    #+#              #
#    Updated: 2018/02/12 19:03:22 by ollevche         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	ollevche.filler

FLAGS	=	-Wall -Werror -Wextra -I./headers -I./libft/headers \
			-I./libft/libft-gnl/headers/

SRCDIR	=	./sources/

OBJDIR	=	./objects/

LIBDIR	=	./libft/

SRC		=	main.c update_map.c get_piece.c util.c

OBJ		=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

LIB		=	libftprintf.a

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBDIR)$(LIB)
	@echo "creating filler binary"
	@gcc -o $(NAME) $(OBJ) $(LIB) $(FLAGS)

$(OBJ): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "creating filler object files"
	@gcc -o $@ -c $< $(FLAGS)

$(LIBDIR)$(LIB):
	@make -C $(LIBDIR)
	@cp $(LIBDIR)$(LIB) ./

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@make -C $(LIBDIR) clean
	@echo "removing filler object files"
	@rm -rf $(OBJ) $(OBJDIR)

fclean: clean
	@make -C $(LIBDIR) fclean
	@echo "removing filler binary"
	@rm -rf $(NAME) $(LIB)

re: fclean $(NAME)
	
test: test.c $(LIBDIR)$(LIB)
	@gcc -o test test.c $(LIB) $(FLAGS)
