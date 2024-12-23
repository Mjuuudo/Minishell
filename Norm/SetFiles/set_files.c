/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:17:04 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:26:06 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"
#include <errno.h>

// int	set_files3(t_cmd *cmd)
// {
// 	char	*template;
// 	int		fd;

// 	template = ft_strdup("/tmp/minishell-XXXXXX");
// 	fd = mkstemp(template);
// 	printf("template: %s\n", template);
// 	if (fd == -1)
// 	{
// 		perror("minishell: Failed to create temporary file");
// 		return (-1);
// 	}
// 	shell.temp_file = ft_strdup(template);
// 	return (fd);
// }

static int get_counter(void)
{
    static int counter = 0;
    return (counter++);
}

int set_files3(t_cmd *cmd)
{
    char    *filename;
    int     fd;
    char    *temp;
    int     counter;
    char    *base;

    counter = get_counter();
    temp = ft_itoa(counter);
    base = ft_strjoin("/tmp/minishell-", temp);

    while (1)
    {
        fd = open(base, O_CREAT | O_RDWR | O_EXCL, 0600);
        if (fd != -1)
            break;
        if (errno == EEXIST)
        {
            counter++;
            temp = ft_itoa(counter);
            base = ft_strjoin("/tmp/minishell-", temp);
            continue;
        }
        return (-1);
    }
    return (shell.temp_file = base, fd);
}

int	set_files2(t_cmd *cmd, int index)
{
	char	*file_name;
	char	*num;
	int		fd;

	file_name = ft_strdup("/tmp/montasir0_");
	num = ft_itoa(index);
	shell.temp_file = ft_strjoin(file_name, num);
	fd = open(shell.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("minishell00$");
	return (fd);
}
