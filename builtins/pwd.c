/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:40:24 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:01:14 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_cmd(void)
{
	char	*cwd;
	size_t	size;

	cwd = NULL;
	size = 0;
	cwd = getcwd(cwd, size);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	else
	{
		perror("getcwd");
		return (-1);
	}
}

int	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}
