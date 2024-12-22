/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:17:04 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/21 16:13:32 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

// int	set_files(t_cmd *cmd, int index)
// {
// 	char	*file_name;
// 	char	*num;
// 	int		fd;

// 	file_name = ft_strdup("/tmp/montasir_");
// 	num = ft_itoa(index);
// 	shell.temp_file = ft_strjoin(file_name, num);
// 	// free(file_name);
// 	// free(num);
// 	fd = open(shell.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		perror("minishell00$");
// 	// close(fd);
// 	return (fd);
// }


// int set_files(t_cmd *cmd) {
//     char template[] = "mont_XXXXXX"; // Template for mkstemp
//     int fd = mkstemp(template);
//     if (fd == -1) {
//         perror("minishell: Failed to create temporary file");
//         return -1;
//     }
//     shell.temp_file = strdup(template); // Store the file name
//     return fd;
// }

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
