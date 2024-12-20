White 	= \e[0;30m
Yellow 	= \x1b[33m
Red	= \e[0;31m
Blue	= \e[0;34m
Green 	= \033[1;32m
RESET 	= \033[0m

NAME	 = minishell
COMPILER = cc
FLAGS	 =  #-Wall -Werror -Wextra -g3 -fsanitize=address
FLAGS	 =  -g3
READLINE = -lreadline
SRCS	 = Minishell.c  Parsing/Environement_init.c linked_list/ft_addnodeenv.c Error_management/ft_freelists.c  Outils/ft_strncpy.c\
				Outils/ft_strdup.c Outils/ft_strlen.c	Parsing/shellon.c Parsing/Struct_init.c Outils/ft_isalpha.c \
				Outils/ft_calloc.c  Outils/ft_split.c Outils/ft_isspace.c Error_management/ft_freecmd.c Parsing/Syntaxe_check/redirection.c\
				Parsing/lexcer.c Parsing/Syntaxe_check/pipe.c Parsing/Syntaxe_check/quotes.c Parsing/lexcer/inputcorrection.c\
				Outils/ft_strchr.c linked_list/ft_addnodecmd.c Outils/ft_strncmp.c linked_list/ft_addnodecmd_2.c Parsing/expand/ft_expand.c\
				Parsing/redirections/redirections_1.c linked_list/ft_addnodefile.c Outils/ft_strcmp.c Outils/ft_isalnum.c Parsing/quotes_remover/Part_01.c\
				Builtins/echo.c Builtins/cd.c Builtins/pwd.c Builtins/unset.c Builtins/export.c Builtins/exit.c \
				Builtins/export_sorting.c Builtins/export_append.c Builtins/env.c Parsing/expand_herdoc.c \
				Parsing/expand/ft_expande_2.c Parsing/expand/ft_expande_3.c Parsing/lexcer/inputcorrection_2.c \
				Parsing/expand_herdoc_2.c Parsing/expand/ft_expande_4.c Norm/Parse/Parse.c\
				Norm/Heredoc/heredoc.c Norm/Executing/execute.c Norm/Executing/execute2.c Norm/GarbegCollector/gc.c \
				Norm/Pipes/pipe.c Norm/Redirections/redirections.c Norm/Path/path1.c Norm/Path/path2.c \
				Norm/Signals/signals.c Norm/Signals/signals2.c Norm/SetFiles/set_files.c \
				Tools/Tools.c Tools/Tools2.c

OBJS	 = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME) $(READLINE)
%.o: %.c
	@$(COMPILER) $(FLAGS) -c $< -o $@
	@echo "$(Red) [!] Compiling File Named $< In Progress \n"
	@echo "$(Green) [✔] Compilation Complete ... !$(RESET)"
	@echo "\n"
clean:
	@rm -rf $(OBJS)
fclean:
	@rm -rf $(OBJS) $(NAME)
re: fclean all
