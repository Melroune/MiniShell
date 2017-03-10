/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 05:53:11 by akerkeb           #+#    #+#             */
/*   Updated: 2015/01/07 05:53:14 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_builtins(char **splitline, t_env *e)
{
	if (ft_strcmp(splitline[0], "exit") == 0)
		exit(splitline[1] ? ft_atoi(splitline[1]) : 0);
	else if (ft_strcmp(splitline[0], "env") == 0)
	{
		ft_env(e);
		return (1);
	}
	else if (ft_strcmp(splitline[0], "setenv") == 0)
	{
		ft_setenv(splitline, e);
		return (1);
	}
	else if (ft_strcmp(splitline[0], "unsetenv") == 0)
	{
		ft_unsetenv(e, splitline);
		return (1);
	}
	else if (ft_strcmp(splitline[0], "cd") == 0)
	{
		ft_cd(e, splitline);
		return (1);
	}
	return (0);
}

void	ft_ps(char **splitline, t_env *e)
{
	struct stat		sb;
	pid_t			father;

	if (!lstat(splitline[0], &sb))
	{
		if (!access(splitline[0], X_OK) && (sb.st_mode & S_IFMT) != S_IFDIR)
		{
			father = fork();
			if (father > 0)
				wait(NULL);
			if (father == 0)
				execve(splitline[0], splitline, e->env);
		}
		else
		{
			ft_putstr_fd("cd : permission denied : ", 2);
			ft_putendl_fd(splitline[0], 2);
		}
	}
	else
	{
		ft_putstr_fd("cd : permission denied : ", 2);
		ft_putendl_fd(splitline[0], 2);
	}
}

char	*jointadd(char *road, char *command)
{
	char	*c_path;
	char	*newroad;

	newroad = ft_strjoin(road, "/");
	c_path = ft_strjoin(newroad, command);
	return (c_path);
}

void	cd_swap5(char *s1, t_env *e)
{
	if (ft_strstr(getvar(e, "PWD"), s1) == NULL)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(s1);
	}
}

void	signal_handler(int sig)
{
	(void)sig;
	ft_putstr("\n");
	ft_putstr("Melr $> ");
}
