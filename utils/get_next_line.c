/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:36:32 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/17 10:37:08 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_extract_first_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_remove_first_line(char *buffer)
{
	char	*newline_loc;
	int		i;
	int		j;

	newline_loc = ft_strchr(buffer, '\n');
	if (!newline_loc)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	newline_loc++;
	i = 0;
	j = 0;
	while (newline_loc[i])
	{
		buffer[j++] = newline_loc[i++];
	}
	buffer[j] = '\0';
	return (buffer);
}

char	*ft_join_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

char	*ft_extract_buffer(int fd, char *buffer)
{
	int		read_statut;
	char	stash[BUFFER_SIZE + 1];
	char	*temp_buffer;

	read_statut = 1;
	temp_buffer = ft_calloc(1, sizeof(char));
	if (!temp_buffer)
		return (NULL);
	while (read_statut > 0)
	{
		read_statut = read(fd, stash, BUFFER_SIZE);
		if (read_statut == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		stash[read_statut] = '\0';
		temp_buffer = ft_join_free(temp_buffer, stash);
		if (ft_strchr(temp_buffer, '\n'))
			break ;
	}
	strncpy(buffer, temp_buffer, BUFFER_SIZE);
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(buffer, '\n'))
	{
		if (!ft_extract_buffer(fd, buffer))
			return (NULL);
	}
	line = ft_extract_first_line(buffer);
	ft_remove_first_line(buffer);
	return (line);
}
