/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:33:31 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/07 22:35:37 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#define MAX_PATH 1024

// Helper function to update environment variables
/**
 * !Purpose of =========update_env===========:
 * ?The update_env function is designed to update an existing environment variable or add a new one if it doesn't exist.
 * ?It typically takes three parameters:
 * ?the environment array, the name of the variable, and the new value to set.
 */
/*
!Purpose of =========get_env===========:
?The get_env function is designed to retrieve the value of a specific environment variable from the environment array.
?It takes two parameters:
?the environment array and the name of the variable you're looking for.
?It should return the value of that variable if found, or NULL if the variable doesn't exist in the environment.
*/


void update_env(char **env, const char *var, const char *value)
{
    int i;
    size_t var_len;
    char *new_entry;

    i = 0;
    var_len = strlen(var);
    while (env[i] != NULL)
    {
        if (strncmp(env[i], var, var_len) == 0 && (env[i][var_len] == '='))// Variable found, update it
        {
            new_entry = malloc(strlen(var) + strlen(value) + 2);// +2 for '=' and null terminator
            if (new_entry == NULL)
            {
                printf("Malloc Error");
                return;
            }
            strcpy(new_entry, var);
            strcat(new_entry, "=");
            strcat(new_entry, value);
            free(env[i]);
            env[i] = new_entry;
            return;
        }
        i++;
    }
}
char *get_env(char **env, const char *var)
{
    int i = 0;
    size_t var_len = strlen(var);

    while (env[i] != NULL) {
        if (strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=') {
            return &env[i][var_len + 1];
        }
        i++;
    }
    return NULL;
}

int cd_builtin(t_cmd *cmd)
{
    char old_pwd[MAX_PATH];
    char new_pwd[MAX_PATH];
    char *path = NULL;

    // Get current working directory
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("cd: getcwd error");
        return 1;
    }

    // Determine the path to change to
    if (cmd->args == NULL || cmd->args[0] == NULL)
    {
        // No argument, go to HOME
        path = get_env(shell.envholder, "HOME");
        if (path == NULL)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
    else if (strcmp(cmd->args[0], "-") == 0)
    {
        // Go to previous directory
        path = get_env(shell.envholder, "OLDPWD");
        if (path == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        printf("%s\n", path);
    }
    else
    {
        // Use provided path
        path = cmd->args[0];
    }

    // Change directory
    if (chdir(path) == -1)
    {
		dprintf(2, "path: %s\n", path);
        perror("cd: chdir error");
        return 1;
    }

    // Get new current working directory
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
    {
        perror("cd: getcwd error");
        return 1;
    }

    // Update environment variables
    update_env(shell.envholder, "OLDPWD", old_pwd);
    update_env(shell.envholder, "PWD", new_pwd);

    return 0;
}
