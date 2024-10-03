White 	= \e[0;30m
Yellow 	= \x1b[33m
Red	= \e[0;31m
Blue	= \e[0;34m
Green 	= \033[1;32m

NAME	 = Shell
COMPILER = cc
FLAGS	 = -Wall -Werror -Wextra #-g3 -fsanitize=address
READLINE = -lreadline
SRCS	 = Minishell.c  Parsing/Environement_init.c linked_list/ft_addnodeenv.c Error_management/ft_freelists.c  Outils/ft_strncpy.c\
				Outils/ft_strdup.c Outils/ft_strlen.c	Parsing/shellon.c Parsing/Struct_init.c Outils/ft_isalpha.c \
				Outils/ft_calloc.c  Outils/ft_split.c Outils/ft_isspace.c Error_management/ft_freecmd.c Parsing/Syntaxe_check/redirection.c\
				Parsing/lexcer.c Parsing/Syntaxe_check/pipe.c Parsing/Syntaxe_check/quotes.c Parsing/lexcer/inputcorrection.c\
				Outils/ft_strchr.c linked_list/ft_addnodecmd.c Outils/ft_strncmp.c linked_list/ft_addnodecmd_2.c

OBJS	 = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME) $(READLINE)
%.o: %.c
	@$(COMPILER) -c $< -o $@
	@echo "$(Red) [!] Compiling File Named $< In Progress \n"
	@echo "$(Green) [✔] Compilation Complete ... ! "
	@echo "\n"
clean:
	@rm -rf $(OBJS)
fclean:
	@rm -rf $(OBJS) $(NAME)
re:
	all fclean
