/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerkeb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/26 06:48:54 by akerkeb           #+#    #+#             */
/*   Updated: 2015/03/22 20:40:37 by akerkeb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_change(char **splitline, t_env *e)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	while (e->env[i])
	{
		if (ft_strncmp(e->env[i], splitline[1], ft_strlen(splitline[1])) == 0)
		{
			tmp = (char **)malloc(sizeof(char *) * ft_strlen(e->env[i]));
			if (tmp == NULL)
				return (-1);
			tmp[k] = e->env[i];
			tmp[k] = ft_strjoin(splitline[1], "=");
			tmp[k] = ft_strjoin(tmp[k], splitline[2]);
			e->env[i] = tmp[k];
		}
		i++;
	}
	return (0);
}

void	ft_addsetenv(char **splitline, t_env *e)
{
	int		i;
	char	**tmp;

	i = 0;
	while (e->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (tmp == NULL)
		return ;
	i = 0;
	while (e->env[i])
	{
		tmp[i] = ft_strdup(e->env[i]);
		i++;
	}
	tmp[i] = ft_strjoin(splitline[1], "=");
	tmp[i] = ft_strjoin(tmp[i], splitline[2]);
	tmp[i + 1] = NULL;
	e->env = tmp;
}

int		is_chekenv(t_env *e, char **splitline)
{
	int		i;

	i = 0;
	while (e->env[i])
	{
		if (ft_strncmp(e->env[i], splitline[1], ft_strlen(splitline[1])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		error_setenv(char **splitline)
{
	int		i;

	i = 0;
	while (splitline[i])
		i++;
	if (i > 4)
	{
		ft_putendl_fd("Too much arguments", 2);
		return (0);
	}
	else if (i == 1 || (i == 4 &&
	splitline[3][0] != '0' && splitline[3][0] != '1'))
	{
		ft_putendl_fd("setenv usage : setenv VARIABLE value [0-1]", 2);
		return (0);
	}
	else if (i < 3)
	{
		ft_putendl_fd("Not enough arguments", 2);
		return (0);
	}
	return (1);
}

int		ft_setenv(char **splitline, t_env *e)
{
	if (error_setenv(splitline))
	{
		if (is_chekenv(e, splitline) == 0)
			ft_addsetenv(splitline, e);
		else if (splitline[3])
		{
			if (splitline[3][0] == '1')
				ft_change(splitline, e);
		}
		get_path(e);
	}
	return (0);
}
