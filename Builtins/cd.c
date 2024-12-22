/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:33:31 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/22 01:08:00 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#define MAX_PATH 1024

char *ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void update_env(char ***env, const char *var, const char *value)
{
    int     i = 0;
    size_t  var_len;
    char    *new_entry;

    var_len = ft_strlen(var);

    while ((*env)[i] != NULL)
    {
        if (ft_strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
        {
            // free((*env)[i]);
			// ft_malloc(0, 'f');
            new_entry = ft_malloc((ft_strlen(var) + ft_strlen(value)) * 100, 'm');
			// new_entry = malloc((ft_strlen(var) + ft_strlen(value)) * 100);
            if (!new_entry)
            {
                perror("malloc error");
                return;
            }
            ft_strcpy(new_entry, var);
            ft_strcat(new_entry, "=");
            ft_strcat(new_entry, value);
            (*env)[i] = new_entry;
            return;
        }
        i++;
    }
    new_entry = ft_malloc((ft_strlen(var) + ft_strlen(value)) * 100, 'm');
	// new_entry = malloc((ft_strlen(var) + ft_strlen(value)) * 100);
    if (!new_entry)
    {
        perror("malloc error");
        return;
    }
    ft_strcpy(new_entry, var);
    ft_strcat(new_entry, "=");
    ft_strcat(new_entry, value);
    if (!*env)
    {
        perror("realloc error");
        return;
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
		ft_strncpy(old_pwd, logical_pwd, sizeof(old_pwd) - 1);
	else
		old_pwd[0] = '\0';
}

int	path_from_shell_env(t_cmd *cmd, char **path)
{
	*path = get_env(shell.envholder, "HOME");
	if (!*path)
	{
		perror("cd: HOME not set");
		shell.exit = 1;
		return (1);
	}
	return (0);
}

void	print_it_norm(char *path)
{
	// fprintf(stderr, "cd: %s: ", path);
	perror("cd");
	perror("");
	shell.exit = 1;
}

void	print_it_norm2(char *path)
{
	printf("cd: %s: error retrieving current directory\n", path);
	shell.exit = 1;
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
			print_it_norm2(path);
			free(new_pwd);
			return ;
		}
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



























// void add_env(t_envvar *env, char *key, char *value)
// {
//     t_envvar *tmp;
//     t_envvar *new;

//     tmp = env;
//     new = (t_envvar *)malloc(sizeof(t_envvar));
//     if (!new)
//         return; // Handle allocation failure
//     new->key = key;
//     new->value = value;
//     new->next = NULL;
//     while (tmp->next)
//         tmp = tmp->next;
//     tmp->next = new;
// }

// t_envvar *find_env(t_envvar *env, char *key)
// {
//     while (env)
//     {
//         if (env->key && ft_strcmp(env->key, key) == 0)
//             return env;
//         env = env->next;
//     }
//     return NULL;
// }

// void print_stderr(char *str)
// {
//     ft_putstr_fd("minishell: ", 2);
//     ft_putstr_fd(str, 2);
//     ft_putstr_fd("\n", 2);
// }

// static int cd_runner(char *dir)
// {
//     char curr[1024];
//     char *oldpwd;

//     oldpwd = NULL;
//     if (chdir(dir) == 0)
//     {
//         if (getcwd(curr, sizeof(curr)))
//         {
//             // Get the old PWD value
//             t_envvar *pwd_env = find_env(shell.envp, "PWD");
//             oldpwd = pwd_env ? ft_strdup(pwd_env->value) : NULL;

//             // Update PWD first
//             update_env2("PWD", curr);

//             // Update OLDPWD and free oldpwd after
//             update_env2("OLDPWD", oldpwd);

//             // No need to free oldpwd here as update_env2 handles it
//             return 0;
//         }
//         else
//         {
//             perror("cd: error retrieving current directory");
//             return 1;
//         }
//     }
//     else
//     {
//         perror("cd");
//         return 1;
//     }
// }

// void update_env2(char *key, char *value)
// {
//     t_envvar *tmp;
//     char *new_value;

//     tmp = find_env(shell.envp, key);
//     if (value)
//         new_value = ft_strdup(value);
//     else
//         new_value = NULL;

//     if (tmp != NULL)
//     {
//         // Free old value if it exists
//         if (tmp->value)
//             free(tmp->value);
//         tmp->value = new_value;
//     }
//     else
//     {
//         // Add new environment variable
//         add_env(shell.envp, ft_strdup(key), new_value);
//     }
// }

// int count_args(t_cmd *cmd)
// {
//     int count = 0;

//     while (cmd)
//     {
//         count++;
//         cmd = cmd->next;
//     }
//     return count;
// }
// static int cha_dir(char *dir)
// {
//     char *path;

//     path = find_env(shell.envp, dir) ? find_env(shell.envp, dir)->value : NULL;
//     if (!path || !*path)
//     {
//         ft_putstr_fd("cd: ", 2);
//         ft_putstr_fd(dir, 2);
//         ft_putstr_fd(" not set\n", 2);
//         return 1;
//     }
//     return cd_runner(path);
// }


// int cd_builtin(t_cmd *cmd)
// {
//     int arg_count;

//     arg_count = count_args(cmd);
//     if (arg_count == 1)
//         return cha_dir("HOME");
//     else if (arg_count == 2 && ft_strcmp(*cmd->next->args, "-") == 0)
//         return cha_dir("OLDPWD");
//     else if (arg_count == 2)
//         return cd_runner(*cmd->next->args);
//     else
//     {
//         print_stderr("cd: too many arguments");
//         return 1;
//     }
// }

