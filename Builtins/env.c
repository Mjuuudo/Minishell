/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:29:37 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/16 09:34:40 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	free_env(t_envvar *env)
{
	t_envvar	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	env_add_back(t_envvar **env, t_envvar *new)
{
	t_envvar	*tmp;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_envvar	*create_env_node(char *key, char *value, int is_exported)
{
	t_envvar	*new;

	new = (t_envvar *)malloc(sizeof(t_envvar));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_envvar	*create_env(void)
{
	t_envvar	*env;
	char		*path;

	env = NULL;
	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	env_add_back(&env, create_env_node(ft_strdup("PATH"), ft_strdup(path), 2));
	env_add_back(&env, create_env_node(ft_strdup("PWD"), getcwd(NULL, 0), 1));
	env_add_back(&env, create_env_node(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	env_add_back(&env, create_env_node(ft_strdup("OLDPWD"), NULL, 1));
	env_add_back(&env, create_env_node(ft_strdup("_"), ft_strdup("./minishell"),
			1));
	return (env);
}

void	print_all_env(t_envvar *envp)
{
	t_envvar	*current;

	current = envp;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_specific_env(t_envvar *envp, char **args)
{
	t_envvar	*current;
	int			i;

	i = 0;
	while (args[i] != NULL)
	{
		current = envp;
		while (current)
		{
			if (ft_strcmp(current->key, args[i]) == 0)
			{
				if (current->value != NULL)
					printf("%s=%s\n", current->key, current->value);
				break ;
			}
			current = current->next;
		}
		i++;
	}
}

int	env_builtin(t_cmd *cmd)
{
	if (shell.envp == NULL)
		shell.envp = create_env();
	if (cmd->args[0] == NULL)
		print_all_env(shell.envp);
	else
		print_specific_env(shell.envp, cmd->args);
	return (0);
}
