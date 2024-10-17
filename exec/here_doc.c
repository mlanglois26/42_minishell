/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:31:11 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 16:54:39 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_heredoc(t_data *data, int here_doc_pipe[2])
{
	printf("\nbash: warning: here-document delimited by end-of-file\n");
	close(here_doc_pipe[1]);
	big_free(data);
	exit(0);
}

int	handle_here_doc(char *delimiter, t_data *data)
{
	int		here_doc_pipe[2];
	char	*line;

	if (pipe(here_doc_pipe) == -1)
		exit(write(2, "Erreur de pipe here_doc\n", 24));
	while (1)
	{
		write(2, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			exit_heredoc(data, here_doc_pipe);
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(here_doc_pipe[1], line, strlen(line));
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
	close(here_doc_pipe[1]);
	return (here_doc_pipe[0]);
}
