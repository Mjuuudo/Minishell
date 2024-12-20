/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:01:38 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/20 22:21:21 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_envvar			t_envvar;
typedef struct s_token			t_token;
typedef struct s_commands		t_commands;
typedef struct s_shell			t_shell;
typedef struct s_cmd			t_cmd;
typedef struct s_redirection	t_redirection;

// Global Variable
extern t_shell	shell;

typedef enum s_types
{
	PIPE,
	STR,
	GREAT,
	DGREAT,
	LESS,
	LLESS,
	NONE
}								t_types;

struct							s_envvar
{
	char						*key;
	char						*value;
	t_envvar					*next;
	t_envvar					*prev;
};

struct							s_token
{
	char						*cmd;
	t_types						type;
	t_token						*next;
	t_token						*prev;
};

struct							s_cmd
{
	char						*order; // command
	char						**args;
	char						**red2;
	t_redirection				*red;
	t_cmd						*next;
	t_cmd						*prev;
};

struct							s_commands
{
	char						*commande;
	char						**table;
};

struct							s_redirection
{
	char						*file;
	t_types						identifier;
	t_redirection				*next;
	t_redirection				*prev;
};

struct							s_shell
{
	int							shell_level;
	int							exit;
	int							env_flag;
	char						**envholder;
	t_commands					commande;
	t_token						*tokens;
	char 						*temp_file;
	t_cmd						*cmd;
	t_envvar					*envp;
	size_t 						max_possible_len;
	int 						counter;
	t_shell						*next;
	t_shell						*prev;
};

// Parsing Environement Variables Functions Prototypes

void							ft_addnodeenv(t_envvar **list, char *value);
t_envvar						*ft_returnlastnodeenv(t_envvar *list);
void							ft_initnodeenv(t_envvar *node, char *value);
t_envvar						*ft_environementinit(t_envvar *envliste,
									char **env);
char							**ft_envholder(char **env, t_shell *shell);

// Parsing The STDIN Function Prototypes

// Lexcer Section

void							ft_members_init(t_shell *shell);
void							ft_shell_on(t_shell *shell);
int								ft_quotes(char *line, int index);
void							ft_cmdhandler(char *line, t_shell *shell);
int								count_spaces(char *line);
char							*spaced_string(char *line, t_shell *shell,
									int spaces, int counter_2);
void 							ft_cmdliste(t_shell *shell, int counter);
t_token							*ft_returnlastnodecmd(t_token *list);

// Parser Section

void							ft_parser(t_shell *shell);
t_cmd							*ft_returnlastnodecmd2(t_cmd *list);
void							ft_cmdliste_2(t_shell *shell, t_token *token);
t_token							*ft_addnodecmd(t_shell *shell, t_token *token);

// Error And Memory Management Functions Prototypes

void							ft_freeenv(t_envvar *list);
void							ft_freeenvholder(char **envholder);
void							ft_freecmdmain(t_shell *shell);
void							ft_freetokenmain(t_shell *shell);
void							ft_freefirstcmd(t_shell *shell);

// Tools Function Prototypes

char							*ft_strdup(const char *str);
size_t							ft_strlen(const char *str);
char							*ft_strncpy(char *src, char *dst,
									unsigned int len);
int								ft_isalpha(int c);
void							*ft_calloc(size_t nmemb, size_t size);
int								ft_ispace(char c);
// Syntaxe Error Functions Prototypes
int								ft_redirections(char *line, t_shell *shell);
int								ft_pipe(char *line, t_shell *shell);
int								ft_quotesch(char *line, t_shell *shell);
//
int								ft_strcmp(char *s1, char *s2);
int								ft_strchr(int c, const char *s);
char							**ft_split(char *str, char *charset);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
int								ft_isalnum(int c);

// Expanding Env Var Args Functions Prototypes
int 							ft_expand(t_token *token, t_envvar *env);

// Redirection Apply  Functions Prototypes

void							ft_redirectioninit(t_cmd **node, int counter);
int								ft_checkred(char **tab, char *cmd);
void							ft_quotesremove(t_cmd **node);
int								ft_isredornot(char *tab);










int redcalcu(t_token *tokens);
int ft_videornor(char *line);
int redcalcu(t_token *tokens);
void ft_morethan2(t_token *node, t_shell *shell, int counter);
int redcalcu(t_token *tokens);
char *ft_expandherdoc(char *line, t_envvar *env);
int ft_checkdollar(char *arg);
char *retrivevalue(t_envvar *env,  char *key);
int foundornot(char *line, t_envvar *env);
int is_valid_var_start(char c);
int is_alnum_or_underscore(char *str);
int extract_var_name(char *input, char *holder, int *index);
int handle_env_var(char *new_string, char *holder, t_envvar *env,
                          int *counter);
void ft_replace(t_token *token, t_envvar *env);
void noquotes(t_token *token, t_envvar *env);
char *spaced_string(char *line, t_shell *shell, int spaces, int counter_2);
int count_spaces(char *line);
int ft_nodescalculation(t_token *token);
int ft_checkdollarher(char *arg);
char *retrivevalueher(t_envvar *env,  char *key);
int foundornother(char *line, t_envvar *env);
int is_valid_var_char(char c);
int read_var_name(char *line, int *i, char *holder);
char  *ft_replaceher(char *line, t_envvar *env);
char	*noquotesher(char *line, t_envvar *env, int i, int j);
char	*process_dollar_token(char *line,  char *new_string, int *i,  int *j);
char	*replace_env_var(t_envvar *env, char *holder, char *new_string);
char *ft_expandherdoc(char *line, t_envvar *env);
int	isinornot(const char *arg, int in_quote , int i, int double_quote_count);
int	norm_3(int in_quotes);
int	norm_2(int in_quotes);
int	handle_dollar_sign(char *input, char *new_string, int *i, int *counter);
int	ft_arcal(t_token *tokens);
void norm_4(t_token *node);
void	norm_5(t_token *node);
int	handle_env_var(char *new_string, char *holder, t_envvar *env, int *counter);
int	extract_var_name(char *input, char *holder, int *index);
int	is_alnum_or_underscore(char *str);
void ft_exitstatus(char *line, int *i, char *new_string);









//Othmane functions
//includes
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>















// /*
// ! Builtins file commands prototypes
// ^(CD)
// */
// int		cd_builtin(t_cmd *cmd);
// void	update_env(char **env, const char *var, const char *value);
// char	*get_env(char **env, const char *var);



// /*
// ! Builtins file commands prototypes
// ^(ECHO)
// */

// int		echo_builtin(t_cmd *cmd);
// void	ft_putstr_flag(char *str, bool n_flag);



// /*
// ! Builtins file commands prototypes
// ^(ENV)
// */

// int		env_builtin(t_cmd *cmd);


// /*
// ! Builtins file commands prototypes
// ^(EXIT)
// */

// int		exit_builtin(t_cmd *cmd);
// bool	is_valid_number(const char *str);
// int		normalize_exit_status(int exit_status);


// /*
// ! Builtins file commands prototypes
// ^(EXPORT)
// */

// int	export_builtin(t_cmd *cmd);
// int	is_valid_identifier(const char *str);
// void	update_the_env_var(t_envvar *env_list, char *str);
// void	add_to_env_var(t_envvar *env_list, char *str);
// int	update_the_env_var2(t_envvar *env_list, char *str);
// void	find_or_update(t_envvar *env_list, char **str, int i);
// void	find_or_add(t_envvar *env_list, char *str);
// bool	find_env_var(t_envvar *env_list, char *str);;
// bool	ft_isalpha2(char c);


// /*
// ! Builtins file commands prototypes
// ^(EXPORT SORTING)
// */

// void	sort_the_linkedlist(t_envvar *env_list);
// void	bubble_sort(t_envvar *env_list);
// void	swap_nodes(t_envvar *a, t_envvar *b);
// bool	is_sorted(t_envvar *env_list);
// void	print_envvar(t_envvar *env_list);

// /*
// ! Builtins file commands prototypes
// ^(EXPORT APPENDING)
// */

// char	*join2(char const *s1, char const *s2);
// size_t	ft_str_lcpy(char *dst, const char *src, size_t dstsize);
// char	*ft_str_join(char const *s1, char const *s2);
// int		appending_env_var(t_envvar *env_list, char *str);
// int		add_to_env_var_appending(t_envvar *env_list, char *str);
// int		update_the_env_var_appending(t_envvar *env_list, char *str);
// bool	find_env_var_appending(t_envvar *env_list, char *str);




// /*
// ! Builtins file commands prototypes
// ^(SELLON.C file)
// */

void	handler(int signum);
int 	set_files(t_cmd *cmd, int index);
int 	set_files2(t_cmd *cmd, int index);
int 	implement_heredoc(t_cmd *cmd);
bool	set_redirections(t_redirection *file);
void	reset_redirections(void);
bool	execute_builtin(t_cmd *cmd);
int		execute_without_path(t_cmd *cmd);
char 	*get_full_path2(char **paths, t_cmd *cmd);
char 	*making_the_path(t_cmd *cmd);
void	join_order_with_args(t_cmd *cmd, char **args);
int		execute_with_path(t_cmd *cmd);
int		execute_cmd(t_cmd *cmd);
int 	ft_execute(t_cmd *cmd);
// int		second_child(t_cmd *cmd, int *fd);
// int		first_child(t_cmd *cmd, int *fd);
int		execute_pipe(t_cmd *cmd);
int		ft_execution(t_cmd *cmd);
// char	**parse_and_handle_redirection(t_shell *shell);
// int		count_commands_anf_flags(t_shell *shell);
// char	**copy_command_and_flags(t_shell *shell, char **only_args);

void		updating_shlvl(t_envvar *env_list);
void 		edit_env(t_envvar *env_list, char *key, char *value);
t_envvar 	*find_env(t_envvar *env_list, char *str);
char 		**rebuild_envp(t_envvar *env_list);
int 		count_heredoc(t_cmd *cmd);
char 		*get_env(char **env, const char *var);
void 		heredoc_sigint_handler(int signum);
void 		update_env(char ***env, const char *var, const char *value);
void 		cd_builtin2(char *old_pwd, char *new_pwd, char *path);
int 		implement_heredoc(t_cmd *cmd);
void		handle_parent_process(pid_t pid);
void		setup_child_signals(void);
void		free_args(char **args);
char		**prepare_command_args(t_cmd *cmd, char **args);
char		**construct_args(t_cmd *cmd);
void		cleanup_and_exit(int status);
void		free_args(char **args);
void		*ft_malloc(size_t size, char f_or_m);












































































































































































































































int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
long long int 	ft_atoll(const char *str);
int 			ll_max_check(char *str);


/*
! Builtins file commands prototypes
^(EXPORT)
*/
void	find_or_add(t_envvar *env_list, char *str);
void	sort_the_linkedlist(t_envvar *env_list);
void	print_envvar(t_envvar *env_list);
char	*ft_str_join(char const *s1, char const *s2);
size_t	ft_str_lcpy(char *dst, const char *src, size_t dstsize);
int		appending_env_var(t_envvar *env_list, char *str);
char	*join2(char const *s1, char const *s2);
void 	execute_shell_commands(t_shell *shell);
char	*ft_itoa(int n);
int	ft_count_len(int n);

/*
! Builtins file commands prototypes
^()
*/
int		export_builtin(t_cmd *cmd);
int		env_builtin(t_cmd *cmd);
// int		check_if_builtin(t_shell *shell);
int		echo_builtin(t_cmd *cmd);
int 	cd_builtin(t_cmd *cmd);
int		pwd_builtin(t_cmd *cmd);
int 	unset_builtin(t_cmd *cmd);
int 	exit_builtin(t_cmd *cmd);


/*
! exec file commands prototypes
^(run_minishell.c file and execute_command.c file)
*/

char				*join_path(const char *base, const char *command);
char				*get_full_path(char **paths, t_cmd *cmd);
void				check_command_access2(char **paths, t_shell *shell, t_cmd *cmd);
void				ft_putstr_fd(char *s, int fd);
char 				*ft_strtok(char *string, char c);
char    			*find_path(t_envvar *envp);
void 				check_command_access(char **paths, char **command, t_shell *shell);
int 				counte_temp(char *temp);
char    			**split_path(char *path_string);
char 				**split_path3(char **paths, char *path_copy);
int 				count_commands_anf_flags(t_shell *shell);
char 				**copy_command_and_flags(t_shell *shell, char **only_args);
char 				**parse_and_handle_redirection(t_shell *shell);
void    			run_simplecmd(t_shell *shell,t_envvar *envp,char **av);


/*
! Redirections file commands prototypes
^(Heredoc.c file)
*/

void				pid_is_0(char *input_file, char *cmd, t_envvar *envp, t_shell *shell);
void				execute_command_with_heredoc(char *input_file, char *cmd,
					t_envvar *envp, t_shell *shell);
void				process_heredoc_input(char *delimiter, char *filename);
void	heredoc_inplementation_0(int heredoc_counter, t_cmd *current,
		t_shell *shell, char **heredoc_files);
void	heredoc_inplementation(int heredoc_counter, t_cmd *current,
		t_shell *shell, char **heredoc_files);
bool				check_heredoc(t_shell *shell);
int					handle_heredoc(t_shell *shell);
void execute_command_with_multiple_heredocs(char **heredoc_files, int count,
                                            char *cmd, t_envvar *envp, t_shell *shell);

/*
! Redirections file commands prototypes
^(Heredoc2.c file)
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_len(int value);
char	*ft_itoa(int n);

/*
! Redirections file commands prototypes
^(pipes.c file)
*/
void	close_pipes(int *pipes_array, int count);
void	execute_commands(t_shell *shell, t_cmd *current, int *pipes_array,
		int count);
void	create_pipe_array(int count, int *pipes_array);
int		count_commands(t_cmd *current);
void	handle_pipes(t_shell *shell);

/*
! Redirections file commands prototypes
^(pipes2.c file)
*/

void	execute_single_command(t_shell *shell, int *pipes_array, int i,
		int count);
void	wait_for_children(int count);
void	close_unused_pipes(int *pipes_array, int count, int i);
void	setup_redirection(int *pipes_array, int i, int direction);


/*
! Redirections file commands prototypes
^(redirects.c file)
*/

int			handle_single_redirections(t_redirection *current);
// static int	child_handle_redirections(t_shell *shell);
void		restore_fds(int saved_stdin, int saved_stdout);
// static int	prepare_redirections(int *saved_stdin, int *saved_stdout);
int			execute_redirections(t_shell *shell);


/*
! Redirections file commands prototypes
^(redirects2.c file)
*/
int	handle_single_redirections2(t_redirection *current);
// int	open_output_file(char *file, t_types identifier);
// int	open_input_file(char *file);


#endif
