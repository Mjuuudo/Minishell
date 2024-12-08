/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:42:20 by oer-refa          #+#    #+#             */
/*   Updated: 2024/11/26 11:05:13 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

/**
 * handle_single_redirections2 - Handles redirections 
 * for a single redirection type.
 * @current: A pointer to the current redirection structure.
 * This function determines the type of redirection based on the identifier
 * in the redirection structure and opens the corresponding file.
 * It returns the file descriptor of the opened file.
 */

int	handle_single_redirections2(t_redirection *current)
{
	int	fd;

	if (current->identifier == GREAT)
		fd = open_output_file(current->file, current->identifier);
	else if (current->identifier == LESS)
		fd = open_input_file(current->file);
	else if (current->identifier == DGREAT)
		fd = open_output_file(current->file, current->identifier);
	return (fd);
}

/**
 * open_output_file - Opens an output file based on the redirection type.
 * @file: The name of the file to open.
 * @identifier: The type of redirection (GREAT or DGREAT).
 *
 * Depending on the identifier, this function either truncates the file (GREAT)
 * or appends to the file (DGREAT). The file is created if it does not exist.
 * It returns the file descriptor of the opened file or -1 if an error occurs.
 */

int	open_output_file(char *file, t_types identifier)
{
	int	fd;

	printf("identifier: %d\n", identifier);
	if (identifier == GREAT)
	{
		printf("identifier GREAT: %d\n", identifier);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (identifier == DGREAT)
	{
		printf("identifier DEGREAT: %d\n", identifier);
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		perror("Failed to open output file");
		return (-1);
	}
	return (fd);
}
/**
 * open_input_file - Opens an input file for reading.
 * @file: The name of the file to open.
 *
 * This function opens the specified file in read-only mode.
 * It returns the file descriptor of the opened file or -1 if an error occurs.
 */

int	open_input_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file");
		return (-1);
	}
	return (fd);
}
