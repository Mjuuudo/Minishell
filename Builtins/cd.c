/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:33:31 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/16 13:32:40 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#define MAX_PATH 1024

void	update_existing_env_entry(char ***env, const char *var,
		const char *value, int i)
{
	size_t	var_len;

	var_len = strlen(var);
	if (strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
	{
		free((*env)[i]);
		(*env)[i] = malloc(strlen(var) + strlen(value) + 2);
		if (!(*env)[i])
		{
			perror("malloc error");
			return ;
		}
		sprintf((*env)[i], "%s=%s", var, value);
	}
}

void	update_env(char ***env, const char *var, const char *value)
{
	int		i;
	char	*new_entry;

	i = 0;
	while ((*env)[i] != NULL)
	{
		update_existing_env_entry(env, var, value, i);
		i++;
	}
	new_entry = malloc(strlen(var) + strlen(value) + 2);
	if (!new_entry)
	{
		perror("malloc error");
		return ;
	}
	sprintf(new_entry, "%s=%s", var, value);
	*env = realloc(*env, sizeof(char *) * (i + 2));
	if (!*env)
	{
		perror("realloc error");
		return ;
	}
	(*env)[i] = new_entry;
	(*env)[i + 1] = NULL;
}

char	*get_env(char **env, const char *var)
{
	int		i;
	size_t	var_len;

	if (!env || !var)
		return (NULL);
	var_len = strlen(var);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

void	get_logical_pwd(char **env, char *old_pwd)
{
	char	*logical_pwd;

	logical_pwd = get_env(shell.envholder, "PWD");
	if (logical_pwd)
		strncpy(old_pwd, logical_pwd, sizeof(old_pwd) - 1);
	else
		old_pwd[0] = '\0';
}

int	path_from_shell_env(t_cmd *cmd, char **path)
{
	*path = get_env(shell.envholder, "HOME");
	if (!*path)
	{
		fprintf(stderr, "cd: HOME not set\n");
		shell.exit = 1;
		return (1);
	}
	return (0);
}

int	cd_builtin(t_cmd *cmd)
{
	char	old_pwd[MAX_PATH];
	char	*new_pwd;
	char	*path;

	new_pwd = NULL;
	path = NULL;
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		get_logical_pwd(shell.envholder, old_pwd);
	if (!cmd->args || !cmd->args[0])
	{
		shell.exit = path_from_shell_env(cmd, &path);
		if (shell.exit == 1)
			return (1);
	}
	else
		path = cmd->args[0];
	cd_builtin2(old_pwd, new_pwd, path);
	return (0);
}

void	print_it_norm(char *path)
{
	fprintf(stderr, "cd: %s: ", path);
	perror("");
	shell.exit = 1;
}

void	print_it_norm2(char *path)
{
	fprintf(stderr,
		"cd: error retrieving current directory: \
			getcwd: cannot access parent directories\n");
	shell.exit = 1;
}

void	cd_builtin2(char *old_pwd, char *new_pwd, char *path)
{
	if (chdir(path) == -1)
	{
		print_it_norm(path);
		return ;
	}
	if (strcmp(path, "..") == 0)
	{
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
		{
			print_it_norm2(path);
			return ;
		}
		free(new_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env(&(shell.envholder), "PWD", new_pwd);
		free(new_pwd);
	}
	else
		update_env(&(shell.envholder), "PWD", path);
	update_env(&(shell.envholder), "OLDPWD", old_pwd);
	shell.exit = 0;
}

// valgrind --leak-check=full --track-origins=yes ./minishell
// # Inside minishell:
// echo "Hello, Pipe!" | grep Hello
// ls | wc -l
// cat Makefile | grep all | wc -l
// exit
