/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:40:13 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 17:34:32 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_too_many_args(char **path)
{
	if (path[1] && path[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	is_home_path(char **path)
{
	if (ft_strcmp(path[0], "~") == 0 && (path[1] == NULL || path[1][0] == '\0'))
	{
		printf("bash: %s: Is a directory\n", getenv("HOME"));
		if (getenv("HOME") == NULL)
		{
			printf("bash: cd: HOME not set\n");
			return (1);
		}
	}
	return (0);
}

static int	handle_cd_without_args(char **path, t_data *data)
{
	char	*home_path;

	home_path = NULL;
	if (data->home_flag == 0 && data->path_flag == 0)
		home_path = getenv("HOME");
	if (home_path == NULL)
	{
		printf("bash: cd: HOME not set\n");
		return (1);
	}
	free(path[0]);
	path[0] = ft_strdup(home_path);
	if (!path[0])
	{
		return (1);
	}
	if (chdir(path[0]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path[0]);
		return (1);
	}
	return (0);
}

static int	handle_cd_with_dash(char **path, t_data *data)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (data->oldpwd_flag == 0 && data->path_flag == 0)
		oldpwd = getenv("OLDPWD");
	if (oldpwd == NULL)
	{
		printf("bash: cd: OLDPWD not set\n");
		return (1);
	}
	printf("%s\n", oldpwd);
	if (chdir(oldpwd) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path[1]);
		return (1);
	}
	return (0);
}

int	cd_cmd(char **path, t_data *data)
{
	if (handle_too_many_args(path))
		return (1);
	if (is_home_path(path))
		return (1);
	if (ft_strcmp(path[0], "cd") == 0 && (path[1] == NULL
			|| path[1][0] == '\0' || path[1][0] == '~'))
	{
		return (handle_cd_without_args(path, data));
	}
	if (ft_strcmp(path[0], "cd") == 0 && path[1] && path[1][0] == '-')
	{
		return (handle_cd_with_dash(path, data));
	}
	if (path[1] && chdir(path[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path[1]);
		return (1);
	}
	return (0);
}
