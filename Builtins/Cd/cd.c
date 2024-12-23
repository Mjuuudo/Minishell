/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:33:31 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:37:37 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"
#define MAX_PATH 1024

void	new_entry2(char *new_entry, const char *var, const char *value,
		char ***env)
{
	size_t	var_len;
	int		i;

	var_len = ft_strlen(var);
	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new_entry = ft_malloc((ft_strlen(var) + ft_strlen(value) + 1) * 100, 'm');
	if (!new_entry)
	{
		perror("malloc error");
		return ;
	}
	ft_strcpy(new_entry, var);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	(*env)[i] = new_entry;
	(*env)[i + 1] = NULL;
}

void	update_env(char ***env, const char *var, const char *value)
{
	int		i;
	size_t	var_len;
	char	*new;

	i = 0;
	var_len = ft_strlen(var);
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], var, var_len) == 0
			&& (*env)[i][var_len] == '=')
		{
			new = ft_malloc((ft_strlen(var) + ft_strlen(value)) * 100, 'm');
			if (!new)
			{
				perror("malloc error");
				return ;
			}
			(ft_strcpy(new, var), ft_strcat(new, "="), ft_strcat(new, value));
			(*env)[i] = new;
			return ;
		}
		i++;
	}
	new_entry2(new, var, value, env);
}

char	*get_env(char **env, const char *var)
{
	int		i;
	size_t	var_len;

	if (!env || !var)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (NULL);
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

void	cd_builtin2(char *old_pwd, char *new_pwd, char *path)
{
	char	buffer[1024];

	if (chdir(path) == -1)
	{
		print_it_norm(path);
		return ;
	}
	if (strcmp(path, "..") == 0)
	{
		new_pwd = getcwd(buffer, 1024);
		if (!new_pwd)
		{
			(print_it_norm2(path), free(new_pwd));
			return ;
		}
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		(update_env(&(shell.envholder), "PWD", new_pwd), free(new_pwd));
	else
		update_env(&(shell.envholder), "PWD", path);
	update_env(&(shell.envholder), "OLDPWD", old_pwd);
	shell.exit = 0;
}
