/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 02:19:19 by akerkeb           #+#    #+#             */
/*   Updated: 2015/02/22 16:59:31 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*test_path(t_env *e, char *line)
{
	int		i;
	char	*c_path;

	i = 0;
	c_path = NULL;
	if (e->path)
	{
		while (e->path[i])
		{
			if (access(jointadd(e->path[i], line), X_OK) == 0)
			{
				c_path = jointadd(e->path[i], line);
				break ;
			}
			i++;
		}
	}
	return (c_path);
}

void	ft_execve(char **splitline, t_env *e)
{
	pid_t	father;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
		execve(test_path(e, splitline[0]), splitline, e->env);
}

int		tchek_sp_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		ft_flnmain(char **splitline, t_env *e)
{
	if (splitline[0] != NULL)
	{
		if (!ft_strncmp(splitline[0], "./", 2) ||
			!ft_strncmp(splitline[0], "/", 1))
			ft_ps(splitline, e);
		else if (is_builtins(splitline, e))
			;
		else if (test_path(e, splitline[0]) == NULL)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(splitline[0], 2);
		}
		else
			ft_execve(splitline, e);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_env	e;
	char	*line;
	char	**splitline;
	char	**splitpv;

	(void)ac;
	(void)av;
	signal(SIGINT, signal_handler);
	e.env = env;
	e.i = 0;
	get_path(&e);
	ft_putstr("Melr $> ");
	while (get_next_line(0, &line))
	{
		splitpv = ft_strsplit(line, ';');
		while (splitpv[e.i] != '\0')
		{
			splitline = strsplit_fn(splitpv[e.i], &tchek_sp_tab);
			ft_flnmain(splitline, &e);
			e.i++;
		}
		e.i = 0;
		ft_putstr("Melr $> ");
	}
	return (0);
}
